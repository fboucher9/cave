/* See LICENSE for license details */

#ifndef cv_debug_code_h_
#define cv_debug_code_h_

/*
 *
 */

#include <cv_debug/cv_debug_pred.h>

#if defined cv_debug_

extern cv_debug_code cv_debug_code_null_ptr;
extern cv_debug_code cv_debug_code_error;
extern cv_debug_code cv_debug_code_already_loaded;
extern cv_debug_code cv_debug_code_already_unloaded;
extern cv_debug_code cv_debug_code_not_loaded;
extern cv_debug_code cv_debug_code_invalid_length;
extern cv_debug_code cv_debug_code_alternative;
extern cv_debug_code cv_debug_code_out_of_memory;
extern cv_debug_code cv_debug_code_not_empty;
extern cv_debug_code cv_debug_code_not_implemented;
extern cv_debug_code cv_debug_code_invalid_parameter;
extern cv_debug_code cv_debug_code_dont_panic;
extern cv_debug_code cv_debug_code_leak;

#endif /* #if defined cv_debug_ */

#endif /* #ifndef cv_debug_code_h_ */

/* end-of-file: cv_debug_code.h */
