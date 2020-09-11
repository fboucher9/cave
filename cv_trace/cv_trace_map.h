/* See LICENSE for license details */

#ifndef cv_trace_map_h_
#define cv_trace_map_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_algo/cv_array.h>
#include <cv_misc/cv_types.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_trace_map {

    /* name */
    cv_array o_name;

    /* -- */

    /* memory mapped file */
    cv_array o_total_region;

    /* -- */

    /* allocator for memory regions */
    cv_array o_avail_region;

};

cv_bool cv_trace_map_init( cv_trace_map * p_this, cv_array const * p_name,
    cv_uptr i_length);
void cv_trace_map_cleanup( cv_trace_map * p_this);
void * cv_trace_map_alloc( cv_trace_map * p_this, cv_uptr i_length);

#endif /* #ifndef cv_trace_map_h_ */

/* end-of-file: cv_trace_map.h */
