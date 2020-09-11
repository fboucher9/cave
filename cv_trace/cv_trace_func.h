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

    /* Counter for number of calls */
    cv_ull i_count;

    /* -- */

    /* Elapsed time in ticks */
    cv_ull i_elapsed;

};

void cv_trace_func_load(void);
void cv_trace_func_unload(void);
void cv_trace_func_init( cv_trace_func * p_trace_func,
    cv_array const * p_name);
void cv_trace_func_cleanup( cv_trace_func * p_this);
cv_array const * cv_trace_func_get_symbol( cv_trace_func const * p_this);
void cv_trace_func_enter( cv_trace_func * p_this);
void cv_trace_func_leave(void);
/* this is used to substract time spent in sub functions */
void cv_trace_func_pause(void);
/* on return from subfunctions, resume clock */
void cv_trace_func_resume(void);

#endif /* #ifndef cv_trace_func_h_ */

/* end-of-file: cv_trace_func.h */
