/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_event.h>

/*
 *
 */

void cv_trace_event_signal( cv_trace_event * p_trace_event) {
    cv_trace_node_dispatch( &p_trace_event->o_trace_node,
        cv_trace_type_event_signal);
}

/* end-of-file: cv_trace_event.c */
