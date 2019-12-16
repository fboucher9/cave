/* See LICENSE for license details */

/*
 *
 */

#include <cv_debug/cv_debug_code.h>

#if defined cv_debug_

cv_debug_code cv_debug_code_null_ptr = "null ptr";

cv_debug_code cv_debug_code_error = "error";

cv_debug_code cv_debug_code_already_loaded = "already loaded";

cv_debug_code cv_debug_code_already_unloaded = "already unloaded";

cv_debug_code cv_debug_code_not_loaded = "not loaded";

cv_debug_code cv_debug_code_invalid_length = "invalid length";

cv_debug_code cv_debug_code_alternative = "alternative";

cv_debug_code cv_debug_code_out_of_memory = "out of memory";

cv_debug_code cv_debug_code_not_empty = "not empty";

cv_debug_code cv_debug_code_not_implemented = "not implemented";

cv_debug_code cv_debug_code_invalid_parameter = "invalid parameter";

cv_debug_code cv_debug_code_dont_panic = "dont panic!";

cv_debug_code cv_debug_code_leak = "leak";

cv_debug_code cv_debug_code_recursive = "recursive";

#else /* #if defined cv_debug_ */

typedef void not_empty;

#endif /* #if defined cv_debug_ */

/* end-of-file: cv_debug_code.c */
