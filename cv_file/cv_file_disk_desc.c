/* See LICENSE for license details */

#include <cv_file/cv_file_disk_desc.h>

#include <cv_memory.h>

#include <cv_misc/cv_sizeof.h>

#include <cv_debug.h>

cv_debug_decl_(g_class);

void cv_file_disk_desc_init(
    cv_file_disk_desc * p_this)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    p_this->p_name = cv_null_;
    p_this->e_mode = cv_file_disk_mode_invalid;
}

void cv_file_disk_desc_cleanup(
    cv_file_disk_desc * p_this)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    p_this->p_name = cv_null_;
    cv_debug_destruct_(g_class, p_this);
}

