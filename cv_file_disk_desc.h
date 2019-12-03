/* See LICENSE for license details */

#ifndef cv_file_disk_desc_h_
#define cv_file_disk_desc_h_

/*

*/

#include <cv_file_pred.h>
#include <cv_array.h>
#include <cv_bool.h>

enum cv_file_disk_mode {
    cv_file_disk_mode_invalid = 0,
    cv_file_disk_mode_read,
    cv_file_disk_mode_write,
    cv_file_disk_mode_append
};

struct cv_file_disk_desc {
    cv_array const * p_name;
    void * pv_padding[1u];
    /* -- */
    int e_mode;
    int ai_padding[3u];
};

#define cv_file_disk_desc_initializer_ { \
    cv_null_, \
    { cv_null_ }, \
    0, \
    {0} }

void cv_file_disk_desc_init(
    cv_file_disk_desc * p_this);

void cv_file_disk_desc_cleanup(
    cv_file_disk_desc * p_this);

#endif /* #ifndef cv_file_disk_desc_h_ */
