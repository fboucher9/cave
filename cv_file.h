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

#include <cv_file_pred.h>

#include <cv_file_impl.h>

#include <cv_bool.h>

#include <cv_string_pred.h>

cv_bool cv_file_init(
    cv_file * p_this,
    cv_file_desc const * p_desc);

void cv_file_cleanup(
    cv_file * p_this);

long cv_file_read(
    cv_file * p_this,
    cv_string const * p_string);

long cv_file_write(
    cv_file * p_this,
    cv_string const * p_string);

#endif /* #ifndef cv_file_h_ */
