/// @file features/links/apple-alias.h

#ifndef APPLE_ALIAS_INITIALISED
#define APPLE_ALIAS_INITIALISED

#include "../../model/stat-model.h"

bool resolveAppleAlias(path_t target_buffer, bool *is_valid_alias, const path_t file_path);
link_t getPrintableAppleAlias(const path_t target_path);

#endif /* !APPLE_ALIAS_INITIALISED */
