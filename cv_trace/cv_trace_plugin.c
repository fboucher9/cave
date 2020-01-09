/* See LICENSE for license details */

#include <cv_trace/cv_trace_plugin.h>

#if defined cv_have_pthread_
#include <pthread.h>
#endif /* #if defined cv_have_pthread_ */

#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

#if defined cv_have_pthread_
extern pthread_key_t cv_trace_key;
pthread_key_t cv_trace_key;
#endif /* #if defined cv_have_pthread_ */

#if defined cv_have_pthread_
static void cv_trace_destructor(void * p_specific) {
    /* merge of thread data into global */
    /* no need to call pthread_setspecific(NULL) */
    (void)p_specific;
#if defined cv_have_libc_
    fprintf(stdout, "*** pthread_key_destructor ***\n");
#endif /* #if defined cv_have_libc_ */
}
#endif /* #if defined cv_have_pthread_ */

/*
 *
 */

void cv_trace_load(void) {
#if defined cv_have_pthread_
    pthread_key_create(&cv_trace_key, &cv_trace_destructor);
#endif /* #if defined cv_have_pthread_ */
}

/*
 *
 */

void cv_trace_unload(void) {
    /* do profile report */
    /* Cleanup of remaining keys */
}

/* end-of-file: cv_trace_plugin.c */
