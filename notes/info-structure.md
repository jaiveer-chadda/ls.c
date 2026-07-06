# Info Structure

## Arrays <!--—————————————————————————————————————————————————————————————————————————————————————————————————————-->

- `DirEntry ALL_DIRECTORIES[]`
  - an entry for each dir inputted by the user
  - and one extra entry to hold all the *files* inputted by the user

- `FileEntry ALL_FILES[]` [maybe?]
  - an entry for each file to be shown

## Structs <!--————————————————————————————————————————————————————————————————————————————————————————————————————-->

- MajMinNo
  - `u_int maj`
  - `u_int min`

- Width
  - `u_int raw`
  - `u_int str`

<!--———————————————————————————————————————————————————————————————————-->

- DirEntry
  - `DIR      * dir_obj`       : Directory Object
  - `name_t     name`          : Display Path
  - `path_t     path`          : Absolute Path
  - `FileEntry  sub_files[]`   : Array of files it contains

- FileEntry
  - `DirEntry * parent`        : parent dir
  - `dirent   * file_obj`      : entry object

  - and then all the fields of the current `FileInfo` struct, in their own, newly-made structs:

  - `FileInfo   file`
    - `name_t      name`       : display path
    - `path_t      path`       : absolute path
    - `bool        can_stat`   : whether we can `stat()` the file or not
    - `type_t      suffix`     : the suffix that should be appended to the filename
    - `FileColour  file_col`   : how the file should be coloured
    - `Width       width`      : the widths of this field

  - `LinkInfo   link`
    - `bool        is_valid`   : whether this file's link points to a valid file
    - `bool        is_valid`   : whether this file's link points to a valid file
    - `FileInfo    link_to`    : a `FileInfo` object of the file that this link points to
    - `Width       width`      : the widths of this field

  - `InodeInfo  inode`
    - `ino_t       ino`        : the file's inode
    - `Width       width`      : the widths of this field

  - `DeviceInfo device`
    - `dev_t       no`         : the device number of the device this file is on
    - `MajMinNo    majmin`     : the maj/min parts of the `dev_no`
    - `Width       width`      : the widths of this field

  - `FlagInfo   flags`
    - `flag_t      raw`        : the raw flag hex string
    - `flagid_t    flags[]`    : an array of each of the file's flags
    - `flagstr     str`        : the formatted string with all of the flags
    - `Width       width`      : the widths of this field

  - `ModeInfo   mode`
    - `mode_t      raw`        : the raw octal mode
    - `modestr     str`        : the formatted string in the unix mode format
    - `bool        has_xattr`  : whether the file has extended attributes
    - `bool        has_acl`    : whether the file has an access control list
    - `Width       width`      : the widths of this field

  - `SizeInfo   size`
    - `off_t       raw`        : the raw size of the file
    - `MajMinNo    majmin`     : the major & minor sizes of the file, if they exist
    - `char        unit`       : the unit size (b, k, M, etc.)
    - `SizeColour  colours[2]` : either the size/unit colours, or the major/minor colours
    - `Width       width`      : the widths of this field

  - `UserInfo   user`
    - `uid_t       id`         : the raw uid of the file's owner
    - `ugidstr     uname`      : the stringified user name
    - `UGIDColour  colour`     : colour of the user
    - `Width       width`      : the widths of this field

  - `GroupInfo  group`
    - `gid_t       id`         : the raw gid of the file's group
    - `ugidstr     name`       : the stringified group name
    - `UGIDColour  colour`     : colour of the group
    - `Width       width`      : the widths of this field

  - `TimeInfo   time`
    - `time_t      raw`        : the raw modificaton time
    - `timestr     str`        : the strftime-formatted time
    - `TimeColour  colour`     : the colour to show the time in
    - `Width       width`      : the widths of this field

<!--———————————————————————————————————————————————————————————————————————————————————————————————————————————————-->
