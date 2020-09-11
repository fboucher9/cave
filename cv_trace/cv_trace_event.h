/* See LICENSE for license details */

#ifndef cv_trace_event_h_
#define cv_trace_event_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_algo/cv_array_pred.h>

cv_trace_event * cv_trace_event_create( cv_trace_map * p_trace_map,
    cv_array const * p_name);
void cv_trace_event_destroy( cv_trace_event * p_this);
cv_array const * cv_trace_event_get_name( cv_trace_event * p_this);
void cv_trace_event_inc( cv_trace_event * p_this);
void cv_trace_event_add( cv_trace_event * p_this, unsigned long i_value);

#endif /* #ifndef cv_trace_event_h_ */

/* end-of-file: cv_trace_event.h */
