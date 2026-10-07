/// @file utils/malloc.c

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "malloc.h"
#include "debugging.h"
#include "model/global.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#ifdef DEBUG_MODE
	static size_t alloc_count = 0, freed_count = 0;
	static bool first_write = true;

#	define print_error(...)	debug(ERROR, __VA_ARGS__)

#	define PTR(p)			((uintptr_t)(p))
#	define REL_PATH(file)	((char *)(strstr((char *)(file), "source/") + (int)(sizeof("source/") - 1)))

#	define DIFF				(L'Δ'), ((ssize_t)(alloc_count - freed_count))
#	define DIFF_FMT(chr)	" [" #chr "=%3zu %lc=%3zd] "

#	define tolog(fpath, mode, fmt, ...) do {							\
		const int err_no = errno;										\
		FILE *const log_file = fopen(fpath, first_write ? "w" : mode);	\
		\
		fprintf(log_file, fmt "  %-26s @ %-14s (%3d)\n",				\
			__VA_ARGS__, REL_PATH(file), func, line						\
		);																\
		fclose(log_file);												\
		errno = err_no;													\
	} while (0)

#	define tologfile(...) do {				\
		tolog(LOG_FILE, "a", __VA_ARGS__);	\
		tolog(LOG_PIPE, "w", __VA_ARGS__);	\
		first_write = false;				\
	} while (0)

	/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	void checkMemLeak(void) {
		if (freed_count == alloc_count) {
			debug(SUCCESS, "likely no memory leak - times alloced = %zu, times freed = %zu (%lc = %zd)",
				alloc_count, freed_count, DIFF
			);
			return;
		}

		if (freed_count > alloc_count) debug(ERROR, "freed memory more times than allocated");

		debug(WARNING, "likely memory leak - times alloced = %zu, times freed = %zu (%lc = %zd)",
			alloc_count, freed_count, DIFF
		);
	}

	/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	static inline void *log_alloc(void *ptr DEBUG_ARGS) {
		alloc_count++;
		tologfile("[alloc]" DIFF_FMT(a) "%29lX", alloc_count, DIFF, PTR(ptr));

		return ptr;
	}

	static inline void *log_realloc(void *oldptr, void *newptr DEBUG_ARGS) {
		if (oldptr == NULL) {
			alloc_count++;
			tologfile("[alloc]" DIFF_FMT(a) "%12lX --> %12lX", alloc_count, DIFF, PTR(oldptr), PTR(newptr));
		} else {
			tologfile("[reall]  -- -- -- --  %12lX --> %12lX",					  PTR(oldptr), PTR(newptr));
		}

		return newptr;
	}

	static inline void *log_freed(void *ptr DEBUG_ARGS) {
		freed_count++;
		tologfile("[freed]" DIFF_FMT(f) "%12lX %16s", freed_count, DIFF, PTR(ptr), "");
		return ptr;
	}

	/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

	void e__alloced(const size_t count DEBUG_ARGS) {
		alloc_count += count;
		tologfile("[alloc]" DIFF_FMT(a) "%29s", alloc_count, DIFF, "???");
	}

#else
#	define	 log_alloc(ptr)		 (ptr)
#	define	 log_freed(ptr)		 (ptr)
#	define log_realloc(old, new) (new)

#	define print_error(...) fprintf(stderr, __VA_ARGS__)
#endif

/* ———————————————————————————————————————————————————————— */

static inline void *exitIfNull(void *ptr) {
	if (ptr != NULL) return ptr;

	print_error("%s: fatal memory error: %s", argv0, strerror(errno));
	exit(EXIT_FAILURE);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

void* e__malloc(size_t size DEBUG_ARGS) {
	return exitIfNull(log_alloc(malloc(size) DEBUG_PASSED));
}

void* e__calloc(size_t count, size_t size DEBUG_ARGS) {
	return exitIfNull(log_alloc(calloc(count, size) DEBUG_PASSED));
}

void* e__realloc(void *ptr, size_t size DEBUG_ARGS) {
	// `reallocf` frees the original pointer if it fails
	return exitIfNull(log_realloc(ptr, reallocf(ptr, size) DEBUG_PASSED));
}

/* ———————————————————————————————————————————————————————— */

void e__free(void *ptr DEBUG_ARGS) {
	free(log_freed(ptr DEBUG_PASSED));
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

// spell:ignore reall
