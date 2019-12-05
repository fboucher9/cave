/* See LICENSE for license details */

#ifndef cv_thread_desc_h_
#define cv_thread_desc_h_

#include <cv_thread_pred.h>
#include <cv_array.h>
#include <cv_bool.h>

typedef void (cv_thread_func)(
    void * p_context);

typedef struct cv_thread_callback {
    cv_thread_func * p_func;
    void * p_context;
} cv_thread_callback;

#define cv_thread_callback_initializer_ \
{ cv_null_, cv_null_ }

struct cv_thread_desc {
    cv_thread_callback o_callback;
    /* -- */
    cv_array o_name;
};

#define cv_thread_desc_initializer_ \
{ cv_thread_callback_initializer_, cv_array_null_ }

void cv_thread_desc_init(
    cv_thread_desc * p_this);

void cv_thread_desc_cleanup(
    cv_thread_desc * p_this);

#endif /* #ifndef cv_thread_desc_h_ */
