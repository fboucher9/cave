/* See LICENSE for license details */

#ifndef cv_file_desc_h_
#define cv_file_desc_h_

/*

*/

#include <cv_file_pred.h>

#include <cv_string.h>

struct cv_file_desc
{
    cv_string o_name;
    cv_string o_mode;
};

#define cv_file_desc_initializer_ { \
    cv_string_initializer_, \
    cv_string_initializer_ }

#endif /* #ifndef cv_file_desc_h_ */
