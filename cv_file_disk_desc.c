/* See LICENSE for license details */

#include <cv_file_disk_desc.h>

#include <cv_memory.h>

#include <cv_sizeof.h>

#include <cv_debug.h>

void cv_file_disk_desc_init(
    cv_file_disk_desc * p_this)
{
    cv_debug_assert_( !!p_this, "null ptr");
    cv_debug_init_( p_this, cv_sizeof_(*p_this));
    cv_array_init( &p_this->o_name);
    p_this->i_flags = cv_file_disk_flag_invalid;
}

void cv_file_disk_desc_cleanup(
    cv_file_disk_desc * p_this)
{
    cv_debug_assert_( !!p_this, "null ptr");
    cv_array_cleanup(&p_this->o_name);
    cv_debug_cleanup_( p_this, cv_sizeof_(*p_this));
}

