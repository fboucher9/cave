/* See LICENSE for license details */

/*
 *  Module: cv_file_disk_desc.h
 *
 *  Description: Descriptor for cv_file_disk initialization.
 */

#include <cv_file/cv_file_disk_desc.h>
#include <cv_debug/cv_debug.h>

/* Debug information for cv_file_disk_desc structure */
cv_debug_decl_(cv_file_disk_desc_class);

/*
 *  Function: cv_file_disk_desc_init
 *
 *  Description: Initialize fields of cv_file_disk_desc structure.
 */

void cv_file_disk_desc_init( cv_file_disk_desc * p_this) {
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(cv_file_disk_desc_class, p_this);
    p_this->p_name = cv_null_;
    p_this->e_mode = cv_file_disk_mode_invalid;
}

/*
 *  Function: cv_file_disk_desc_cleanup
 *
 *  Description: Undo initialization of cv_file_disk_desc structure.
 */

void cv_file_disk_desc_cleanup( cv_file_disk_desc * p_this) {
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    p_this->p_name = cv_null_;
    cv_debug_destruct_(cv_file_disk_desc_class, p_this);
}

/* end-of-file: cv_file_disk_desc.c */
