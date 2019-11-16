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

cv_file * cv_file_create(
    cv_file_desc const * p_desc);

void cv_file_destroy(
    cv_file * p_this);

long cv_file_read(
    cv_file * p_this,
    cv_buffer const * p_buffer);

long cv_file_write(
    cv_file * p_this,
    cv_buffer const * p_buffer);

char cv_file_wait_read(
    cv_file * p_this,
    cv_clock const * p_clock);

char cv_file_wait_write(
    cv_file * p_this,
    cv_clock const * p_clock);

#endif /* #ifndef cv_file_h_ */
