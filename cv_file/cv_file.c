/* See LICENSE for license details */

#include <cv_file/cv_file.h>
#include <cv_algo/cv_array.h>
#include <cv_runtime.h>
#include <cv_debug.h>
#include <cv_misc/cv_sizeof.h>

cv_debug_decl_(g_class);

void cv_file_init(
    cv_file * p_this) {
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    p_this->i_index = -1;
}

void cv_file_cleanup(
    cv_file * p_this) {
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_debug_destruct_(g_class, p_this);
}

long cv_file_read(
    cv_file const * p_this,
    cv_array const * p_array)
{
    long i_result = -1;
    cv_debug_assert_( p_this && p_array, cv_debug_code_null_ptr);
    {
        long const i_array_len = cv_array_len(p_array);
        if (i_array_len > 0) {
            if (p_this->i_index >= 0) {
                i_result = cv_runtime_read(
                    p_this->i_index,
                    p_array->o_min.p_void,
                    i_array_len);
            }
        }
    }
    return i_result;
}

long cv_file_write(
    cv_file const * p_this,
    cv_array const * p_array)
{
    long i_result = -1;
    cv_debug_assert_(p_this && p_array, cv_debug_code_null_ptr);
    {
        long const i_array_len = cv_array_len(p_array);
        if (i_array_len > 0) {
            if (p_this->i_index >= 0) {
                i_result = cv_runtime_write(
                    p_this->i_index,
                    p_array->o_min.p_void,
                    i_array_len);
            }
        }
    }
    return i_result;
}

