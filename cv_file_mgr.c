/* See LICENSE for license details */

#include <cv_file_mgr.h>

#include <cv_file_impl.h>

cv_file cv_file_stdin = cv_file_initializer_;

cv_file cv_file_stdout = cv_file_initializer_;

cv_file cv_file_stderr = cv_file_initializer_;

cv_bool cv_file_mgr_load(void)
{
    return cv_true_;
}

void cv_file_mgr_unload(void)
{
}

