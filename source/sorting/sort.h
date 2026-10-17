/// @file sorting/sort.h

#ifndef SORT_H
#define SORT_H

#include "model/stat-model.h"

#define DO_SORT_CHILDREN(p_fs) ( \
	isFSDir(p_fs)			&&	 \
	(p_fs)->f != NULL		&&	 \
	(p_fs)->f->child_count >= 2	 \
)

#define SORT_CHILDREN(p_fs, depth_) do { \
	if (DO_SORT_CHILDREN(p_fs)) {		 \
		sortFiles((depth_),				 \
			(p_fs)->f->children,		 \
			(p_fs)->f->child_count		 \
		);								 \
	}									 \
} while (0)

void sortFiles(const uint8_t depth, void *const arr, const int arr_count);

#endif /* !SORT_H */
