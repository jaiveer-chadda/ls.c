/// @file features/links/links.h

#ifndef LINKS_H
#define LINKS_H

#include "model/types.h"

link_t getLink(const path_t link_path);
bool resolveAppleAlias(path_t target_buffer, bool *is_valid_alias, const path_t file_path);

#endif /* !LINKS_H */
