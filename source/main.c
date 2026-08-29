/**
 * @mainpage
 * @file main.c
 */

#include <errno.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#include "model/global.h"
#include "model/new-stat-model.h"
#include "main/process-dir.h"

#include "utils/malloc.h"
#include "utils/string.h"
#include "options/options.h"
#include "features/time/time.h"

#include "debugging/debugging.h"

/// How many children to allocate memory for, when we don't know how many children there are going to be.
#define INIT_CHILD_COUNT 2

/// Approximately multiplies a number by 1.5
#define MULT_BY_1_5(var) ((var) += (var) == 1 ? 1 : (var) >> 1)

#define printError(errno_) \
	fprintf(stderr, "%s: %s: %s\n", argv0, path, strerror(errno_))

static inline const char *getArgv0(const int argc, char *restrict argv[]);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

path_t G_DOTDIR_PATH;
const char *argv0;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

int main(const int argc, char *argv[]) {
	initDebugging(argv);

	// set the locale to the system default (it'll check the env vars)
	//	(this is to ensure that multibyte characters can be printed as file icons)
	const char *const locale = setlocale(LC_ALL, "");
	if(!strends(locale, "UTF-8")) debug(WARNING, "Non-UTF-8 locale - locale is '%s'", locale);

	argv0 = getArgv0(argc, argv);

	/* —— Parse User Options ————————————————————————————————————————————————————————————————————— */

	// parse the user's inputted options, and find where the options end (& where the files start)
	//	e.g. if the program is run as `lk --clear --sort name ~/.config/options`, then `files_start` will be 4
	const int opt_count = setOptions(argc, (const char**)argv);

	/* —— Determine Input Paths —————————————————————————————————————————————————————————————————— */

	/// How many filepaths were entered after the options ended.
	/// If there were no path entered, then assume there was just one path (`.`).
	const int file_count = opt_count < argc ? argc - opt_count : 1;

	/// The raw string paths inputted by the user.
	char **file_paths = argv + opt_count;
	// if there were no paths entered, then assume the user inputted the path `.`
	if (opt_count >= argc) file_paths[0] = DOTDIR;

	/* —— Find Target Files/Dirs ————————————————————————————————————————————————————————————————— */

	/// Whether the user inputted at least one valid input into the function.
	bool any_valid_input = false;

	/// An array of pointers to FileStat objects, each representing the inputted files/dirs.
	FileStat *fs_input_arr[file_count];

	for (int i = 0; i < file_count; i++) {
		char *path = file_paths[i];
		struct stat file_stat = {0};

		printf("%d: %s\n", i, path);

		/* ———————————————————————————————————————————————————————————— */

		// firstly, try to run `lstat` on the input path
		//	the reason we're `stat`ting the file upfront is because we absolutely _need_ to know
		//	whether its a directory or not, so we might as well store the stat information if we have it
		if (lstat(path, &file_stat) == -1) {
			// if it fails, print an error and move onto the next file
			const int stat_errno = errno;
			if (stat_errno == ENOENT) { /* handle */ }

			printError(stat_errno);

			// set the pointer to this input to NULL, so we know not to process it later
			fs_input_arr[i] = NULL;
			continue;
		}

		// file was `stat`ted successfully - note down that we've had at least 1 valid input
		any_valid_input = true;

		/* ———————————————————————————————————————————————————————————— */
		// since we successfully got the `stat` information, we can start building the `FileStat` object

		// allocate memory for this file's `FileStat` object, and zero the memory
		FileStat *const p_fsobj = ecalloc(1, sizeof(FileStat));
		// and add its pointer to the input array
		fs_input_arr[i] = p_fsobj;

		/* ———————————————————————————————————————————————————————————— */

		// allocate memory for the `stat` object that will be pointed to by `FileStat::s`
		struct stat *const p_stat = emalloc(sizeof(struct stat));

		// copy `file_stat` from the stack into the newly-allocated heap memory,
		//	and then assign the pointer to that heap memory to `FileStat::s`
		p_fsobj->s = memcpy(p_stat, &file_stat, sizeof(struct stat));

		// finally, allocate memory for the `FileStatFields` object, and assign its pointer to the FileStat object
		p_fsobj->f = ecalloc(1, sizeof(FileStatFields));

		/* ———————————————————————————————————————————————————————————— */

		// since `path` comes from `file_paths`, which comes from `argv`, the memory containing `p_fsobj->name`
		//	doesn't need to be allocated, since pointers to `argv` exist through the lifetime of the program
		p_fsobj->name = path;
		// we don't know the name's length, so set it to -1 for now, and we can calculate it later if need be
		p_fsobj->name_len = -1;

		/* ———————————————————————————————————————————————————————————— */

		// if the input was a file (i.e. not a dir), then there's nothing else to do at this stage
		if (!S_ISDIR(file_stat.st_mode) || DIRS_AS_FILES()) continue;

		/* ———————————————————————————————————————————————————————————— */
		// if the input was a directory, however, we need to find its children

		char *const dirpath = path; // (changing the name of the variable to ease legibility)

		// firstly, open the directory and get a pointer to a `DIR` object
		//	note: we can't get any info from `DIR`, it's use is to be passed into other functions
		DIR *p_dir = opendir(dirpath);

		// if we can't open the directory, note that there aren't any children, and move on
		if (p_dir == NULL) {
			// set the number of children to -1, so we know the difference between having 0 children,
			//	and not being able to open the directory
			p_fsobj->f->child_count = -1;

			printError(errno);
			continue;
		}

		// allocate some memory for an arbitrary number of children, with the intention that
		//	we'll realloc if we need more memory later
		int32_t child_alloc_count = INIT_CHILD_COUNT;
		FileStat *children = ecalloc(child_alloc_count, sizeof(FileStat));

		/* ———————————————————————————————————————————————————————————— */

		// iterate through the directory until you run out of children (or there's an error)
		const struct dirent *p_child;
		while (( p_child = readdir(p_dir) ) != NULL) {
			// if this child has the name ".", then it's not a child, but the dir itself
			if (strcmp(p_child->d_name, DOTDIR) == 0) {
				// get the few pieces of information that we care about from the `dirent` object
				// note: we're not keeping `d_name` or `d_namlen`, since these would just
				//	return "." and 1 respectively, which isn't much help to us
				p_fsobj->type = p_child->d_type;
				p_fsobj->inum = p_child->d_ino;

				continue; // continue - the rest of the information we need is already in `p_fsobj->s`
			}

			// with the output structure I'm building, I don't think it makes sense to show `..`
			//	if I want to add an option to keep it later, I can just add it to this condition
			if (strcmp(p_child->d_name, "..") == 0) continue;
			// note: when I add the `-a` and `-A` options later, this is where I'll add a check for them

			/* ———————————————————————————————————————————————————————————— */

			// keep track of the number of children in the dir
			if (++p_fsobj->f->child_count > child_alloc_count) {
                const int32_t old_alloc_count = child_alloc_count; // save the old capacity before multiplying

				// if the number of children (after we increment it) is more than we have space for,
				//	then increase the number of children we have space for, by a factor of 1.5.
				// 1.5 is the optimal multiplier to make sure we don't over-allocate memory, but also so that
				//	we aren't constantly allocating it either
				MULT_BY_1_5(child_alloc_count);

				// re-allocate the memory. note that `[e]realloc` will free the original pointer and hard exit if it
				//	fails, so we don't have to worry about memory leaks by overwriting the original pointer
				children = erealloc(children, sizeof(FileStat) * child_alloc_count);

				// zero out the new memory that we were just allocated
				//	this isn't strictly necessary, but it could prove rly useful for debugging
				//	(I might remove it later if I don't think it's needed)
				memset(children + old_alloc_count, 0, sizeof(FileStat) * (child_alloc_count - old_alloc_count));
			}

			printf("\t%s/%s\n", dirpath, p_child->d_name);
		}

		closedir(p_dir);
	}

	/* ———————————————————————————————————————————————————————————— */

	// if none of the inputted directories were valid, exit with failure
	if (!any_valid_input) return EXIT_FAILURE;

	/* ——————————————————————————————————————————————————————————————————————————————————————————— */

	for (int i = 0; i < file_count; i++) {
		FileStat *fsobj = fs_input_arr[i];
		if (fsobj != NULL) efree(fsobj);
	}

	// checkMemLeak();
	return EXIT_SUCCESS;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

static inline const char *getArgv0(const int argc, char *restrict argv[]) {
	if ((argc < 1) || (argv[0] == NULL) || (argv[0][0] == '\0')) return PROGRAM_NAME;

	const char *basename = strrchr(argv[0], '/');
	if (basename != NULL) return basename + 1;

	return argv[0];
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
