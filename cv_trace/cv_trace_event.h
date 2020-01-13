/* See LICENSE for license details */

#ifndef cv_trace_event_h_
#define cv_trace_event_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_trace/cv_trace_node.h>

#define cv_trace_event_decl_( level, name) \
    cv_trace_decl_( \
        cv_trace_klass_event, level, name)

#define cv_trace_event_signal_(name) \
    cv_trace_signal_(name)

#define cv_trace_event0_decl_(name) \
    cv_trace_event_decl_(cv_trace_level_0, name)

#define cv_trace_event0_signal_(name) \
    cv_trace_event_signal_(name)

#define cv_trace_event1_decl_(name) \
    cv_trace_event_decl_(cv_trace_level_1, name)

#define cv_trace_event1_signal_(name) \
    cv_trace_event_signal_(name)

#define cv_trace_event2_decl_(name) \
    cv_trace_event_decl_(cv_trace_level_2, name)

#define cv_trace_event2_signal_(name) \
    cv_trace_event_signal_(name)

#define cv_trace_event3_decl_(name) \
    cv_trace_event_decl_(cv_trace_level_3, name)

#define cv_trace_event3_signal_(name) \
    cv_trace_event_signal_(name)

#define cv_trace_event4_decl_(name) \
    cv_trace_event_decl_(cv_trace_level_4, name)

#define cv_trace_event4_signal_(name) \
    cv_trace_event_signal_(name)

#define cv_trace_event5_decl_(name) \
    cv_trace_event_decl_(cv_trace_level_5, name)

#define cv_trace_event5_signal_(name) \
    cv_trace_event_signal_(name)

#define cv_trace_event6_decl_(name) \
    cv_trace_event_decl_(cv_trace_level_6, name)

#define cv_trace_event6_signal_(name) \
    cv_trace_event_signal_(name)

#define cv_trace_event7_decl_(name) \
    cv_trace_event_decl_(cv_trace_level_7, name)

#define cv_trace_event7_signal_(name) \
    cv_trace_event_signal_(name)

#endif /* #ifndef cv_trace_event_h_ */

/* end-of-file: cv_trace_event.h */
