/* See LICENSE for license details */

#ifndef cv_trace_pred_h_
#define cv_trace_pred_h_

#define cv_trace_levels_ 1

/*
 *
 */

typedef struct cv_trace_stats cv_trace_stats;

typedef struct cv_trace_node cv_trace_node;

typedef struct cv_trace_msg cv_trace_msg;

typedef struct cv_trace_func cv_trace_func;

#if (cv_trace_levels_ > 0)
typedef struct cv_trace_func0 cv_trace_func0;
#endif

#if (cv_trace_levels_ > 1)
typedef struct cv_trace_func1 cv_trace_func1;
#endif

#if (cv_trace_levels_ > 2)
typedef struct cv_trace_func2 cv_trace_func2;
#endif

#if (cv_trace_levels_ > 3)
typedef struct cv_trace_func3 cv_trace_func3;
#endif

#if (cv_trace_levels_ > 4)
typedef struct cv_trace_func4 cv_trace_func4;
#endif

#if (cv_trace_levels_ > 5)
typedef struct cv_trace_func5 cv_trace_func5;
#endif

#if (cv_trace_levels_ > 6)
typedef struct cv_trace_func6 cv_trace_func6;
#endif

#if (cv_trace_levels_ > 7)
typedef struct cv_trace_func7 cv_trace_func7;
#endif

typedef struct cv_trace_event cv_trace_event;

#if (cv_trace_levels_ > 0)
typedef struct cv_trace_event0 cv_trace_event0;
#endif

#if (cv_trace_levels_ > 1)
typedef struct cv_trace_event1 cv_trace_event1;
#endif

#if (cv_trace_levels_ > 2)
typedef struct cv_trace_event2 cv_trace_event2;
#endif

#if (cv_trace_levels_ > 3)
typedef struct cv_trace_event3 cv_trace_event3;
#endif

#if (cv_trace_levels_ > 4)
typedef struct cv_trace_event4 cv_trace_event4;
#endif

#if (cv_trace_levels_ > 5)
typedef struct cv_trace_event5 cv_trace_event5;
#endif

#if (cv_trace_levels_ > 6)
typedef struct cv_trace_event6 cv_trace_event6;
#endif

#if (cv_trace_levels_ > 7)
typedef struct cv_trace_event7 cv_trace_event7;
#endif

#endif /* #ifndef cv_trace_pred_h_ */

/* end-of-file: cv_trace_pred.h */
