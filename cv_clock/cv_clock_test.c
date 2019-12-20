/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock/cv_clock_test.h>
#include <cv_clock/cv_clock.h>
#include <cv_clock/cv_clock_it.h>
#include <cv_clock/cv_clock_mono.h>
#include <cv_clock/cv_clock_mono_it.h>
#include <cv_clock/cv_clock_duration.h>
#include <cv_clock/cv_clock_tool.h>
#include <cv_clock/cv_clock_info.h>
#include <cv_clock/cv_clock_counter.h>
#include <cv_test_print.h>
#include <cv_number/cv_number_desc.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_misc/cv_unused.h>

/*
 *
 */

static void cv_clock_test_unix_1(void) {
    cv_clock o_value = cv_clock_initializer_;
    if (cv_clock_read(&o_value, cv_clock_epoch_unix)) {
    }
}

/*
 *
 */

static void cv_clock_test_mono_1(void) {
    cv_clock_mono o_clock_mono = cv_clock_mono_initializer_;
    cv_clock_mono_init(&o_clock_mono);
    cv_clock_mono_read(&o_clock_mono);
    cv_clock_mono_until(&o_clock_mono);
    {
        cv_clock_info o_clock_info = cv_clock_info_initializer_;
        cv_clock_mono_info(&o_clock_mono, &o_clock_info);
    }
    {
        cv_clock_duration o_clock_duration = cv_clock_duration_initializer_;
        cv_clock_mono_diff(&o_clock_mono, &o_clock_mono, &o_clock_duration);
    }
    {
        cv_clock_mono_it o_clock_mono_it = cv_clock_mono_it_initializer_;
        cv_clock_duration o_clock_duration = cv_clock_duration_initializer_;
        o_clock_duration.o_clock.i_seconds = 1;
        o_clock_duration.o_clock.i_fraction = 0;
        cv_clock_mono_it_init(&o_clock_mono_it, &o_clock_mono);
        cv_clock_mono_it_next(&o_clock_mono_it, &o_clock_duration);
        cv_clock_mono_it_cleanup(&o_clock_mono_it);
    }
    cv_clock_mono_cleanup(&o_clock_mono);
}

/*
 *
 */

static void cv_clock_test_counter_1(void) {
    cv_clock_counter o_clock_counter = cv_clock_counter_initializer_;
    cv_clock_counter_init(&o_clock_counter);
    cv_clock_counter_set(&o_clock_counter, 12345UL);
    {
        cv_ull ll_value = 0;
        ll_value = cv_clock_counter_get(&o_clock_counter);
        cv_unused_(ll_value);
    }
    cv_clock_counter_inc(&o_clock_counter);
    cv_clock_counter_dec(&o_clock_counter);
    cv_clock_counter_add(&o_clock_counter, 42UL);
    cv_clock_counter_sub(&o_clock_counter, 42UL);
    cv_clock_counter_cleanup(&o_clock_counter);
}

/*
 *
 */

static void cv_clock_test_duration_1(void) {
    {
        cv_clock_duration o_clock_duration = cv_clock_duration_initializer_;
        cv_clock_duration_init(&o_clock_duration);
        cv_clock_duration_cleanup(&o_clock_duration);
    }
    {
        cv_clock_duration o_clock_duration = cv_clock_duration_initializer_;
        cv_clock_duration_init_msec(&o_clock_duration, 0, 100UL);
        cv_clock_duration_until(&o_clock_duration);
#if 0 /* not used yet */
        {
            cv_clock_info o_clock_info = cv_clock_info_initializer_;
            cv_clock_duration_info(&o_clock_duration, &o_clock_info);
        }
#endif /* not used yet */
        {
            cv_clock_duration o_clock_duration_min =
                cv_clock_duration_initializer_;
            cv_clock_duration_min(&o_clock_duration, &o_clock_duration,
                &o_clock_duration_min);
        }
        cv_clock_duration_cleanup(&o_clock_duration);
    }
    {
        cv_clock_duration o_clock_duration = cv_clock_duration_initializer_;
        cv_clock_duration_init_usec(&o_clock_duration, 1, 999999UL);
        cv_clock_duration_cleanup(&o_clock_duration);
    }
    {
        cv_clock_duration o_clock_duration = cv_clock_duration_initializer_;
        cv_clock_duration_init_nsec(&o_clock_duration, 1, 999999999UL);
        cv_clock_duration_cleanup(&o_clock_duration);
    }
}

/*
 *
 */

void cv_clock_test(void) {
    cv_clock_test_unix_1();
    cv_clock_test_mono_1();
    cv_clock_test_counter_1();
    cv_clock_test_duration_1();
    {
        cv_clock o_value = cv_clock_initializer_;
        if (cv_clock_read(&o_value, cv_clock_epoch_mono)) {
            cv_print_unsigned(o_value.i_seconds, cv_number_format_dec());
            cv_print_char('.');
            cv_print_unsigned(o_value.i_fraction, cv_number_format_hex8());
            cv_print_nl();
            {
                cv_clock_msec o_value_msec = cv_clock_msec_initializer_;
                cv_clock_get_msec(&o_value, &o_value_msec);
                cv_print_unsigned(o_value_msec.i_seconds,
                    cv_number_format_dec());
                cv_print_char('.');
                cv_print_unsigned(o_value_msec.i_mseconds,
                    cv_number_format_dec());
                cv_print_nl();
            }
            {
                cv_clock_usec o_value_usec = cv_clock_usec_initializer_;
                cv_clock_get_usec(&o_value, &o_value_usec);
                cv_print_unsigned(o_value_usec.i_seconds,
                    cv_number_format_dec());
                cv_print_char('.');
                cv_print_unsigned(o_value_usec.i_useconds,
                    cv_number_format_dec());
                cv_print_nl();
            }
            {
                cv_clock_nsec o_value_nsec = cv_clock_nsec_initializer_;
                cv_clock_get_nsec(&o_value, &o_value_nsec);
                cv_print_unsigned(o_value_nsec.i_seconds,
                    cv_number_format_dec());
                cv_print_char('.');
                cv_print_unsigned(o_value_nsec.i_nseconds,
                    cv_number_format_dec());
                cv_print_nl();
            }
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
                o_max_sleep.o_clock.i_seconds = 2;
                o_max_sleep.o_clock.i_fraction = 0;
                while (cv_clock_it_next(&o_clock_it, &o_max_sleep)) {
                    static unsigned char const a_msg[] = {
                        'n', 'e', 'x', 't', '.', '.', '.' };
                    cv_print_vector(a_msg, cv_sizeof_(a_msg));
                    cv_print_nl();
                }
                cv_clock_duration_cleanup(&o_max_sleep);
            }
            cv_clock_it_cleanup(&o_clock_it);
        }
    }
}

/* end-of-file: cv_clock_test.c */
