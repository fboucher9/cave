/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_unicode_test.h>
#include <cv_unicode/cv_utf16.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_it.h>
#include <cv_test_print.h>

/*
 *
 */

void cv_unicode_test(void) {
    {
        static unsigned char const a_input[] = {
            0x12, 0x34
        };
        static cv_array const g_input =
            cv_array_initializer_(a_input, a_input + sizeof a_input);
        cv_array_it o_input;
        cv_array_it_init(&o_input, &g_input);
        {
            unsigned long i_output = 0;
            if (cv_utf16be_decode(&o_input, &i_output)) {
                cv_print_hex(i_output);
                cv_print_nl();
            }
        }
        cv_array_it_cleanup(&o_input);
    }

    {
        unsigned char a_storage[2u];
        cv_array o_storage;
        cv_array_it o_output;
        cv_array_init_vector(&o_storage, a_storage, sizeof a_storage);
        cv_array_it_init(&o_output, &o_storage);
        {
            if (cv_utf16be_encode(0x1234ul, &o_output)) {
                cv_print_0("0x", 2);
                cv_print_hex(a_storage[0u]);
                cv_print_0(", 0x", 80);
                cv_print_hex(a_storage[1u]);
                cv_print_nl();
            }
        }
        cv_array_it_cleanup(&o_output);
        cv_array_cleanup(&o_storage);
    }

}

/* end-of-file: cv_unicode_test.c */
