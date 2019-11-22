/* See LICENSE for license details */

#include <cv_file_disk_desc.h>

#include <cv_memory.h>

#include <cv_sizeof.h>

cv_bool cv_file_disk_desc_init(
    cv_file_disk_desc * p_this)
{
    cv_bool b_result = cv_false_;
    if (p_this)
    {
        cv_memory_zero(
            p_this,
            cv_sizeof_(cv_file_disk_desc));
        b_result = cv_true_;
    }
    return b_result;
}

void cv_file_disk_desc_cleanup(
    cv_file_disk_desc * p_this)
{
    if (p_this)
    {
    }
}

