/* See LICENSE for license details */

#include <cv_file.h>
#include <cv_array.h>
#if defined cv_linux_
#include <cv_linux.h>
#else /* #if defined cv_linux_ */
#include <cv_runtime.h>
#endif /* #if defined cv_linux_ */
#include <cv_debug.h>
#include <cv_sizeof.h>

void cv_file_init(
    cv_file * p_this) {
    cv_debug_assert_(!!p_this, "null ptr");
    cv_debug_init_(p_this, cv_sizeof_(*p_this));
#if defined cv_linux_
    p_this->i_index = -1;
#else /* #if defined cv_linux_ */
    p_this->p_void = cv_null_;
#endif /* #if defined cv_linux_ */
}

void cv_file_cleanup(
    cv_file * p_this) {
    cv_debug_assert_(!!p_this, "null ptr");
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}

long cv_file_read(
    cv_file const * p_this,
    cv_array const * p_array)
{
    long i_result = -1;
    cv_debug_assert_( p_this && p_array, "null ptr");
    {
        long const i_array_len = cv_array_len(p_array);
        if (i_array_len > 0) {
#if defined cv_linux_
            if (p_this->i_index >= 0) {
                i_result = cv_linux_read(
                    p_this->i_index,
                    p_array->o_min.p_void,
                    i_array_len);
            }
#else /* #if defined cv_linux_ */
#endif /* #if defined cv_linux_ */
        }
    }
    return i_result;
}

long cv_file_write(
    cv_file const * p_this,
    cv_array const * p_array)
{
    long i_result = -1;
    cv_debug_assert_(p_this && p_array, "null ptr");
    {
        long const i_array_len = cv_array_len(p_array);
        if (i_array_len > 0) {
#if defined cv_linux_
            if (p_this->i_index >= 0) {
                i_result = cv_linux_write(
                    p_this->i_index,
                    p_array->o_min.p_void,
                    i_array_len);
            }
#else /* #if defined cv_linux_ */
            cv_runtime_printf("%.*s",
                cv_cast_(int, i_array_len),
                p_array->o_min.pc_char);
#endif /* #if defined cv_linux_ */
        }
    }
    return i_result;
}

