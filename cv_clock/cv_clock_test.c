/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock/cv_clock_test.h>
#include <cv_clock/cv_clock.h>
#include <cv_clock/cv_clock_mono.h>
#include <cv_clock/cv_clock_it.h>
#include <cv_clock/cv_clock_duration.h>
#include <cv_test_print.h>
#include <cv_number_desc.h>

/*
 *
 */

void cv_clock_test(void) {
    {
        cv_clock o_value = cv_clock_initializer_;
        if (cv_clock_read(&o_value, cv_clock_epoch_mono)) {
            cv_print_unsigned(o_value.i_seconds, cv_number_format_hex8());
            cv_print_char('.');
            cv_print_unsigned(o_value.i_fraction, cv_number_format_hex8());
            cv_print_nl();
        } else {
        }
    }
    {
        cv_clock_mono o_value = cv_clock_mono_initializer_;
        if (cv_clock_mono_read(&o_value)) {
            cv_print_unsigned(o_value.o_clock.i_seconds,
                cv_number_format_hex8());
            cv_print_char('.');
            cv_print_unsigned(o_value.o_clock.i_fraction,
                cv_number_format_hex8());
            cv_print_nl();
        } else {
        }
    }
    /* Try the iterator */
    {
        cv_clock o_target = cv_clock_initializer_;
        if (cv_clock_read(&o_target, cv_clock_epoch_mono)) {
            cv_clock_it o_clock_it = cv_clock_it_initializer_;
            o_target.i_seconds += 5;
            cv_clock_it_init(&o_clock_it, &o_target, cv_clock_epoch_mono);
            {
                cv_clock_duration o_max_sleep = cv_clock_duration_initializer_;
                cv_clock_duration_init(&o_max_sleep);
                o_max_sleep.o_clock.i_seconds = 1;
                o_max_sleep.o_clock.i_fraction = 0;
                cv_clock_it_next(&o_clock_it, &o_max_sleep);
                cv_clock_duration_cleanup(&o_max_sleep);
            }
            cv_clock_it_cleanup(&o_clock_it);
        }
    }
}

/* end-of-file: cv_clock_test.c */
