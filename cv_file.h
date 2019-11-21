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

#include <cv_types.h>

#include <cv_bool.h>

union cv_file_data
{
    cv_sll ll_align;

    void * p_void;

    int i_index;

};

#define cv_file_data_initializer { 0 }

struct cv_file
{
    union cv_file_data o_data;
};

#define cv_file_initializer_ { cv_file_data_initializer_ }

long cv_file_sizeof(void);

cv_bool cv_file_init(
    cv_file * p_this,
    cv_file_desc const * p_desc);

void cv_file_cleanup(
    cv_file * p_this);

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

cv_bool cv_file_wait_read(
    cv_file * p_this,
    cv_clock const * p_clock);

cv_bool cv_file_wait_write(
    cv_file * p_this,
    cv_clock const * p_clock);

#endif /* #ifndef cv_file_h_ */
