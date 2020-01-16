/* See LICENSE for license details */

#ifndef cv_trace_level_
#define cv_trace_level_

/*
 *
 */

#include <cv_misc/cv_bool.h>

void cv_trace_set_stack_levels(unsigned char i_stack_levels);

void cv_trace_set_profile_levels( unsigned char i_profile_levels);

void cv_trace_set_echo_levels(unsigned char i_echo_levels);

void cv_trace_set_log_levels(unsigned char i_log_levels);

cv_bool cv_trace_test_stack_level(unsigned char i_level);

cv_bool cv_trace_test_profile_level(unsigned char i_level);

cv_bool cv_trace_test_echo_level(unsigned char i_level);

cv_bool cv_trace_test_log_level(unsigned char i_level);

#endif /* #ifndef cv_trace_level_ */

/* end-of-file: cv_trace_level.h */
