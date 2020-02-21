/* See LICENSE for license details */

#ifndef cv_file_disk_h_
#define cv_file_disk_h_

/*
 *  Module: cv_file_disk.h
 *
 *  Description: Abstraction of files stored on disk.
 */

#include <cv_file/cv_file.h>

/*
 *  Structure: cv_file_disk
 *
 *  Description: Storage for base cv_file structure.
 */

struct cv_file_disk {
    cv_file o_file;
};

cv_bool cv_file_disk_init( cv_file_disk * p_this,
    cv_file_disk_desc const * p_desc);
void cv_file_disk_cleanup( cv_file_disk * p_this);

#endif /* #ifndef cv_file_disk_h_ */

/* end-of-file: cv_file_disk.h */
