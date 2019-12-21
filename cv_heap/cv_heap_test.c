/* See LICENSE for license details */

/*
 *
 */

#include <cv_heap/cv_heap_test.h>
#include <cv_heap/cv_heap.h>
#include <cv_thread/cv_thread.h>
#include <cv_options/cv_options_it.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_tool.h>

/*
 *
 */

static void cv_heap_test_stress(cv_options_it * p_options_it) {
    /* create threads */
    /* allocate memory */
    /* write memory */
    /* read memory */
    /* free memory */
    /* sleep */
    (void)p_options_it;
}

/*
 *
 */

void cv_heap_test(cv_options_it * p_options_it) {
    static unsigned char const a_stress[] = {
        's', 't', 'r', 'e', 's', 's' };
    static cv_array const g_stress =
        cv_array_text_initializer_(a_stress);
    cv_array o_argument = cv_array_null_;
    cv_array_init(&o_argument);
    if (cv_options_it_next(p_options_it, &o_argument)) {
        if (cv_array_compare(&o_argument, &g_stress)) {
            cv_heap_test_stress(p_options_it);
        } else {
        }
    } else {
    }
    cv_array_cleanup(&o_argument);
}

/* end-of-file: cv_heap_test.c */
