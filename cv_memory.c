/* See LICENSE for license details */

#include <cv_memory.h>

#include <cv_cast.h>

#include <cv_null.h>

#include <cv_bool.h>

#include <cv_algo/cv_array.h>

#include <cv_runtime.h>

#include <cv_debug.h>

void cv_memory_zero(
    void * p_buf,
    long i_buf_len)
{
    if (p_buf && i_buf_len) {
        cv_runtime_memset(p_buf, 0, i_buf_len);
    } else {
        cv_debug_msg_(cv_debug_code_invalid_parameter);
    }
}

void cv_memory_fill(
    void * p_buf,
    long i_buf_len,
    unsigned char c_value)
{
    if (p_buf && i_buf_len) {
        cv_runtime_memset(p_buf, c_value, i_buf_len);
    } else {
        cv_debug_msg_(cv_debug_code_invalid_parameter);
    }
}

long cv_memory_copy(
    void * p_dst,
    long i_dst_len,
    void const * p_src,
    long i_src_len)
{
    long i_copy_len = 0;
    if (p_dst && p_src) {
        i_copy_len =
            (i_src_len < i_dst_len)
            ? i_src_len
            : i_dst_len;
        if (i_copy_len > 0) {
            cv_runtime_memcpy(p_dst, p_src, i_copy_len);
        } else {
            cv_debug_msg_(cv_debug_code_invalid_length);
            i_copy_len = 0;
        }
    } else {
        cv_debug_msg_(cv_debug_code_null_ptr);
    }
    return i_copy_len;
}

long cv_memory_find_0(
    void const * p_src,
    long i_src_len)
{
    long i_find_len = -1;
    if (p_src && i_src_len > 0) {
        cv_array o_array = cv_array_null_;
        o_array.o_min.pc_void = p_src;
        o_array.o_max.pc_void = cv_runtime_memchr(p_src, '\000', i_src_len);
        if (o_array.o_max.pc_void) {
            i_find_len = cv_array_len(&o_array);
        }
    } else {
        cv_debug_msg_(cv_debug_code_invalid_parameter);
    }
    return i_find_len;
}

int cv_memory_compare(
    void const * p_left,
    long i_left_len,
    void const * p_right,
    long i_right_len)
{
    int i_compare_result = -1;
    if (p_left && p_right) {
        long const i_compare_len =
            i_left_len < i_right_len ? i_left_len : i_right_len;
        i_compare_result = cv_runtime_memcmp(
            p_left, p_right, i_compare_len);
        if (0 == i_compare_result) {
            if (i_left_len > i_right_len) {
                i_compare_result = 1;
            } else if (i_left_len < i_right_len) {
                i_compare_result = -1;
            }
        }
    } else {
        cv_debug_msg_(cv_debug_code_invalid_parameter);
    }
    return i_compare_result;
}

