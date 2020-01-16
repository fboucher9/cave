/* See LICENSE for license details */

#include <cv_trace/cv_trace_plugin.h>
#include <cv_thread/cv_specific.h>
#include <cv_trace/cv_trace_msg.h>

#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

extern struct cv_specific cv_trace_key;
struct cv_specific cv_trace_key;

void cv_trace_flush(void);

static void cv_trace_destructor(void * p_specific) {
    /* merge of thread data into global */
    /* no need to call pthread_setspecific(NULL) */
    (void)p_specific;
    cv_trace_flush();
    cv_trace_msg_flush();
    cv_trace_msg_thread_detach();
}

/*
 *
 */

void cv_trace_load(void) {
    cv_specific_init(&cv_trace_key, &cv_trace_destructor);
}

/*
 *
 */

void cv_trace_unload(void) {
    /* do profile report */
    /* Cleanup of remaining keys */
}

/* end-of-file: cv_trace_plugin.c */
