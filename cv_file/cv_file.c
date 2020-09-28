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

/* Debugging information for cv_file structure */
cv_debug_decl_(cv_file_class, "cv_file", sizeof(cv_file));

/*
 *  Function: cv_file_init
 *
 *  Description: Initialize instance of cv_file structure.
 */

void cv_file_init( cv_file * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(cv_file_class, p_this);
    cv_file_set_index(p_this, -1);
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

cv_sptr cv_file_read( cv_file const * p_this, cv_array const * p_array) {
    cv_sptr i_result = -1;
    cv_debug_assert_( p_this && p_array, cv_debug_code_null_ptr);
    {
        cv_uptr const i_array_len = cv_array_len(p_array);
        if (i_array_len > 0) {
            int const i_index = cv_file_get_index(p_this);
            if (i_index >= 0) {
                i_result = cv_runtime_read(
                    i_index,
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

cv_sptr cv_file_write( cv_file const * p_this, cv_array const * p_array) {
    cv_sptr i_result = -1;
    cv_debug_assert_(p_this && p_array, cv_debug_code_null_ptr);
    {
        cv_uptr const i_array_len = cv_array_len(p_array);
        if (i_array_len > 0) {
            int const i_index = cv_file_get_index(p_this);
            if (i_index >= 0) {
                i_result = cv_runtime_write(
                    i_index,
                    p_array->o_min.p_void,
                    i_array_len);
            }
        }
    }
    return i_result;
}

/*
 *
 */

int cv_file_get_index( cv_file const * p_this) {
    int i_index = -1;
    if (p_this->i_handle > 0) {
        i_index = p_this->i_handle - 1;
    } else {
        i_index = -1;
    }
    return i_index;
}

/*
 *
 */

void cv_file_set_index( cv_file * p_this, int i_index) {
    if (i_index < 0) {
        p_this->i_handle = 0;
    } else {
        p_this->i_handle = i_index + 1;
    }
}

/* end-of-file: cv_file.c */
