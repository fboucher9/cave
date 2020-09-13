/* See LICENSE for license details */

#ifndef cv_trace_func_h_
#define cv_trace_func_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_algo/cv_array.h>
#include <cv_misc/cv_types.h>
#include <cv_misc/cv_bool.h>
#include <cv_algo/cv_list_node.h>
#include <cv_algo/cv_list_it.h>
#include <cv_trace/cv_trace_count.h>

union cv_trace_func_ptr {
    void const * pc_void;
    void * p_void;
    cv_trace_func const * pc_trace_func;
    cv_trace_func * p_trace_func;
    cv_list_ptr o_list_ptr;
};

/*
 *
 */

struct cv_trace_func {

    /* Linked list of functions */
    cv_list_node o_node;

    /* -- */

    /* Symbol for name */
    cv_array o_symbol;

    /* -- */

    /* Number of times the function is called */
    cv_trace_count o_call;

    /* -- */

    /* Amount of time elapsed within function call */
    cv_trace_count o_elapsed;

};

void cv_trace_func_load(void);
void cv_trace_func_unload(void);
void cv_trace_func_init( cv_trace_func * p_trace_func,
    cv_array const * p_name);
void cv_trace_func_cleanup( cv_trace_func * p_this);
void cv_trace_func_enter( cv_trace_func * p_this);
void cv_trace_func_leave(void);
/* this is used to substract time spent in sub functions */
void cv_trace_func_pause(void);
/* on return from subfunctions, resume clock */
void cv_trace_func_resume(void);

/* Iterator for list of functions, used by reports */

/*
 *
 */

struct cv_trace_func_it {
    cv_list_it o_list_it;
};

void cv_trace_func_it_init( cv_trace_func_it * p_this );
void cv_trace_func_it_cleanup( cv_trace_func_it * p_this );
cv_bool cv_trace_func_it_next( cv_trace_func_it * p_this,
    cv_trace_func_ptr * r_trace_func_ptr);

#endif /* #ifndef cv_trace_func_h_ */

/* end-of-file: cv_trace_func.h */
