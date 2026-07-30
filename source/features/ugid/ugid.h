/// @file features/ugid/ugid.h

#ifndef UGID_INITIALISED
#define UGID_INITIALISED

void  getUser(char *usr_str, const uid_t uid);
void getGroup(char *grp_str, const gid_t gid);

#endif /* !UGID_INITIALISED */
