/* See LICENSE for license details */

#ifndef cv_file_h_
#define cv_file_h_

/*

Interface for files.  Files may be located on disk or may be devices such
as a terminal or a device driver.  Files are open in non-blocking mode so
that we may check for other tasks.

The wait functions may be used to detect when a read or write operation is
ready.  In linux the wait is implemented using the poll() system call and in
Windows, the WaitForSingleObject function is used.

*/

#include <cv_file/cv_file_pred.h>

#include <cv_misc/cv_bool.h>

#include <cv_algo/cv_array.h>

#include <cv_misc/cv_types.h>

union cv_file {

    /* Storage for POSIX file descriptor */
    int i_index;

    /* Alignment to pointer */
    void * p_void;

};

#define cv_file_initializer_ { -1 }

/* Compile-time verification of cv_file handle */
typedef char cv_verify_sizeof_file [
    (sizeof(cv_file) >= sizeof(int))
    && (sizeof(cv_file) >= sizeof(void *))
    ? 1 : -1 ];

void cv_file_init(
    cv_file * p_this);

void cv_file_cleanup(
    cv_file * p_this);

long cv_file_read(
    cv_file const * p_this,
    cv_array const * p_array);

long cv_file_write(
    cv_file const * p_this,
    cv_array const * p_array);

#endif /* #ifndef cv_file_h_ */
