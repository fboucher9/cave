/* See LICENSE for license details */

#ifndef cv_file_poll_h_
#define cv_file_poll_h_

/*
 *  Module: cv_file_poll.h
 *
 *  Description: Poll read and write events for file descriptors.
 */

#include <cv_file/cv_file_pred.h>
#include <cv_clock/cv_clock_pred.h>
#include <cv_misc/cv_bool.h>

/*
 *  Enumeration: cv_file_poll_flag
 *
 *  Description: Indicate types of events to be polled for each file
 *  descriptor.
 */

enum cv_file_poll_flag {
    cv_file_poll_flag_read = 1,
    cv_file_poll_flag_write = 2
};

/*
 *  Structure: cv_file_poll
 *
 *  Description: Poll information for a single file descriptor.
 */

struct cv_file_poll {
    cv_file const * p_file;
    /* -- */
    long i_flags_in;
    long i_flags_out;
};

void cv_file_poll_init( cv_file_poll * p_this);
void cv_file_poll_cleanup( cv_file_poll * p_this);
cv_bool cv_file_poll_dispatch( cv_file_poll * p_poll_min, unsigned i_count,
    cv_clock const * p_timeout);

#endif /* #ifndef cv_file_poll_h_ */

/* end-of-file: cv_file_poll.h */
