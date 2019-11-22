/* See LICENSE for license details */

#include <cv_file.h>

#include <cv_unused.h>

cv_bool cv_file_init(
    cv_file * p_this,
    cv_file_desc const * p_desc)
{
    cv_unused_(p_this);
    cv_unused_(p_desc);
    return cv_false_;
}

void cv_file_cleanup(
    cv_file * p_this)
{
    cv_unused_(p_this);
}

long cv_file_read(
    cv_file * p_this,
    cv_string const * p_string)
{
    cv_unused_(p_this);
    cv_unused_(p_string);
    return -1;
}

long cv_file_write(
    cv_file * p_this,
    cv_string const * p_string)
{
    cv_unused_(p_this);
    cv_unused_(p_string);
    return -1;
}

