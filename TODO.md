<!--
@file TODO.md
-->

# TODO

-----------------------------------------------------------------------------------------------------------------------

## Priority Features

### Visual

#### Sorting
- [x] Sort files by name
- [x] Sort entires with directories first
- [ ] Implement a way to sort them by any category
  - Probably with the `-s | --sort-by <field>` flag

#### Colour Filenames
- [x] Colour filenames based on their types / permissions / other fields
  - [ ] Read colours from `$LSCOLORS` ond/or `$LS_COLORS`
  - [x] Set the defaults as:
    - [x] normal file         ` .--------- ` `\e[37m`
    - [x] directory           ` d--------- ` `\e[36m`
    - [x] symlink             ` l--------- ` `\e[35m`
    - [x] executable          ` .--x--x--x ` `\e[31m`
    - [x] named pipe          ` p--------- ` `\e[33m`
    - [x] socket              ` s--------- ` `\e[32m`
    - [x] char device         ` c--------- ` `\e[43m`
    - [x] block device        ` b--------- ` `\e[46m`
    - [x] other-writable dir  ` .-------w- ` `\e[42m`
    - [x] setuid bit set      ` .--s------ ` `\e[41m`
    - [x] setgid bit set      ` .-----s--- ` `\e[45m`
    - [x] sticky bit set      ` .--------t ` `\e[44m`
    - [x] dataless file/dir                  `\e[47m`
    - [x] whiteout            ` w--------- ` `\e[07m`
- [ ] Colour filenames based on their extensions
  - [ ] either use the info from `$EZA_COLORS`,
  - [ ] or make my own variable to store colours in

#### Colour Other Fields

##### `mode_str`
- [x] colour the first bit the same colour as its filetype
- [x] colour each other bit based on whether its:
  - [x] read        ` .r--r--r-- ` `\e[92m`
  - [x] write
    - [x] user/grp  ` .-w---w--- ` `\e[93m`
    - [x] other     ` .-------w- ` `\e[42m`
  - [x] exec
    - [x] file      ` .--x--x--x ` `\e[31m`
    - [x] dir       ` d--x--x--x ` `\e[91m`
  - [x] setuid
    - [x] exec      ` .--s------ ` `\e[41m`
    - [x] non-exec  ` .--S------ ` `\e[101m`
  - [x] setgid
    - [x] exec      ` .-----s--- ` `\e[45m`
    - [x] non-exec  ` .-----S--- ` `\e[105m`
  - [x] sticky
    - [x] exec      ` .--------t ` `\e[44m`
    - [x] non-exec  ` .--------T ` `\e[104m`

##### `nlink`
- [x] there should be a default colour `\e[36m`, and a colour for regular files with 2+ hardlinks `\e[105m`
- [x] files with 2+ hardlinks should also have other visual flourishes on their filenames  `\e[21m \e[105m`

##### `size`
- [ ] a gradient of colours for different sized files
  - probably from `\e[92m` to `\e[31m`

##### `usr_name`
- [ ] a different colour for:
  - [ ] you   `#807ded`
  - [ ] root  `\e[31m`
  - [ ] other `\e[93m`

##### `grp_name`
- [ ] a different colour for:
  - [ ] yours   `\e[93m`
  - [ ] root's  `\e[94m`
  - [ ] others' `\e[91m`

##### `flag_str`
- [ ] maybe a different colour for each type of flag??
  - [ ] nodump      `\e[35m`
  - [ ] uimmutable  `\e[92m`
  - [ ] uappend     `\e[93m`
  - [ ] opaque      `\e[97m`
  - [ ] compressed  `\e[91m`
  - [ ] tracked     `\e[94m`
  - [ ] datavault   `\e[100m`
  - [ ] hidden      `\e[02m`
  - [ ] archived    `\e[42m`
  - [ ] simmutable  `\e[32m`
  - [ ] sappend     `\e[33m`
  - [ ] restricted  `\e[41m`
  - [ ] nounlink    `\e[46m`
  - [ ] dataless    `\e[07m`
- [ ] and then a grey hyphen for no flags

##### `time_str`
- [x] have a different colour for each named time:
  - [x] Now               `\e[38;2;203;210;242m`
  - [x] 1 min. ago        `\e[38;2;193;203;240m`
  - [x] 2 mins ago        `\e[38;2;188;199;240m`
  - [x] 3 mins ago        `\e[38;2;178;192;238m`
  - [x] Today             `\e[38;2;152;174;234m`
  - [x] Yesterday         `\e[38;2;133;161;228m`
  - [x] 2 Days Ago        `\e[38;2;100;145;225m`
- [x] and a different time for other time periods which don't have names
  - [x] This month        `\e[38;2;056;116;212m`
  - [x] This year         `\e[38;2;035;106;204m`
  - [x] Before this year  `\e[38;2;005;093;181m`
  - [ ] Birth time??
  - [ ] [No time]

#### Headers
- [x] Colourise? and underline headers

#### Hidden Files
- [x] Dim the filenames of any files starting with a `.`

### Fields

#### Permissions
- [ ] Add an ampersand `@` to see whether a file has extended permissions or not

#### Symlinks
- [ ] Figure out whether a symlink is valid or not, and adjust the visualisation based on that

### Features

#### Alphanum Sorting
- [x] Make sorting work in a way where numbers are sorted logically, and case is insensitive otherwise

#### Escape control chars
- [ ] Replace any control characters with their C/Hex equivalents
- [ ] Probably also highlight them in some colour
  - [ ] But that being said, I'll have to make sure that their escaped colours
    don't clash with any other colours being used

#### Options
- [ ] Implement an options/flags system to turn various features on/off

-----------------------------------------------------------------------------------------------------------------------

## Intend to Add

### Visual

#### Width
- [ ] Find a way to adjust which fields show/dont show
  - [ ] Make it based on the `$COLUMNS` env var

#### Line Separators
- [ ] Make it so that files with more than 3? 5? `[-–—─]`s in a row get a special format, and act as separators

### Fields

#### Git Integration

##### File Statuses
- [ ] Figure out how to check a git repo to see which files have been:
  - [ ] Modified
  - [ ] Added
  - [ ] Deleted
  - [ ] Renamed
  - [ ] Ignored

##### Branch Information
- [ ] Which branch we're on
- [ ] And whether the current branch is behind/ahead of the remote

#### Apple Integration

##### Apple Aliases
- [ ] Figure out how to find the target of an Apple alias file.
  - [ ] It'll probably have to be done with some version of the stuff I'm using in the `alisma` program
    - luckily though, `.swift` files can be compiled into binaries, which should cut down on the time it takes to
      fork out to them
    - the only issue I can see though, is the fact that I don't actually know whether a file is an Apple alias unless
      I use `/usr/bin/file`

##### Apple Comments
- [ ] Add some sort of lookup/integration with Apple's file comments system
  - [ ] Either do it with AppleScript,
    - once again, luckily, AppleScript has a compiled file format `.scpt`, but I honestly don't rly trust its effiency
  - [ ] or find a way to parse `.DS_Store`

##### Apple Tags
- [ ] Implement a way to visualise Apple's tags
  - i.e. the ones they use in Finder to colour/tag folders
  - I don't know how I'm gonna get these, but if I had to guess, it would be some AppleScript program

#### VSCode Integration

- [ ] If there isn't a colour defined for a directory, then look into that dir's `.vscode` directory,
  into the `settings.json` file, and see if there's a field called `peacock.color`.
  - [ ] if so, then use that colour to highlight the directory

#### Reimplement `/usr/bin/file`
- [ ] Find a way to use the same process as `/usr/bin/file` to find out what *specific* type of file smth is
  - i.e. running: `file ~zdd/.zshrc`
  - yields: `.../zsh/.zshrc: a /usr/bin/env zsh script text executable, Unicode text, UTF-8 text`
    - which tells you more info about the file that you would have gotten on your own
  - If I had to guess how it worked
    - it probably checks the file's binary header, to see if it has any special info
    - and if that fails, it'll check the first line of the file to see if it has a shebang

### Features

#### Recursive Directory Searching
- [ ] Implement a very similar feature to `eza`'s tree search, 
  - in which you can see the recursive tree structure of a directory up to a certain depth

-----------------------------------------------------------------------------------------------------------------------

## Would be Nice

### Visual

#### Icons
- [ ] Implement file/folder icons similar to `eza`'s implementation
  - Initially I might have to trawl through `eza`'s source code and steal their defaults before I write my own

### Features

#### Compression
- [ ] See if there's a way where, if some fields have too much extra space to their sides,
  - they can be squished together to fit nicer, and take up less room

```sh
# spell:disable
# e.g.:
...
drwxr-xr-x  5    160 jv   staff -              2 Days Ago  14:52  archive/
drwxr-xr-x  3     96 jv   staff -                            Now  out/
drwxr-xr-x  5    160 jv   staff -           Thu 11 Jun 26  00:30  resources/
drwxr-xr-x  14   448 jv   staff -               Yesterday  23:58  source/
.rw-r--r--  1     73 jv   staff track,hiddn                  Now  .gitignore
.rw-r--r--  1   2.2k jv   staff track                        Now  TODO.md
brw-r--r--  1    1,0 root staff -           Thu 11 Jun 26  01:34  _test_block_dev
crw-r--r--  1    1,0 root staff -           Thu 11 Jun 26  01:34  _test_char_dev
.rwxr--r--  1  12.3k jv   admin track          2 Days Ago  23:51  _test_exe*
lrwxr-xr-x  1     19 jv   staff -               Yesterday  14:36  _test_link@ --> ~/.zprofile
lrwxr-xr-x  1     28 jv   staff -               Yesterday  15:58  _test_link_3@ --> ~/.config/bash/bash_*

# becomes something like:
...
drwxr-xr-x  5   160 jv   staff -         2 Days Ago  14:52  archive/
drwxr-xr-x  3    96 jv   staff -                       Now  out/
drwxr-xr-x  5   160 jv   staff -      Thu 11 Jun 26  00:30  resources/
drwxr-xr-x  14  448 jv   staff -          Yesterday  23:58  source/
.rw-r--r--  1    73 jv   staff track,hiddn             Now  .gitignore
.rw-r--r--  1  2.2k jv   staff track                   Now  TODO.md
brw-r--r--  1   1,0 root staff -      Thu 11 Jun 26  01:34  _test_block_dev
crw-r--r--  1   1,0 root staff -      Thu 11 Jun 26  01:34  _test_char_dev
.rwxr--r--  1 12.3k jv   admin track     2 Days Ago  23:51  _test_exe*
lrwxr-xr-x  1    19 jv   staff -          Yesterday  14:36  _test_link@ --> ~/.zprofile
lrwxr-xr-x  1    28 jv   staff -          Yesterday  15:58  _test_link_3@ --> ~/.config/bash/bash_*
# spell:enable
```

-----------------------------------------------------------------------------------------------------------------------

<!-- spell:word uimmutable uappend -->
