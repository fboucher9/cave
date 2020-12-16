/* See LICENSE for license details */

/*
 *
 */

#include <cv_random/cv_random_test.h>
#include <cv_random/cv_random.h>
#include <cv_random/cv_random_crypto.h>
#include <cv_random/cv_random_tiny.h>
#include <cv_debug/cv_debug.h>
#include <cv_test_print.h>
#include <cv_number/cv_number_format.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_options/cv_options_it.h>

/*
 *
 */

static void cv_random_test_step(
    unsigned long i_seed) {
    unsigned long i_value = 0;
    struct cv_random o_random;
    cv_random_init(&o_random, i_seed);
    i_value = cv_random_pick(&o_random, 0);
    (void)i_value;
    cv_random_cleanup(&o_random);
}

/*
 *
 */

static void cv_random_test_crypto_1(void) {
    struct cv_random_crypto o_crypto;
    if (cv_random_crypto_init(&o_crypto)) {
        unsigned long const i_value = cv_random_crypto_pick(&o_crypto, 0);
        cv_print_unsigned(i_value, cv_number_format_hex8());
        cv_print_nl();
        cv_random_crypto_cleanup(&o_crypto);
    }
}

/*
 *
 */

static void cv_random_test_bench_1(void) {
    struct cv_random o_random;
    unsigned long i_count = 10ul * 1000ul * 1000ul;
    unsigned long i_value = 0;
    cv_random_init(&o_random, 12345ul);
    while (i_count) {
        i_value = cv_random_pick(&o_random, 0);
        i_count --;
    }
    (void)i_value;
    cv_random_cleanup(&o_random);
}

/*
 *
 */

static void cv_random_test_bench_2(void) {
    struct cv_random_tiny o_random;
    unsigned long i_count = 10ul * 1000ul * 1000ul;
    unsigned long i_value = 0;
    cv_random_tiny_init(&o_random, 12345ul);
    while (i_count) {
        i_value = cv_random_tiny_pick(&o_random, 0) & 0xfffffffful;
        i_count --;
    }
    (void)i_value;
    cv_random_tiny_cleanup(&o_random);
}

/*
 *
 */

static void cv_random_test_check_pcg(
    unsigned long i_seed,
    unsigned long i_count) {
    struct cv_random o_random;
    unsigned long i_iterator = i_count;
    unsigned long i_value = 0;
    cv_random_init(&o_random, i_seed);
    cv_print_0("PCG", 80);
    cv_print_nl();
    while (i_iterator) {
        i_value = cv_random_pick(&o_random, 0) & 0xfffffffful;
        cv_print_unsigned(i_value, cv_number_format_dec10());
        cv_print_nl();
        i_iterator --;
    }
    {
        /* count bits during 1 million iterations */
        signed long a_bits[32u];
        signed long i_bits_all;
        unsigned char i_index;

        i_bits_all = 0;
        for (i_index = 0; i_index < 32; i_index ++) {
            a_bits[i_index] = 0;
        }

        i_iterator = 1024ul * 1024ul;
        while (i_iterator) {
            i_value = cv_random_pick(&o_random, 0) & 0xfffffffful;
            for (i_index = 0; i_index < 32u; i_index ++) {
                if (i_value & (1ul << i_index)) {
                    a_bits[i_index] ++;
                    i_bits_all ++;
                } else {
                    a_bits[i_index] --;
                    i_bits_all --;
                }
            }
            i_iterator --;
        }

        cv_print_0("-> bits:", 80);
        for (i_index = 0; i_index < 32u; i_index ++) {
            cv_print_signed(a_bits[i_index], cv_number_format_dec());
        }
        cv_print_nl();
        cv_print_0("-> total:", 80);
        cv_print_signed(i_bits_all, cv_number_format_dec());
        cv_print_nl();
    }
}

/*
 *
 */

static void cv_random_test_check_tiny(
    unsigned long i_seed,
    unsigned long i_count) {
    struct cv_random_tiny o_random;
    unsigned long i_iterator = i_count;
    unsigned long i_value = 0;
    cv_random_tiny_init(&o_random, i_seed);
    cv_print_0("TINY", 80);
    cv_print_nl();
    while (i_iterator) {
        i_value = cv_random_tiny_pick(&o_random, 0) & 0xfffffffful;
        cv_print_unsigned(i_value, cv_number_format_dec10());
        cv_print_nl();
        i_iterator --;
    }
    cv_random_tiny_cleanup(&o_random);
}

/*
 *
 */

static void cv_random_test_print_1(void) {
    static unsigned char a_bytes[1024u];
    struct cv_random o_random;
    char b_continue = 1;
    unsigned int i_offset = 0;
    cv_random_init(&o_random, 12345);
    while (b_continue) {
        unsigned long const i_value = cv_random_pick(&o_random, 0) & 0xffffffff;
        unsigned long const i_temp_1 = (i_value >> 24u);
        unsigned long const i_temp_2 = (i_value >> 16u);
        unsigned long const i_temp_3 = (i_value >> 8u);
        a_bytes[i_offset + 0u] = i_temp_1 & 0xffu;
        a_bytes[i_offset + 1u] = i_temp_2 & 0xffu;
        a_bytes[i_offset + 2u] = i_temp_3 & 0xffu;
        a_bytes[i_offset + 3u] = i_value & 0xffu;
        i_offset += 4u;
        if (i_offset >= 1024u) {
            cv_print_vector(a_bytes, i_offset);
            i_offset = 0u;
        }
    }
    cv_random_cleanup(&o_random);
}

/*
 *
 */

void cv_random_test(cv_options_it * p_options_it) {
    cv_array o_array;
    cv_array_init(&o_array);
    if (cv_options_it_next(p_options_it, &o_array)) {
        static unsigned char const s_crypto_text[] = {
            'c', 'r', 'y', 'p', 't', 'o' };
        static unsigned char const s_bench1_text[] = {
            'b', 'e', 'n', 'c', 'h', '1' };
        static unsigned char const s_bench2_text[] = {
            'b', 'e', 'n', 'c', 'h', '2' };
        static unsigned char const s_print1_text[] = {
            'p', 'r', 'i', 'n', 't', '1' };
        static cv_array const s_crypto_array =
            cv_array_text_initializer_(s_crypto_text);
        static cv_array const s_bench1_array =
            cv_array_text_initializer_(s_bench1_text);
        static cv_array const s_bench2_array =
            cv_array_text_initializer_(s_bench2_text);
        static cv_array const s_print1_array =
            cv_array_text_initializer_(s_print1_text);
        if (cv_array_compare(&o_array, &s_crypto_array)) {
            cv_random_test_crypto_1();
        } else if (cv_array_compare(&o_array, &s_bench1_array)) {
            cv_random_test_bench_1();
        } else if (cv_array_compare(&o_array, &s_bench2_array)) {
            cv_random_test_bench_2();
        } else if (cv_array_compare(&o_array, &s_print1_array)) {
            cv_random_test_print_1();
        }
    } else {
        cv_random_test_check_pcg(2UL, 10ul);
        cv_random_test_check_tiny(1ul, 10ul);
        cv_random_test_step(12345UL);
    }
    cv_array_cleanup(&o_array);
}

/* end-of-file: cv_random_test.c */
