/* See LICENSE for license details */

#ifndef cv_file_std_h_
#define cv_file_std_h_

#include <cv_file_pred.h>

#include <cv_bool.h>

cv_bool cv_file_std_load(void);

void cv_file_std_unload(void);

cv_file const * cv_file_std_in(void);

cv_file const * cv_file_std_out(void);

cv_file const * cv_file_std_err(void);

#endif /* #ifndef cv_file_std_h_ */

/* end-of-file: cv_file_std.h */
