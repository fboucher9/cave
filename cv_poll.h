/* See LICENSE for license details */

#ifndef cv_poll_h_
#define cv_poll_h_

/*

poll manager

    -   standard files
    -   terminal or pseudo-terminal
    -   fifo pipe
    -   sockets
    -   etc.

*/

#include <cv_clock.h>

#define cv_poll_flag_read_ (1)

#define cv_poll_flag_write_ (2)

typedef void (cv_poll_notify)(
    void * p_context,
    cv_file_handle * p_file_handle,
    long i_flags);

typedef struct cv_poll_desc cv_poll_desc;

struct cv_poll_desc
{
    cv_poll_notify * p_notify;
    void * p_context;
    /* -- */
    cv_file_handle o_handle;
    /* -- */
    long i_flags;
    long l_padding[1u];
};

typedef struct cv_poll_node cv_poll_node;

struct cv_poll_node
{
    cv_node o_node;
    /* -- */
    cv_poll_desc o_desc;
};

typedef struct cv_poll_list cv_poll_list;

struct cv_poll_list
{
    cv_list o_list;
};

cv_bool cv_poll_dispatch(
    cv_poll_list const * p_poll_list,
    cv_clock const * p_timeout;

#endif /* #ifndef cv_poll_h_ */

/* end-of-file: cv_poll.h */
