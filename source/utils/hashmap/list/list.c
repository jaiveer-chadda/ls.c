/// @file utils/hashmap/list/list.c

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./list.h"

/* —— Macro Definitions ———————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @brief Check if the value `check` is NULL. If it is, print a warning and return `ret`.
 *
 * Note that `ret` can be left empty (`RETURN_IF_NULL(list,)`) when using returning from a `void` function.
 */
#define RETURN_IF_NULL(check, ret) do {	\
	if ((check) == NULL) {				\
		fprintf(stderr,					\
			"%s: warning: %s\n",		\
			__func__, strerror(errno)	\
		);								\
		return ret;						\
	}									\
} while (0)

/* —————————————————————————————————————————————————— */

/**
 * @brief Print an error and hard-exit the program.
 *
 * Usually used for index out-of-range errors, which aren't realistically recoverable.
 * If I need them to be recoverable in the future, this could turn into a similar macro to `RETURN_IF_NULL`.
 */
#define EXIT_FATAL(caller, fmt, ...) do {		\
	fprintf(stderr, ("%s: error: " fmt "\n"),	\
		(caller) __VA_OPT__(,) __VA_ARGS__		\
	);											\
	exit(EXIT_FAILURE);							\
} while (0)

/** @brief Print an out-of-range error, specifying the length and index, then exit. */
#define IDX_OOR_ERROR(caller, llist, index) \
	EXIT_FATAL(caller, "index %ld is out of range for list of length %lu", (index), (llist)->len)

/* —— Typedefs & Structs ——————————————————————————————————————————————————————————————————————————————————————————— */

typedef struct LLItem LLItem;

/**
 * @struct l__llist
 * @brief A struct representing a linked list.
 *
 * ---
 *
 * This struct can only be directly accessed from in this file - the functions below provide functionality for all
 *	actions that could be performed on this struct by an external user.
 *
 * Usually referenced as `LList` (`typedef struct l__llist *LList`), which points to an instance of this struct.
 */
struct l__llist {
	LLItem *head, *tail;
	size_t len;
};

/**
 * @struct LLItem
 * @brief A struct representing an individual item in a linked list.
 *
 * @var LLItem::next A pointer to the next item in the linked list. `NULL` if this is the last item.
 * @var LLItem::val	 A pointer to the data stored by this element of the linked list.
 */
struct LLItem {
	LLItem *next;
	const void *val;
};

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_len() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @fn ll_len
 * @brief Get the length of `list`.
 *
 * While usually, the struct values stored behind the `LList` pointer can only be accessed from `list.c`, a user may
 *	need to know the linked list's length, so this function exists to provide an interface to do so.
 *
 * @param list The linked list of which to get the length.
 * @return The length of `list`.
 *
 * @throw `RETURN_IF_NULL` – Prints a warning to `stderr` if list is `NULL`, and returns `-1`.
 * @note `Θ(1)`
 */
size_t ll_len(const LList list) {
	RETURN_IF_NULL(list, -1);
	return list->len;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_init() ———————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @fn ll_init
 * @brief Initialise a new linked list.
 *
 * This function allocates memory for the linked list, and must be freed with `ll_free()`.
 *
 * @return An initialised linked list object. `NULL` on failure.
 *
 * @throw `RETURN_IF_NULL` – Prints a warning to `stderr` if memory allocation fails. Returns `NULL`.
 * @note `Θ(1)`
 */
LList ll_init(void) {
	LList list = calloc(1, sizeof(struct l__llist));
	RETURN_IF_NULL(list, NULL);

	return list;
}

/* —— ll_free() ————————————————————————————————————— */

/**
 * @fn ll_free
 * @brief Free a linked list and all its constituent parts.
 *
 * Frees all `LLItem` elements contained within the linked list, and then frees the list itself.
 *
 * @param list The linked list to free.
 * 
 * @throw `RETURN_IF_NULL` – Prints a warning to `stderr` if the inputted list is `NULL`.
 * @note `Θ(n)`, where `n ∝ list.len`
 */
void ll_free(LList list) {
	// if the list is NULL, then print an error and return
	RETURN_IF_NULL(list,);

	LLItem **item_ptrs = malloc(list->len * sizeof(LLItem*));
	LLItem *current = list->head;

	// we have to iterate through the list and save all the pointers that need to be freed
	//	this could also be done recursively, but honestly, this is easier.
	for (size_t i = 0; i < list->len; i++) {
		item_ptrs[i] = current;
		current = current->next;
	}

	for (size_t i = 0; i < list->len; i++) {
		free(item_ptrs[i]);
	}

	free(item_ptrs);
	free(list);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_to_arr() —————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @fn ll_to_arr
 * @brief Convert the linked list `list`, to an array of pointers.
 *
 * This function allocates `list.len × sizeof(void*)` bytes of memory for the created array. The pointer to this
 *	allocated array is returned, and must be freed by the user.
 *
 * @param list[in] The linked list to be converted to an array.
 * @return An array of pointers, each pointing to the values stored in each element of the linked list.
 *
 * @throw `RETURN_IF_NULL` – Prints a warning to `stderr` if memory allocation fails. Returns `NULL`.
 * @note `Θ(n)`, where `n ∝ list.len`
 */
void **ll_to_arr(const LList list) {
	const void **array = calloc(list->len, sizeof(void*));
	RETURN_IF_NULL(array, NULL);

	const LLItem *current = list->head;
	// we have to iterate through the list and save all the pointers that need to be freed
	//	this could also be done recursively, but honestly, this is easier.
	for (size_t i = 0; i < list->len; i++) {
		array[i] = current->val;
		current = current->next;
	}

	return (void**)array;
}

/* —— ll_from_arr() ———————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @fn ll_from_arr
 * @brief Convert an array of pointers into a linked list.
 *
 * This function calls `ll_init()` which allocates memory for the linked list, and must be freed with `ll_free()`.
 *
 * @param array[in] A pointer to an array of pointers, which is to be converted into a linked list.
 * @param len[in] The number of pointers in the array pointed to by `array`.
 *
 * @return The linked list created from the inputted array. `NULL` on failure.
 *
 * @throw `RETURN_IF_NULL` – Prints a warning to `stderr` if `ll_init()` fails. Returns `NULL`.
 * @note `Θ(n)`, where `n ∝ len`
 */
LList ll_from_arr(const void *const *const array, const size_t len) {
	LList list = ll_init();
	RETURN_IF_NULL(list, NULL);

	for (size_t i = 0; i < len; i++) ll_append(list, array[i]);
	return list;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_append() —————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @fn ll_append
 * @brief Add a new value to the end of a linked list.
 *
 * @param list[in,out] The linked list to append the inputted value to.
 * @param val[in] The value to be appended.
 *
 * @return The positive index of the the newly appended value (also equal to `list.len`).
 *
 * @throw `RETURN_IF_NULL` – Prints a warning to `stderr` if memory allocation fails, and returns `NULL`.
 * @note `Θ(1)`
 */
idx_t ll_append(LList list, const void *const val) {
	// allocate memory for this item, and initialise it with the inputted `val` param
	LLItem *pitem = malloc(sizeof(LLItem));
	RETURN_IF_NULL(pitem, -1);

	*pitem = (LLItem){ .next = NULL, .val = val };

	// if this is the first element, then also set the head to this item
	if (list->head == NULL) list->head = pitem;
	// otherwise, just set the `next` property of the last element
	else list->tail->next = pitem;

	list->tail = pitem; // no matter what, set the tail of the linked list to this item
	return ++list->len; // return the index of the added item
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— normalise_index() ———————————————————————————————————————————————————————————————————————————————————————————— */

#define XNOR ==

/**
 * @fn @static normalise_index
 * @overload l__normalise_index
 */
#define normalise_index(llist, index) \
	l__normalise_index(__func__, (llist), (index))

/**
 * @fn @static ll__normalise_index
 * @brief Convert any negative indices to their positive equivalenets.
 *
 * Additionally, checks that an index is valid, and in range for the .
 *	Also runs some assertions to make sure that `list` is generally valid.
 *
 * @param caller[in]
 *		The calling function's name, determined and passed by the `normalise_index` macro.
 *			Used solely to print errors as if the errors were raised by the caller itself.
 * @param list[in] The list for which the index is being normalised.
 * @param idx[in] The raw (un-normalised) index, passed by the user.
 *
 * @return The normalised index for the inputted list.
 *
 * @throw `IDX_OOR_ERROR` – Exits with error code `1` if the inputted index isn't in range for the list.
 *
 * @pre If `list.head` is NULL then `list.tail` should be too, and vice versa.
 * @pre If `list.head` is NULL then `list.len`  should be `0`.
 * @pre If `list.tail` is NULL then `list.len`  should be `0`.
 *
 * @note `Θ(1)`
 */
static inline idx_t l__normalise_index(const char *const caller, const LList list, const idx_t idx) {
	// there should never be a case in which the head or tail is NULL, and the other one isn't
	assert((list->head == NULL) XNOR (list->tail == NULL));

	// equally, whenever the head and/or tail is NULL, the length should be 0
	assert((list->head == NULL) XNOR (list->len == 0));
	assert((list->tail == NULL) XNOR (list->len == 0));

	// make a copy of the index which we can manipulate as needed
	idx_t index = idx;

	// if the user requests the last element, then just return the linked list's tail
	if (index == -1 || index == (idx_t)(list->len - 1)) {
		// that is, unless the list is empty
		if (list->len == 0) IDX_OOR_ERROR(caller, list, index);
		return (idx_t)(list->len - 1);
	}

	// make sure that the list is long enough to accommodate this index
	if (index >= (idx_t)list->len) IDX_OOR_ERROR(caller, list, index);

	// if the index entered was negative, then convert it into its positive counterpart
	if (index <= -1) {
		index = list->len + idx;
		// check that the index is still in range
		if (index < 0) IDX_OOR_ERROR(caller, list, idx);
	}

	return index;
}

/* —— ll_get() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @fn ll_get
 * @brief Get the value of a linked list at a given index.
 *
 * @param list[in] The linked list from which to find the value.
 * @param idx[in] The list index at which to get the value.
 *
 * @return The value of `list` at index `idx`.
 *
 * @throw `RETURN_IF_NULL` – Prints a warning to `stderr` if `list` is `NULL`. Returns `NULL`.
 * @throw `IDX_OOR_ERROR` – Exits with error code `1` if the inputted index isn't in range for the list.
 *
 * @note `Θ(n)`, where `n ∝ idx[normalised]`
 */
const void *ll_get(const LList list, const idx_t idx) {
	// don't try and operate on a list that points to NULL
	RETURN_IF_NULL(list, NULL);

	const idx_t index = normalise_index(list, idx);
	if (index == (idx_t)(list->len - 1)) return list->tail->val;

	// iterate through the list until we find the index requested
	const LLItem *current = list->head;
	for (idx_t i = 0; i < index; i++) {
		current = current->next;
		assert(current != NULL);
	}

	return current->val;
}

/* —— ll_pop() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @fn ll_pop
 * @brief Remove an element from a linked list by index, and return the removed item's value.
 *
 * @param list[in,out] The list from which to remove the item.
 * @param idx[in] The index of the item to remove.
 *
 * @return The value of the removed item.
 *
 * @throw `RETURN_IF_NULL` – Prints a warning to `stderr` if `list` is `NULL`. Returns `NULL`.
 * @note `Θ(n)`, where `n ∝ idx[normalised]`
 */
const void *ll_pop(LList list, const idx_t idx) {
	// don't try and operate on a list that points to NULL
	RETURN_IF_NULL(list, NULL);

	const idx_t index = normalise_index(list, idx);

	LLItem *prv_item = NULL;       /** The item before the item to delete; NULL if deleting the head. */
	LLItem *del_item = list->head; /** The item to delete. */

	for (idx_t i = 0; i < index; i++) {
		// keep updating the previous item and the item to delete
		prv_item = del_item, del_item = del_item->next;
		// `del_item` shouldn't be able to be NULL, since the loop is bounded by `index`, which should be `< list.len`
		assert(del_item != NULL);
	}

	LLItem *const nxt_item = del_item->next; /** The item after the item to delete. */

	// update the head directly if there's no previous item
	if (prv_item == NULL) list->head = nxt_item;
	// and just relink around the deleted item if everything exists
	else prv_item->next = nxt_item;

	// if we're about to delete the tail, the new tail is whatever was before it (`NULL` if the list is now empty)
	if (del_item == list->tail) list->tail = prv_item;

	const void *const retval = del_item->val; // save the deleted item's value so it can be returned.
	free(del_item);	// delete the item by freeing its memory

	list->len--;	// decrement the list's length
	return retval;	// and finally, return the value that was held by the now-deleted item
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_iter() ———————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @fn l__iter
 *
 * @overload ll_iter_reset
 * @brief Reset the iteration of a linked list.
 *
 * @overload ll_iter
 * @brief Iterate over the next item of a linked list.
 * 
 * Usually used as:
 *
 * ```c
 *	void *value;
 *	while (( value = ll_iter(list) )) {
 *		// ...
 *	}
 * ```
 *
 * @param list[in] The linked list to iterate over.
 * @param do_reset[in] Whether this function should reset itself, or should act as if its starting a new iteration.
 *
 * @return The value of the linked list at the current iteration. `NULL` if 
 *
 * @throw `RETURN_IF_NULL` – Prints a warning to `stderr` and returns NULL if `list` is NULL and `do_reset` is false.
 * @note `Θ(1)`
 */
const void *l__iter(const LList list, const bool do_reset) {
	// the active item being tracked by this iterator
	static const LLItem *current = NULL;

	// this is just some simple overloading, so I don't have to do anything complicated when resetting the iterator
	if (do_reset) return ( current = NULL ); // the retval here doesn't matter - this is just a concise way to do it

	// if the input was NULL (and we're not resetting), then print an error, and return NULL
	RETURN_IF_NULL(list, NULL);

	// if the iteration has just started, set `current` to the first element, otherwise, move onto the next element
	current = (current == NULL) ? list->head : current->next;

	// if the first/next element is `NULL`, then we've reached the end of the list - return NULL
	if (current == NULL) return NULL;
	// otherwise, return the new item's value
	return current->val;
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— ll_dump() ———————————————————————————————————————————————————————————————————————————————————————————————————— */

/**
 * @brief Display the indices and values of each member of a linked list.
 *
 * @param list[in] The list list to be displayed.
 * @param fmt[in] The format string that should be used to display the values stored by the linked list.
 *
 * @note `Θ(n)`, where `n ∝ list.len`
 */
void ll_dump(const LList list, const char *const fmt) {
	if (list == NULL) { puts("NULL"); return; }

	printf("length = %zu", list->len);

	// calculate the max length of the index, for ease of printing
	//	sure, this could be done a better way, but `ll_dump` is mostly used for debugging, so it doesn't rly matter
	const int idxlen = snprintf(NULL, 0, "%zd", (idx_t)(list->len - 1));

	// set up all the iterator variables
	const void *value;
	idx_t idx = 0;
	ll_iter_reset();

	// print each item's index, along with its value, using the format specifier provided
	while (( value = ll_iter(list) )) {
		printf("\n[%*zd] = ", idxlen, idx++);
		printf(fmt, value);
	}

	putchar('\n');
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
