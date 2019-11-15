/* See LICENSE for license details */

#ifndef cv_thread_desc_h_
#define cv_thread_desc_h_

#include <cv_thread_pred.h>

typedef void (cv_thread_func)(
    void * p_context);

struct cv_thread_desc
{
    cv_thread_func * p_func;
    void * p_context;
    char const * p_name0;
};

char cv_thread_desc_init(
    cv_thread_desc * p_this);

void cv_thread_desc_cleanup(
    cv_thread_desc * p_this);

#endif /* #ifndef cv_thread_desc_h_ */
