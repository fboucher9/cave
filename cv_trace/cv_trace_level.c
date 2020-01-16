/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_level.h>

static unsigned char g_stack_levels = 8u;

static unsigned char g_profile_levels = 8u;

static unsigned char g_echo_levels = 8u;

static unsigned char g_log_levels = 8u;

/*
 *
 */

void cv_trace_set_stack_levels( unsigned char i_stack_levels) {
    g_stack_levels = i_stack_levels;
}

/*
 *
 */

void cv_trace_set_profile_levels( unsigned char i_profile_levels) {
    g_profile_levels = i_profile_levels;
}

/*
 *
 */

void cv_trace_set_echo_levels(unsigned char i_echo_levels) {
    g_echo_levels = i_echo_levels;
}

/*
 *
 */

void cv_trace_set_log_levels(unsigned char i_log_levels) {
    g_log_levels = i_log_levels;
}

/*
 *
 */

cv_bool cv_trace_test_stack_level(unsigned char i_level) {
    return (i_level < g_stack_levels) ? cv_true : cv_false;
}

/*
 *
 */

cv_bool cv_trace_test_profile_level(unsigned char i_level) {
    return (i_level < g_profile_levels) ? cv_true : cv_false;
}

/*
 *
 */

cv_bool cv_trace_test_echo_level(unsigned char i_level) {
    return (i_level < g_echo_levels) ? cv_true : cv_false;
}

/*
 *
 */

cv_bool cv_trace_test_log_level(unsigned char i_level) {
    return (i_level < g_log_levels) ? cv_true : cv_false;
}

/* end-of-file: cv_trace_level.c */
