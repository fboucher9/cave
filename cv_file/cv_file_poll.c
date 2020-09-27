/* See LICENSE for license details */

/*
 *  Module: cv_file_poll.h
 *
 *  Description: Poll read and write events for file descriptors.
 */

#include <cv_file/cv_file_poll.h>
#include <cv_file/cv_file.h>
#include <cv_memory.h>
#include <cv_debug/cv_debug.h>
#include <cv_heap/cv_heap.h>
#include <cv_misc/cv_limits.h>
#include <cv_algo/cv_unique.h>
#if defined cv_linux_
#include <poll.h>
#endif /* #if defined cv_linux_ */

#if defined cv_linux_

/* Predefine */
typedef union pollfd_ptr pollfd_ptr;

/*
 *
 */

union pollfd_ptr {
    void const * pc_void;
    void * p_void;
    struct pollfd const * pc_pollfd;
    struct pollfd * p_pollfd;
    cv_ptr o_ptr;
};

/*
 *
 */

static void cv_file_poll_linux_prepare( struct pollfd * p_pollfd,
    cv_file_poll * p_poll_min, unsigned i_count) {
    unsigned i_index = 0;
    for (i_index = 0; i_index < i_count; i_index++) {
        cv_file_poll * const p_file_poll = p_poll_min + i_index;
        p_pollfd[i_index].fd = cv_file_get_index(p_file_poll->p_file);
        if (cv_file_poll_flag_read & p_file_poll->i_flags_in) {
            p_pollfd[i_index].events |= POLLIN;
        }
        if (cv_file_poll_flag_write & p_file_poll->i_flags_in) {
            p_pollfd[i_index].events |= POLLOUT;
        }
        p_file_poll->i_flags_out = 0;
    }
}

/*
 *
 */

static void cv_file_poll_linux_return( struct pollfd * p_pollfd,
    cv_file_poll * p_poll_min, unsigned i_count) {
    unsigned i_index = 0;
    for (i_index = 0; i_index < i_count; i_index++) {
        cv_file_poll * const p_file_poll = p_poll_min + i_index;
        if (p_pollfd[i_index].revents & POLLIN) {
            p_file_poll->i_flags_out |= cv_file_poll_flag_read;
        }
        if (p_pollfd[i_index].revents & POLLOUT) {
            p_file_poll->i_flags_out |= cv_file_poll_flag_write;
        }
    }
}

/*
 *
 */

static cv_bool cv_file_poll_linux_dispatch( cv_file_poll * p_poll_min,
    unsigned i_count, cv_clock const * p_timeout) {
    cv_bool b_result = cv_false;
    (void)(p_timeout);
    cv_debug_assert_(p_poll_min && i_count > 0, cv_debug_code_null_ptr);
    {
        pollfd_ptr o_pollfd_ptr = {0};
        struct pollfd a_pollfd[1u];
        cv_uptr const i_pollfd_len = sizeof(struct pollfd) * i_count;
        if (1 >= i_count) {
            o_pollfd_ptr.p_pollfd = a_pollfd;
        } else {
            static unsigned char const a_pollfd_class[] = {
                'p', 'o', 'l', 'l', 'f', 'd' };
            static cv_unique g_pollfd_unique =
                cv_unique_initializer_(a_pollfd_class);
            cv_unique_next(&g_pollfd_unique);
            o_pollfd_ptr.p_void = cv_heap_alloc(i_pollfd_len,
                &g_pollfd_unique);
        }
        if (o_pollfd_ptr.p_pollfd) {
            struct pollfd * p_pollfd = o_pollfd_ptr.p_pollfd;
            cv_memory_zero(p_pollfd, i_pollfd_len);
            cv_file_poll_linux_prepare( p_pollfd, p_poll_min, i_count);
            {
                nfds_t const i_pollfd_count = i_count;
                int const i_poll_result = poll(
                    p_pollfd, i_pollfd_count, 1000);
                if (i_poll_result > 0) {
                    /* Update revents */
                    cv_file_poll_linux_return(
                        p_pollfd, p_poll_min, i_count);
                    b_result = cv_true;
                }
            }
        }
        if (1 >= i_count) {
        } else {
            if (o_pollfd_ptr.p_void) {
                cv_heap_free(o_pollfd_ptr.p_void);
            }
        }
    }
    return b_result;
}
#endif /* #if defined cv_linux_ */

/*
 *
 */

cv_bool cv_file_poll_dispatch(
    cv_file_poll * p_poll_min,
    unsigned i_count,
    cv_clock const * p_timeout)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_poll_min && (i_count > 0), cv_debug_code_null_ptr);
#if defined cv_linux_
    if (cv_file_poll_linux_dispatch(
        p_poll_min, i_count, p_timeout)) {
        b_result = cv_true;
    }
#else /* #if defined cv_linux_ */
    (void)(p_poll_min);
    (void)(i_count);
    (void)(p_timeout);
    cv_debug_msg_(cv_debug_code_not_implemented);
#endif /* #if defined cv_linux_ */
    return b_result;
}

