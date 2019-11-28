/* See LICENSE for license details */

#ifndef cv_file_disk_desc_h_
#define cv_file_disk_desc_h_

/*

*/

#include <cv_file_pred.h>

#include <cv_array.h>

#include <cv_bool.h>

enum cv_file_disk_flag
{
    cv_file_disk_flag_read = 1,

    cv_file_disk_flag_write = 2,

    cv_file_disk_flag_append = 4

};

struct cv_file_disk_desc
{
    cv_array o_name;

    /* -- */

    long i_flags;

    long l_padding[1u];

};

#define cv_file_disk_desc_initializer_ { \
    cv_array_null_, \
    0, \
    {0} }

cv_bool cv_file_disk_desc_init(
    cv_file_disk_desc * p_this);

void cv_file_disk_desc_cleanup(
    cv_file_disk_desc * p_this);

#endif /* #ifndef cv_file_disk_desc_h_ */
