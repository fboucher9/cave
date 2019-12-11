/* See LICENSE for license details */

#ifndef cv_file_poll_h_
#define cv_file_poll_h_

#include <cv_file/cv_file_pred.h>
#include <cv_clock/cv_clock_pred.h>
#include <cv_misc/cv_bool.h>

enum cv_file_poll_flag {
    cv_file_poll_flag_read = 1,
    cv_file_poll_flag_write = 2
};

struct cv_file_poll {
    cv_file const * p_file;
    /* -- */
    long i_flags_in;
    long i_flags_out;
};

#define cv_file_poll_initializer_ \
{ cv_null_, 0, 0 }

cv_bool cv_file_poll_dispatch(
    cv_file_poll * p_poll_min,
    long i_count,
    cv_clock const * p_timeout);

#endif /* #ifndef cv_file_poll_h_ */

/* end-of-file: cv_file_poll.h */