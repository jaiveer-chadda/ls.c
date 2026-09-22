/// @file utils/hashmap/hashmap.h

#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "./list/list.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct hm__hashmap *HashMap;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

HashMap hm_init(void);
void hm_free(HashMap map);

void  hm_add(HashMap map, const void *const key, const size_t ksize, const void *const value);
void *hm_get(HashMap map, const void *const key, const size_t ksize);
void *hm_pop(HashMap map, const void *const key, const size_t ksize);

#define hm_adds(map, key, value) hm_add((map), &(key), sizeof(key), (value))
#define hm_gets(map, key)		 hm_get((map), &(key), sizeof(key))
#define hm_pops(map, key)		 hm_pop((map), &(key), sizeof(key))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !HASHMAP_H_ */
