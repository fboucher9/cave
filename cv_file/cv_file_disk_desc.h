/* See LICENSE for license details */

#ifndef cv_file_disk_desc_h_
#define cv_file_disk_desc_h_

/*
 *  Module: cv_file_disk_desc.h
 *
 *  Description: Descriptor for cv_file_disk initialization.
 */

#include <cv_file/cv_file_pred.h>
#include <cv_algo/cv_array.h>

/*
 *  Enumeration: cv_file_disk_mode
 *
 *  Description: File access mode to use when opening the file.
 */

enum cv_file_disk_mode {
    cv_file_disk_mode_invalid = 0,
    cv_file_disk_mode_read,
    cv_file_disk_mode_write,
    cv_file_disk_mode_append
};

/*
 *  Structure: cv_file_disk_desc
 *
 *  Description: Descriptor for cv_file_disk initialization.
 */

struct cv_file_disk_desc {
    cv_array const * p_name;
    /* -- */
    int e_mode;
    int ai_padding[3u];
};

void cv_file_disk_desc_init( cv_file_disk_desc * p_this);

void cv_file_disk_desc_cleanup( cv_file_disk_desc * p_this);

#endif /* #ifndef cv_file_disk_desc_h_ */

/* end-of-file: cv_file_disk_desc.h */
