/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_utf8_encoder.h>
#include <cv_unicode/cv_unicode_encoder.h>
#include <cv_unicode/cv_unicode_format.h>
#include <cv_debug/cv_debug.h>

/*
 *
 */

void cv_utf8_encoder_init(cv_unicode_encoder * p_this) {
    cv_unicode_encoder_init(p_this, cv_unicode_format_utf8);
}

/*
 *
 */

void cv_utf8_encoder_cleanup(cv_unicode_encoder * p_this) {
    cv_unicode_encoder_cleanup(p_this);
}

/*
 *
 */

cv_uptr cv_utf8_encoder_produce(cv_unicode_encoder * p_this,
    unsigned long i_input) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(cv_unicode_format_utf8 == p_this->e_format,
        cv_debug_code_error);
    p_this->i_count = 0;
    if (0x7ful >= i_input) {
        p_this->a_accum[0u] = i_input & 0x7fu;
        p_this->i_count = 1;
    } else if (0x7fful >= i_input) {
        unsigned long const l_temp = ((i_input >> 6u) & 0x1ful) | 0xc0ul;
        unsigned long const l_temp2 = ((i_input) & 0x3ful) | 0x80ul;
        p_this->a_accum[1u] = l_temp & 0xff;
        p_this->a_accum[0u] = l_temp2 & 0xff;
        p_this->i_count = 2;
    } else if (0xfffful >= i_input) {
        unsigned long const l_temp1 = ((i_input >> 12u) & 0x0ful) | 0xe0ul;
        unsigned long const l_temp2 = ((i_input >> 6u) & 0x3ful) | 0x80ul;
        unsigned long const l_temp3 = ((i_input) & 0x3ful) | 0x80ul;
        p_this->a_accum[2u] = l_temp1 & 0xff;
        p_this->a_accum[1u] = l_temp2 & 0xff;
        p_this->a_accum[0u] = l_temp3 & 0xff;
        p_this->i_count = 3;
    } else if (0x10fffful >= i_input) {
        unsigned long const l_temp1 = ((i_input >> 18u) & 0x07ul) | 0xf0ul;
        unsigned long const l_temp2 = ((i_input >> 12u) & 0x3ful) | 0x80ul;
        unsigned long const l_temp3 = ((i_input >> 6u) & 0x3ful) | 0x80ul;
        unsigned long const l_temp4 = ((i_input) & 0x3ful) | 0x80ul;
        p_this->a_accum[3u] = l_temp1 & 0xff;
        p_this->a_accum[2u] = l_temp2 & 0xff;
        p_this->a_accum[1u] = l_temp3 & 0xff;
        p_this->a_accum[0u] = l_temp4 & 0xff;
        p_this->i_count = 4;
    }
    return p_this->i_count;
}

/*
 *
 */

cv_bool cv_utf8_encoder_consume(cv_unicode_encoder * p_this,
    unsigned char * r_output) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && r_output, cv_debug_code_null_ptr);
    cv_debug_assert_(cv_unicode_format_utf8 == p_this->e_format,
        cv_debug_code_error);
    if (p_this->i_count) {
        p_this->i_count --;
        *r_output = p_this->a_accum[p_this->i_count];
        b_result = cv_true;
    }
    return b_result;
}

/* end-of-file: cv_utf8_encoder.c */
