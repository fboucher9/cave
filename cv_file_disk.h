/* See LICENSE for license details */

#ifndef cv_file_disk_h_
#define cv_file_disk_h_

#include <cv_file.h>

struct cv_file_disk
{
    cv_file o_file;
};

#define cv_file_disk_initializer_ { cv_file_initializer_ }

cv_bool cv_file_disk_init(
    cv_file_disk * p_this,
    cv_file_disk_desc const * p_desc);

void cv_file_disk_cleanup(
    cv_file_disk * p_this);

#endif /* #ifndef cv_file_disk_h_ */

/* end-of-file: cv_file_disk.h */
