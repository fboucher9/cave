/* See LICENSE for license details */

/*
 *
 */

#include <cv_number/cv_number_test.h>
#include <cv_number/cv_number_format.h>
#include <cv_number/cv_number_desc.h>
#include <cv_number/cv_number_enc.h>
#include <cv_number/cv_number_print.h>
#include <cv_number/cv_number_dec.h>
#include <cv_number/cv_number_scan.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_it.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_test_print.h>
#include <cv_misc/cv_sizeof.h>

/*
 *
 */

static void cv_number_test_format(void) {
    cv_number_format_dec();
    cv_number_format_hex();
    cv_number_format_hex2();
    cv_number_format_hex4();
    cv_number_format_hex8();
}

/*
 *
 */

static void cv_number_test_desc(void) {
    cv_number_desc o_desc = cv_number_desc_initializer_;
    cv_number_desc_init(&o_desc);
    cv_number_desc_cleanup(&o_desc);
}

/*
 *
 */
static cv_array const * get_temp_buf(void) {
    static unsigned char a_buf[80];
    static cv_array const g_buf =
        cv_array_text_initializer_(a_buf);
    return &g_buf;
}

static void cv_number_test_enc_step(cv_number_desc const * p_desc) {
    cv_array o_result = cv_array_null_;
    cv_array_init(&o_result);
    if (cv_number_status_done == cv_number_enc_convert(
            p_desc, get_temp_buf(), &o_result)) {
        cv_print_array(&o_result);
        cv_print_nl();
    }
    cv_array_cleanup(&o_result);
}

/*
 *
 */

static void cv_number_test_enc(void) {
    cv_number_desc o_desc = cv_number_desc_initializer_;
    o_desc.o_format = *cv_number_format_dec();
    cv_number_test_enc_step(&o_desc);
    o_desc.o_data.i_unsigned = 12345;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_data.b_negative = 1;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_data.b_negative = 0;
    o_desc.o_format.i_flags = cv_number_flag_plus;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_format.i_flags = cv_number_flag_space;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_format.i_flags = 0;
    o_desc.o_format.i_precision = 2;
    o_desc.o_format.i_digits = 1;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_format.i_precision = 7;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_format.i_precision = 2;
    o_desc.o_format.i_digits = 7;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_format.i_precision = 0;
    o_desc.o_format.i_digits = 7;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_format.i_digits = 0;
    o_desc.o_format.i_width = 10;
    o_desc.o_format.i_flags = cv_number_flag_left;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_format.i_flags = cv_number_flag_center;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_format.i_flags = 0;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_format.i_base = 16;
    o_desc.o_format.i_width = 0;
    cv_number_test_enc_step(&o_desc);
    o_desc.o_format.i_flags = cv_number_flag_prefix;
    cv_number_test_enc_step(&o_desc);
}

/*
 *
 */

static void cv_number_test_print(void) {
    cv_number_print_signed(12345, cv_number_format_dec(), get_temp_buf());
    cv_number_print_signed(-12345, cv_number_format_dec(), get_temp_buf());
    cv_number_print_unsigned(12345, cv_number_format_dec(), get_temp_buf());
}

/*
 *
 */

static void cv_number_test_dec_step(char const * p_text, unsigned int i_base) {
    cv_array o_array = cv_array_null_;
    cv_array_it o_array_it = cv_array_it_initializer_;
    cv_number_dec o_number_dec = cv_number_dec_initializer_;
    cv_array_init_0(&o_array, p_text, 0x7fff);
    cv_array_it_init(&o_array_it, &o_array);
    cv_number_dec_init(&o_number_dec, i_base);
    while (cv_number_status_continue == cv_number_dec_step(&o_number_dec,
            &o_array_it)) {
    }
    /* show result... */
    cv_number_dec_cleanup(&o_number_dec);
    cv_array_it_cleanup(&o_array_it);
    cv_array_cleanup(&o_array);
}

/*
 *
 */

static void cv_number_test_dec(void) {
    cv_number_test_dec_step("12345", 10);
    cv_number_test_dec_step("-12345", 10);
    cv_number_test_dec_step("+12345", 10);
    cv_number_test_dec_step("abcd", 16);
    cv_number_test_dec_step("ABCD", 16);
    cv_number_test_dec_step("0xabcd", 16);
    cv_number_test_dec_step("0XABCD", 16);
    cv_number_test_dec_step("123.45", 10);
    cv_number_test_dec_step("abc.dE", 16);
    cv_number_test_dec_step("  12345", 10);
    cv_number_test_dec_step("12345  ", 10);
    cv_number_test_dec_step("123g", 10);
    cv_number_test_dec_step("123.g", 10);
    cv_number_test_dec_step("123.4g", 10);
    cv_number_test_dec_step("123c", 10);
    cv_number_test_dec_step("123.c", 10);
    cv_number_test_dec_step("123.4c", 10);
    cv_number_test_dec_step("012345", 10);
    cv_number_test_dec_step("0012345", 10);
}

/*
 *
 */

static void cv_number_test_scan(void) {
    static unsigned char a_sample[] = {
        '1', '2', '3', '4', '5' };
    {
        cv_array o_array = cv_array_null_;
        cv_array_init_range(&o_array, a_sample, a_sample + sizeof(a_sample));
        cv_number_scan_array(&o_array, 10);
        cv_array_cleanup(&o_array);
    }
    cv_number_scan_range(a_sample, a_sample + sizeof(a_sample), 10);
    cv_number_scan_vector(a_sample, cv_sizeof_(a_sample), 10);
    cv_number_scan_0("-12345", 80, 10);
}

/*
 *
 */

void cv_number_test(void) {
    /* format */
    cv_number_test_format();
    /* desc */
    cv_number_test_desc();
    /* enc */
    cv_number_test_enc();
    /* dec */
    cv_number_test_dec();
    /* print */
    cv_number_test_print();
    /* scan */
    cv_number_test_scan();
}

/* end-of-file: cv_number_test.c */
