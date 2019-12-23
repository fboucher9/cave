/* See LICENSE for license details */

/*
 *
 */

#include <cv_random/cv_random_test.h>
#include <cv_random/cv_random.h>
#include <cv_debug/cv_debug.h>
#include <cv_test_print.h>
#include <cv_number/cv_number_format.h>

/*
 *
 */

static void cv_random_test_step(
    unsigned long i_seed,
    unsigned long i_count,
    unsigned long i_modulo,
    unsigned long i_result) {
    unsigned long i_value = 0;
    struct cv_random o_random = cv_random_initializer_;
    cv_random_init(&o_random, i_seed);
    while (i_count) {
        i_value = cv_random_pick(&o_random, i_modulo);
        i_count --;
    }
    cv_random_cleanup(&o_random);
    cv_debug_assert_(i_value == i_result, cv_debug_code_error);
}

/*
 *
 */

void cv_random_test(cv_options_it * p_options_it) {
    (void)p_options_it;
    cv_random_test_step(12345UL, 10, 52, 49);
}

/* end-of-file: cv_random_test.c */
