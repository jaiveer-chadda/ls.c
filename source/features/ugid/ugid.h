/// @file features/ugid/ugid.h

#ifndef UGID_INITIALISED
#define UGID_INITIALISED

char  *getUser(const uid_t uid);
char *getGroup(const gid_t gid);

#endif /* !UGID_INITIALISED */
