/* See LICENSE for license details */

#include <cv_file_poll.h>

#include <cv_file.h>

#include <cv_unused.h>

#include <cv_memory.h>

#include <cv_sizeof.h>

#include <cv_debug.h>

#if defined cv_have_libc_
#include <poll.h>
#endif /* #if defined cv_have_libc_ */

cv_bool cv_file_poll_dispatch(
    cv_file_poll * p_poll_min,
    cv_file_poll * p_poll_max,
    cv_clock const * p_timeout)
{
    cv_bool b_result = cv_false;

    cv_debug_assert_(p_poll_min && p_poll_max, "null ptr");
    cv_unused_(p_timeout);
#if defined cv_have_libc_
    if (1 == (p_poll_max - p_poll_min)) {
        struct pollfd a_pollfd[1u];
        cv_memory_zero(a_pollfd, cv_sizeof_(a_pollfd));
        a_pollfd[0].fd = p_poll_min->p_file->i_index;
        if (cv_file_poll_flag_read & p_poll_min->i_flags_in) {
            a_pollfd[0].events |= POLLIN;
        }
        if (cv_file_poll_flag_write & p_poll_min->i_flags_in) {
            a_pollfd[0].events |= POLLOUT;
        }
        p_poll_min->i_flags_out = 0;
        {
            int const i_poll_result = poll(a_pollfd, 1, 1000);
            if (i_poll_result > 0) {
                /* Update revents */
                if (a_pollfd[0].revents & POLLIN) {
                    p_poll_min->i_flags_out |= cv_file_poll_flag_read;
                }
                if (a_pollfd[0].revents & POLLOUT) {
                    p_poll_min->i_flags_out |= cv_file_poll_flag_write;
                }
                b_result = cv_true;
            }
        }
    }
#endif /* #if defined cv_have_libc_ */
    return b_result;
}

