/* See LICENSE for license details */

#include <cv_file/cv_file_disk.h>

#include <cv_file/cv_file_disk_desc.h>

#include <cv_memory.h>

#include <cv_misc/cv_sizeof.h>

#include <cv_algo/cv_string0.h>

#include <cv_misc/cv_unused.h>

#include <cv_debug.h>

#include <cv_runtime.h>

cv_debug_decl_(g_class);

cv_bool cv_file_disk_init(
    cv_file_disk * p_this,
    cv_file_disk_desc const * p_desc)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_desc, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_file_init(&p_this->o_file);
    /* Setup call to open */
    {
        cv_string0 o_name0 = cv_string0_initializer_;
        if (cv_string0_init(&o_name0, p_desc->p_name)) {
            char const * const p_open_pathname =
                cv_string0_get(&o_name0);
            if (p_desc->e_mode == cv_file_disk_mode_append) {
                p_this->o_file.i_index = cv_runtime_open_append(
                    p_open_pathname);
            } else if (p_desc->e_mode == cv_file_disk_mode_write) {
                p_this->o_file.i_index = cv_runtime_open_write(
                    p_open_pathname);
            } else if (p_desc->e_mode == cv_file_disk_mode_read) {
                p_this->o_file.i_index = cv_runtime_open_read(
                    p_open_pathname);
            }
            if (p_this->o_file.i_index != -1) {
                b_result = cv_true;
            }
            cv_string0_cleanup(&o_name0);
        }
    }
    if (!b_result) {
        cv_file_cleanup(&p_this->o_file);
        cv_debug_destruct_(g_class, p_this);
    }
    return b_result;
}

void cv_file_disk_cleanup(
    cv_file_disk * p_this)
{
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    /* Setup call to close */
    if (p_this->o_file.i_index >= 0) {
        cv_runtime_close(p_this->o_file.i_index);
        p_this->o_file.i_index = -1;
    }
    cv_file_cleanup(&p_this->o_file);
    cv_debug_destruct_(g_class, p_this);
}

/* end-of-file: cv_file_disk.c */
