/* See LICENSE for license details */

#ifndef cv_file_desc_h_
#define cv_file_desc_h_

/*

*/

#include <cv_file_pred.h>

#include <cv_string.h>

#include <cv_bool.h>

enum cv_file_mode
{
    cv_file_mode_read = 1,

    cv_file_mode_write = 2,

    cv_file_mode_append = 3

};

struct cv_file_desc
{
    cv_string o_name;

    /* -- */

    long e_mode;

    long l_padding[1u];

};

#define cv_file_desc_initializer_ { \
    cv_string_initializer_, \
    0, \
    {0} }

cv_bool cv_file_desc_init(
    cv_file_desc * p_this);

void cv_file_desc_cleanup(
    cv_file_desc * p_this);

#endif /* #ifndef cv_file_desc_h_ */
