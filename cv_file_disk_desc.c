/* See LICENSE for license details */

#include <cv_file_disk_desc.h>

#include <cv_memory.h>

#include <cv_sizeof.h>

#include <cv_debug.h>

void cv_file_disk_desc_init(
    cv_file_disk_desc * p_this)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_debug_init_( p_this, cv_sizeof_(*p_this));
    p_this->p_name = cv_null_;
    p_this->e_mode = cv_file_disk_mode_invalid;
}

void cv_file_disk_desc_cleanup(
    cv_file_disk_desc * p_this)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    p_this->p_name = cv_null_;
    cv_debug_cleanup_( p_this, cv_sizeof_(*p_this));
}

