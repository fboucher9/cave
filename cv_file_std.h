/* See LICENSE for license details */

#ifndef cv_file_std_h_
#define cv_file_std_h_

#include <cv_file.h>

struct cv_file_std
{
    cv_file o_file;
};

#define cv_file_std_initializer_ { cv_file_initializer_ }

extern cv_file_std g_cv_file_std_in;

extern cv_file_std g_cv_file_std_out;

extern cv_file_std g_cv_file_std_err;

cv_bool cv_file_std_load(void);

void cv_file_std_unload(void);

cv_bool cv_file_std_print(
    cv_array const * p_array);

cv_bool cv_file_std_print_0(
    char const * const p_msg0,
    long i_msg0_max_len);

cv_bool cv_file_std_print_nl(void);

#endif /* #ifndef cv_file_std_h_ */

/* end-of-file: cv_file_std.h */
