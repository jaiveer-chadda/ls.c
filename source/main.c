/**
 * @mainpage
 * @file main.c
 */

#include "info/info.h"

#include "path/path.h"
#include "time/time.h"
#include "options/options.h"

int main(const int argc, const char *argv[]) {
	char target_dir[MAX_NAME_LEN];

	// Get the target directory from the user's input
	DIR *directory = getDirectory(target_dir, argc, argv);
	if (directory == NULL) return 1;

	/* ——————————————————————————————————————————————————————————————————————— */

	// Find the current time and make it available globally
	initTime();

	/* ——————————————————————————————————————————————————————————————————————— */

	FileInfo all_files[MAX_FILES_IN_DIR];
	int count = 0;

	// Run the `stat` and `lstat` syscalls, and start parsing the files' information
	getAllFileInfo(all_files, &count, directory, target_dir);

	/* ——————————————————————————————————————————————————————————————————————— */

	// Find the min lens of each field, and set each field's printf format string
	initFormatting();

	// Run through each of the fields and find its maximum length
	getFieldLengths(all_files, &count);

	/* ——————————————————————————————————————————————————————————————————————— */

	// Print the target directory, as a title to the list
	// (casting to void, since we don't rly care whether the path is printed)
	(void) printAbsolutePath(target_dir);

	// Print the fields' headers
	if (DO_HEADER) printHeader();

	/* ——————————————————————————————————————————————————————————————————————— */

	// Print the fields' actual information
	printFields(all_files, &count);

	return 0;
}
