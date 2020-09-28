/* See LICENSE for license details */

#ifndef cv_trace_count_h_
#define cv_trace_count_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_misc/cv_types.h>
#include <cv_algo/cv_list_node.h>
#include <cv_algo/cv_list_it.h>
#include <cv_algo/cv_array.h>

/*
 *
 */

union cv_trace_count_ptr {
    void const * pc_void;
    void * p_void;
    cv_trace_count const * pc_trace_count;
    cv_trace_count * p_trace_count;
    cv_list_ptr o_list_ptr;
};

/*
 *
 */

struct cv_trace_count {

    /* list of counters */
    cv_list_node o_node;

    /* -- */

    /* name of parent object */
    char const * p_parent;

    /* name of counter */
    char const * p_name;

    /* -- */

    /* unique instance id for counter */
    cv_uptr i_instance;

    /* align to 64-bit */
    cv_uptr z_padding[1u];

    /* -- */

    cv_ull i_period_count;

    /* -- */

    cv_ull i_summary_count;

};

/*
 *
 */

void cv_trace_count_load(void);
void cv_trace_count_unload(void);
void cv_trace_count_init( cv_trace_count * p_this, char const * p_parent,
    char const * p_name );
void cv_trace_count_cleanup( cv_trace_count * p_this );
void cv_trace_count_add( cv_trace_count * p_this,
    cv_ull i_increment);

/*
 *
 */

struct cv_trace_count_it {
    cv_list_it o_list_it;
};

/*
 *
 */

void cv_trace_count_it_init( cv_trace_count_it * p_this );
void cv_trace_count_it_cleanup( cv_trace_count_it * p_this );
cv_bool cv_trace_count_it_next( cv_trace_count_it * p_this,
    cv_trace_count_ptr * r_trace_count_ptr);

#endif /* #ifndef cv_trace_count_h_ */

/* end-of-file: cv_trace_count.h */
