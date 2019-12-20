/* See LICENSE for license details */

/*
 *
 */

#include <cv_coverage.h>

static long g_coverage_count = 0L;

static long g_coverage_limit = 0L;

/*
 *
 */

cv_bool cv_coverage_test(void) {
    g_coverage_count ++;
    return (g_coverage_count != g_coverage_limit);
}

/*
 *
 */

void cv_coverage_set(long i_count) {
    g_coverage_count = 0L;
    g_coverage_limit = i_count;
}

/*
 *
 */

long cv_coverage_query(void) {
    return g_coverage_count;
}

/* end-of-file: cv_coverage.c */
