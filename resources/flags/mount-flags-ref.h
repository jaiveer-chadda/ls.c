// mount flags
// ‾‾‾‾‾‾‾‾‾‾‾

// MNT_RDONLY			0x00000001	-v-	A read-only filesystem
// MNT_SYNCHRONOUS		0x00000002	-v-	Filesystem is written to synchronously
// MNT_NOEXEC			0x00000004	-v-	Can't exec from filesystem
// MNT_NOSUID			0x00000008	-v-	Setuid bits are not honored on this filesystem
// MNT_NODEV			0x00000010	-v-	Don't interpret special files
// MNT_UNION			0x00000020	-v-	Union with underlying filesysten
// MNT_ASYNC			0x00000040	-v-	Filesystem written to asynchronously
// MNT_CPROTECT			0x00000080	-v-	Filesystem supports per-file encrypted data protection
// MNT_EXPORTED			0x00000100	-v-	Filesystem is exported
// MNT_REMOVABLE		0x00000200	-?-	Denotes storage which can be removed from the system by the user.
// MNT_QUARANTINE		0x00000400	-?-	MAC labeled / "quarantined" flag
//	UNKNOWN				0x00000800	-x-
// MNT_LOCAL			0x00001000	-v-	Filesystem is stored locally
// MNT_QUOTA			0x00002000	-v-	Quotas are enabled on this filesystem
// MNT_ROOTFS			0x00004000	-v-	This filesystem is the root of the filesystem
// MNT_DOVOLFS			0x00008000	-v-	Filesystem supports volfs
// MNT_DONTBROWSE		0x00100000	-v-	Filesystem is not appropriate path to user data
// MNT_IGNORE_OWNERSHIP	0x00200000	-v-	VFS will ignore ownership info on filesystem objects (MNT_UNKNOWNPERMISSIONS)
// MNT_AUTOMOUNTED		0x00400000	-v-	Filesystem was mounted by automounter
// MNT_JOURNALED		0x00800000	-v-	Filesystem is journaled
// MNT_NOUSERXATTR		0x01000000	-?-	Don't allow user extended attributes
// MNT_DEFWRITE			0x02000000	-v-	Filesystem should defer writes
// MNT_MULTILABEL		0x04000000	-v-	MAC support for individual labels
// MNT_NOFOLLOW			0x08000000	-?-	don't follow symlink when resolving mount point
// MNT_NOATIME			0x10000000	-?-	disable update of file access time
//	UNKNOWN				0x20000000	-x-
// MNT_SNAPSHOT			0x40000000	-?-	The mount is a snapshot
// MNT_STRICTATIME		0x80000000	-?-	enable strict update of file access time
