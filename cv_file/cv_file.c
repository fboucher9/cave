/* See LICENSE for license details */

/*
 *  Module: cv_file.c
 *
 *  Description: File abstraction layer.
 */

#include <cv_file/cv_file.h>
#include <cv_algo/cv_array.h>
#include <cv_runtime.h>
#include <cv_debug/cv_debug.h>
#include <cv_misc/cv_sizeof.h>

/* Debugging information for cv_file structure */
cv_debug_decl_(cv_file_class);

/*
 *  Function: cv_file_init
 *
 *  Description: Initialize instance of cv_file structure.
 */

void cv_file_init( cv_file * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(cv_file_class, p_this);
    p_this->i_index = -1;
}

/*
 *  Function: cv_file_cleanup
 *
 *  Description: Undo initialization of cv_file structure.
 */

void cv_file_cleanup( cv_file * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_destruct_(cv_file_class, p_this);
}

/*
 *  Function: cv_file_read
 *
 *  Description: Low-level read from file descriptor.  Attempt to fill in
 *  entire array with data from file.  Actual number of bytes read is returned.
 *
 *  Comments: Caller is responsible of iteration or completion of read when
 *  less than expected length is read.
 */

long cv_file_read( cv_file const * p_this, cv_array const * p_array) {
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

/*
 *  Function: cv_file_write
 *
 *  Description: Low-level write to file descriptor.  Attempt to write to
 *  file entire contents of array.  Actual number of bytes written is returned.
 *
 *  Comments: Caller is responsible of iteration or completion of write when
 *  less than expected length is written.
 */

long cv_file_write( cv_file const * p_this, cv_array const * p_array) {
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

/* end-of-file: cv_file.c */
