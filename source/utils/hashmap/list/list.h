/// @file list/list.h

#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct l__llist *LList;
typedef ssize_t idx_t;

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

LList ll_init(void);
void ll_free(LList list);

void **ll_to_arr(const LList list);
LList ll_from_arr(const void *const *const array, const size_t len);

idx_t ll_append(LList list, const void *const val);
size_t ll_len(const LList list);

const void *ll_get(const LList list, const idx_t idx);
const void *ll_pop(LList list, const idx_t idx);

const void *l__iter(const LList list, const bool do_reset);
void ll_dump(const LList list, const char *const fmt);

#define ll_iter(list)	l__iter((const LList)(list), false)
#define ll_iter_reset()	l__iter((const LList)( -1 ), true )
// note: `-1` is just an arbitrary value - it could be anything, since it's never checked when `do_reset` is `true`

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !LIST_H */
