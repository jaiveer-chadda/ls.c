/// @file model/stat-model.h

/// An arbitrary upper bound on how many file's we're going to accept.
#define MAX_FILES_IN_DIR 1 << 11

/// The maximum number of possible user and super user flags on MacOS.
#define MAX_FLAG_NUM 17
/// The longest flag name on MacOS ("uimmutable") + 1.
#define MAX_FLAG_LEN 11

/** Given that the maximum filesize on MacOS is `( 1 << ( ( 1 << 6 ) - 1 ) ) - 1` == `2^63 - 1`,
 * the longest string would be "9,223,372,036,854,775,806 b" (27 chars) + 1. */
#define MAX_SIZE_LEN 28
#define MAX_UGID_LEN 1 << 8

typedef char type_t;
typedef char name_t[MAX_NAME_LEN];
typedef char path_t[MAX_PATH_LEN];
typedef unsigned int flag_t;

typedef char modestr[MAX_MODE_LEN];
typedef char timestr[MAX_TIME_LEN];
typedef char ugidstr[MAX_UGID_LEN];
typedef char flagstr[MAX_FLAG_LEN];
typedef char sizestr[MAX_SIZE_LEN];

typedef struct {
	name_t name;
	path_t path;
	type_t suffix;

	nlink_t nlink;
	dev_t dev_no;
	ino_t inode;

	flag_t flags;	flagstr flags_strs[MAX_FLAG_NUM];
	mode_t mode;	modestr mode_str;
	off_t size;		sizestr size_str;

	uid_t uid;		ugidstr usr_name;
	gid_t gid;		ugidstr grp_name;

	time_t atime;	timestr atime_str;
	time_t mtime;	timestr mtime_str;
	time_t ctime;	timestr ctime_str;
	time_t btime;	timestr btime_str;
} FileInfo;
