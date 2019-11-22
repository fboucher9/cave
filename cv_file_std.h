/* See LICENSE for license details */

#ifndef cv_file_std_h_
#define cv_file_std_h_

#include <cv_file.h>

struct cv_file_std
{
    cv_file o_file;
};

#define cv_file_std_initializer_ { cv_file_initializer_ }

cv_file_std const * cv_file_std_in(void);

cv_file_std const * cv_file_std_out(void);

cv_file_std const * cv_file_std_err(void);

cv_bool cv_file_std_load(void);

void cv_file_std_unload(void);

#endif /* #ifndef cv_file_std_h_ */

/* end-of-file: cv_file_std.h */
