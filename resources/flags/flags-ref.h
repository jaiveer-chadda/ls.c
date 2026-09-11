
#include <sys/stat.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— All Valid MacOS Flags ———————————————————————————————————————————————————————————————————————————————————————— */

#define _ UF_NODUMP     0x00000001 _______1 // \e[92m
#define _ UF_IMMUTABLE  0x00000002 _______2 // \e[94m
#define _ UF_APPEND     0x00000004 _______4 // \e[93m
#define _ UF_OPAQUE     0x00000008 _______8 // \e[97m
#define _ UF_COMPRESSED 0x00000020 ______2_ // \e[95m
#define _ UF_TRACKED    0x00000040 ______4_ // \e[91m
#define _ UF_DATAVAULT  0x00000080 ______8_ // \e[07m
#define _ UF_HIDDEN     0x00008000 ____8___ // \e[02m

#define _ SF_ARCHIVED   0x00010000 ___1____ // \e[32m
#define _ SF_IMMUTABLE  0x00020000 ___2____ // \e[34m
#define _ SF_APPEND     0x00040000 ___4____ // \e[33m
#define _ SF_RESTRICTED 0x00080000 ___8____ // \e[31m
#define _ SF_NOUNLINK   0x00100000 __1_____ // \e[36m
#define _ SF_FIRMLINK   0x00800000 __8_____ // \e[35m
#define _ SF_DATALESS   0x40000000 4_______ // \e[47m

#define _ UF_ALL_FLAGS  0x000080ef ____8_ef
#define _ SF_ALL_FLAGS  0x409f0000 4_9f____
#define _ AF_ALL_FLAGS  0x409f80ef 4_9f8_ef

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Unique MacOS ————————————————————————————————————————————————————————————————————————————————————————————————— */

#define _ UF_NODUMP     0x00000001 _______1 // \e[92m
#define _ UF_IMMUTABLE  0x00000002 _______2 // \e[94m
#define _ UF_APPEND     0x00000004 _______4 // \e[93m
#define _ UF_OPAQUE     0x00000008 _______8 // \e[97m
#define _ UF_COMPRESSED 0x00000020 ______2_ // \e[95m
#define _ UF_TRACKED    0x00000040 ______4_ // \e[91m
#define _ UF_DATAVAULT  0x00000080 ______8_ // \e[07m
#define _ UF_HIDDEN     0x00008000 ____8___ // \e[02m √

#define _ SF_ARCHIVED   0x00010000 ___1____ // \e[32m
#define _ SF_IMMUTABLE  0x00020000 ___2____ // \e[34m
#define _ SF_APPEND     0x00040000 ___4____ // \e[33m
#define _ SF_RESTRICTED 0x00080000 ___8____ // \e[31m
#define _ SF_NOUNLINK   0x00100000 __1_____ // \e[36m ×
#define _ SF_FIRMLINK   0x00800000 __8_____ // \e[35m √
#define _ SF_DATALESS   0x40000000 4_______ // \e[47m √

/* ——————————————————————————————————————————————— */

#define _ UF_HIDDEN     0x00008000 ____8___ // \e[02m
#define _ SF_FIRMLINK   0x00800000 __8_____ // \e[35m
#define _ SF_DATALESS   0x40000000 4_______ // \e[47m

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— All Possible Flags ——————————————————————————————————————————————————————————————————————————————————————————— */

#define _ UF_NODUMP     0x00000001 _______1
#define _ UF_IMMUTABLE  0x00000002 _______2
#define _ UF_APPEND     0x00000004 _______4
#define _ UF_OPAQUE     0x00000008 _______8
#define _ UF_NOUNLINK   0x00000010 ______1_ [bsd only - not on macos]
#define _ UF_COMPRESSED 0x00000020 ______2_
#define _ UF_TRACKED    0x00000040 ______4_
#define _ UF_DATAVAULT  0x00000080 ______8_
#define _ __UNDEFINED   0x00000100 _____1__ [left undefined in specification]
#define _ __UNDEFINED   0x00000200 _____2__ [left undefined in specification]
#define _ __UNDEFINED   0x00000400 _____4__ [left undefined in specification]
#define _ __UNDEFINED   0x00000800 _____8__ [left undefined in specification]
#define _ __UNDEFINED   0x00001000 ____1___ [left undefined in specification]
#define _ __UNDEFINED   0x00002000 ____2___ [left undefined in specification]
#define _ __UNDEFINED   0x00004000 ____4___ [left undefined in specification]
#define _ UF_HIDDEN     0x00008000 ____8___

#define _ UF_ALL_MACOS  0x000080ef ____8_ef
#define _ UF_ALL_BSD    0x000080ff ____8_ff

/* ——————————————————————————————————————————————— */

#define _ SF_ARCHIVED   0x00010000 ___1____
#define _ SF_IMMUTABLE  0x00020000 ___2____
#define _ SF_APPEND     0x00040000 ___4____
#define _ SF_RESTRICTED 0x00080000 ___8____
#define _ SF_NOUNLINK   0x00100000 __1_____
#define _ SF_SNAPSHOT   0x00200000 __2_____ [bsd only - not on macos]
#define _ __UNKNOWN     0x00400000 __4_____ [unknown]
#define _ SF_FIRMLINK   0x00800000 __8_____
#define _ __UNKNOWN     0x01000000 _1______ [unknown]
#define _ __UNKNOWN     0x02000000 _2______ [unknown]
#define _ __UNKNOWN     0x04000000 _4______ [unknown]
#define _ __UNKNOWN     0x08000000 _8______ [unknown]
#define _ __UNKNOWN     0x10000000 1_______ [unknown]
#define _ __UNKNOWN     0x20000000 2_______ [unknown]
#define _ SF_DATALESS   0x40000000 4_______

#define _ SF_ALL_MACOS  0x409f0000 4_9f____
#define _ SF_ALL_BSD    0x40bf0000 4_bf____

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
