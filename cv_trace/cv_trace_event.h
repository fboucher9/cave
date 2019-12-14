/* See LICENSE for license details */

#ifndef cv_trace_event_h_
#define cv_trace_event_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_node.h>

struct cv_trace_event {
    cv_trace_node o_trace_node;
};

#define cv_trace_event_initializer_(level, text) \
{ cv_trace_node_initializer_(level, text) }

void cv_trace_event_signal( cv_trace_event * p_trace_event);

#endif /* #ifndef cv_trace_event_h_ */

/* end-of-file: cv_trace_event.h */
