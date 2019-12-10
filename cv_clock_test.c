/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock_test.h>
#include <cv_clock.h>
#include <cv_clock_mono.h>
#include <cv_test_print.h>
#include <cv_number_desc.h>

/*
 *
 */

void cv_clock_test(void) {
    {
        cv_clock o_value;
        if (cv_clock_read(&o_value, cv_clock_epoch_mono)) {
            cv_print_unsigned(o_value.i_seconds, cv_number_format_hex8());
            cv_print_char('.');
            cv_print_unsigned(o_value.i_fraction, cv_number_format_hex8());
            cv_print_nl();
        } else {
        }
    }
    {
        cv_clock_mono o_value;
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
}

/* end-of-file: cv_clock_test.c */
