/* See LICENSE for license details */

#ifndef cv_file_handle_h_
#define cv_file_handle_h_

#include <cv_file_pred.h>

#include <cv_types.h>

union cv_file
{
    /* Alignment to 64-bits */
    cv_sll ll_align;

    /* Storage for FILE* or for Windows HANDLE */
    void * p_void;

    /* Storage for POSIX file descriptor */
    int i_index;

};

#define cv_file_initializer_ { 0 }

/* Compile-time verification of cv_file handle */
typedef char cv_verify_sizeof_file [
    (sizeof(cv_file) == sizeof(cv_sll))
    && (sizeof(cv_file) >= sizeof(int))
    && (sizeof(cv_file) >= sizeof(void *))
    ? 1 : -1 ];

#endif /* #ifndef cv_file_handle_h_ */
