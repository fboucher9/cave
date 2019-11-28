/* See LICENSE for license details */

#include <cv_file_disk_desc.h>

#include <cv_memory.h>

#include <cv_sizeof.h>

#include <cv_debug.h>

cv_bool cv_file_disk_desc_init(
    cv_file_disk_desc * p_this)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        cv_debug_init_(
            p_this,
            cv_sizeof_(*p_this));
        if (cv_array_init(
                &p_this->o_name))
        {
            p_this->i_flags = cv_file_disk_flag_invalid;
            b_result = cv_true;
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

void cv_file_disk_desc_cleanup(
    cv_file_disk_desc * p_this)
{
    if (p_this)
    {
        cv_array_cleanup(&p_this->o_name);
        cv_debug_cleanup_(
            p_this,
            cv_sizeof_(*p_this));
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
}

