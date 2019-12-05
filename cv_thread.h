/* See LICENSE for license details */

#ifndef cv_thread_h_
#define cv_thread_h_

/*

Thread abstraction layer.  Abstraction of pthread thread handles.  These
functions define an OS-independant way of creating threads.  Descriptor
is used to start a thread with all required attributes.  The thread is
automatically joined before destruction.  If the thread is in detached state
then the join step is automatically skipped.

*/

#include <cv_thread_pred.h>
#include <cv_thread_impl.h>

cv_bool cv_thread_init(
    cv_thread * p_this,
    cv_thread_desc const * p_thread_desc);

void cv_thread_cleanup(
    cv_thread * p_this);

/*

Note: use of interrupt is not portable.  Look into more portable ways of
unblocking thread that are blocked.  An implementation of interrupt exists for
linux and windows, not sure for other platforms.

*/

void cv_thread_interrupt(
    cv_thread * p_this);

#endif /* #ifndef cv_thread_h_ */
