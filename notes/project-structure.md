# Project Structure

## Take & Parse User Input

> - Set all user flags/options as global vars
> - Create an array of every file which needs to be analysed

- Take the user input
  - first find all of the options/flags the user gave
    - store the options' results in global variables
  - then take the remaining inputs, and figure out:
    - which ones are dirs, and
    - which ones are files

- Get all the directories that the user inputted
  - create an array of `DirEntry` structs containing the dirs, with the structs containing:
    - a `DIR *` object
    - the dir's display path
      - should be the exact way the user inputted it
        - (usually its basename / relative path)
      - unless the option `--do-absolute-paths` is given
        - in which case it should be the absolute path
    - the dir's absolute path
      - this should be its path without any symlinks resolved
      - unless the option `--follow-dir-links` is given
    - an array of sub-file `FileEntry` structs

  - then iterate through the dirs, and find every file inside each of those dirs
    - hold each of the files in a `FileEntry` struct containing
      - a pointer to the file's parent's `DirEntry`
      - a `dirent *` object
      - the file's display path
      - the file's absolute path
      - each of the fields currently stored in `FileInfo`
    - then add each of those files to their parent dir's struct's array

- Get all the files that the user inputted
  - The same way the directories entered have a `DirEntry`, which stores the files under them
    - the inputted files will also have a phantom parent `DirEntry`,
    - which stores each of the inputted files in `FileEntry` structs

- If there's no user input (after the options),
  - then set `ALL_DIRECTORIES[]` to contain `$PWD`

## Get Files' Info

- ...
