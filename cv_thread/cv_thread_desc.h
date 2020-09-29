/* See LICENSE for license details */

#ifndef cv_thread_desc_h_
#define cv_thread_desc_h_

#include <cv_thread/cv_thread_pred.h>
#include <cv_algo/cv_array.h>
#include <cv_misc/cv_bool.h>

typedef void (cv_thread_func)( void * p_context);

typedef struct cv_thread_callback {
    cv_thread_func * p_func;
    void * p_context;
} cv_thread_callback;

struct cv_thread_desc {
    cv_thread_callback o_callback;
    /* -- */
    cv_array o_name;
};

void cv_thread_desc_load(void);
void cv_thread_desc_unload(void);
cv_thread_desc * cv_thread_desc_cast(void * p_placement);
void cv_thread_desc_init( cv_thread_desc * p_this);
void cv_thread_desc_cleanup( cv_thread_desc * p_this);
cv_thread_desc * cv_thread_desc_create(void);
void cv_thread_desc_destroy( cv_thread_desc * p_this);

#endif /* #ifndef cv_thread_desc_h_ */
