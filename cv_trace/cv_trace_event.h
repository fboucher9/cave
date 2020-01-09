/* See LICENSE for license details */

#ifndef cv_trace_event_h_
#define cv_trace_event_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_node.h>

#define cv_trace_event_decl_( level, name) \
    cv_trace_node_decl_( \
        cv_trace_type_event_signal, level, name)

#define cv_trace_event_signal_(name) \
    cv_trace_node_signal_(name)

#endif /* #ifndef cv_trace_event_h_ */

/* end-of-file: cv_trace_event.h */
