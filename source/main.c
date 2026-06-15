/**
 * @mainpage
 * @file main.c
 */

#include <string.h>

#include "info/info.h"
#include "sorting/sort.h"
#include "options/options.h"

#include "features/path/path.h"
#include "features/time/time.h"

int main(const int argc, const char *argv[]) {

	/* —— Find Target Directory —————————————————————————————————————————————————————————————————— */

	char target_dir[MAX_NAME_LEN];

	// Get the target directory from the user's input
	DIR *dir_obj = getDirectory(target_dir, argc, argv);
	if (dir_obj == NULL) return 1;

	/* —— Get Current Time ——————————————————————————————————————————————————————————————————————— */

	// Find the current time and make it available globally
	initTime();

	/* —— Get File Info from `stat` —————————————————————————————————————————————————————————————— */

	FileInfo dirs[MAX_FILES_IN_DIR], files[MAX_FILES_IN_DIR];
	int dir_count, file_count;

	// Run the `stat` and `lstat` syscalls, and start parsing the files' information
	getAllFileInfo(
		dirs, files,
		&dir_count, &file_count,
		dir_obj, target_dir
	);

	/* —— Sort Files if Dirs First ——————————————————————————————————————————————————————————————— */

	if (SORT_DIRS_FIRST) {
		sortFiles( dirs,  &dir_count);
		sortFiles(files, &file_count);
	}

	/* —— Combine Dirs & Files ——————————————————————————————————————————————————————————————————— */

	const int count = dir_count + file_count;
	FileInfo all_files[count];

	memcpy(all_files,			   dirs,  dir_count * sizeof(FileInfo));
	memcpy(all_files + dir_count, files, file_count * sizeof(FileInfo));

	/* —— Sort Files if not Dirs First ——————————————————————————————————————————————————————————— */

	if (!SORT_DIRS_FIRST) sortFiles(all_files, &count);

	/* —— Find Widths of Fields —————————————————————————————————————————————————————————————————— */

	// Find the min lens of each field, and set each field's printf format string
	initFormatting();

	// Run through each of the fields and find its maximum length
	getFieldLengths(all_files, &count);

	/* —— Print Headers —————————————————————————————————————————————————————————————————————————— */

	// Print the target directory, as a title (casting it to void, since it's not rly that important)
	(void) printAbsolutePath(target_dir);

	// Print the fields' headers
	if (DO_HEADER) printHeader();

	/* —— Print File Info ———————————————————————————————————————————————————————————————————————— */

	// Print the fields' actual information
	printFields(all_files, &count);

	/* ——————————————————————————————————————————————————————————————————————————————————————————— */

	return 0;
}
