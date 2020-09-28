/* See LICENSE for license details */

/*
 *  Module: cv_file_disk.h
 *
 *  Description: Abstraction of files stored on disk.
 */

#include <cv_file/cv_file_disk.h>
#include <cv_file/cv_file_disk_desc.h>
#include <cv_algo/cv_array_0.h>
#include <cv_debug/cv_debug.h>
#include <cv_runtime.h>

/* Debug information for cv_file_disk structure */
cv_debug_decl_(cv_file_disk_class, "cv_file_disk", sizeof(cv_file_disk));

/*
 *  Function: cv_file_disk_init
 *
 *  Description: Open file using information from descriptor.
 */

cv_bool cv_file_disk_init( cv_file_disk * p_this,
    cv_file_disk_desc const * p_desc) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_desc, cv_debug_code_null_ptr);
    cv_debug_construct_(cv_file_disk_class, p_this);
    cv_file_init(&p_this->o_file);
    /* Setup call to open */
    {
        cv_array_0 o_name0 = {0};
        if (cv_array_0_init(&o_name0, p_desc->p_name, "file_disk_name", 0)) {
            char const * const p_open_pathname =
                cv_array_0_get(&o_name0);
            if (p_desc->e_mode == cv_file_disk_mode_append) {
                cv_file_set_index(&p_this->o_file, cv_runtime_open_append(
                    p_open_pathname));
            } else if (p_desc->e_mode == cv_file_disk_mode_write) {
                cv_file_set_index(&p_this->o_file, cv_runtime_open_write(
                    p_open_pathname));
            } else if (p_desc->e_mode == cv_file_disk_mode_read) {
                cv_file_set_index(&p_this->o_file, cv_runtime_open_read(
                    p_open_pathname));
            }
            if (cv_file_get_index(&p_this->o_file) >= 0) {
                b_result = cv_true;
            }
            cv_array_0_cleanup(&o_name0);
        }
    }
    if (!b_result) {
        cv_file_cleanup(&p_this->o_file);
        cv_debug_destruct_(cv_file_disk_class, p_this);
    }
    return b_result;
}

/*
 *  Function: cv_file_disk_cleanup
 *
 *  Description: Close the file
 *
 */

void cv_file_disk_cleanup( cv_file_disk * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    /* Setup call to close */
    {
        int const i_index = cv_file_get_index(&p_this->o_file);
        if (i_index >= 0) {
            cv_runtime_close(i_index);
            cv_file_set_index(&p_this->o_file, -1);
        }
    }
    cv_file_cleanup(&p_this->o_file);
    cv_debug_destruct_(cv_file_disk_class, p_this);
}

/* end-of-file: cv_file_disk.c */
