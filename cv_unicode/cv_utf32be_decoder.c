/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_utf32be_decoder.h>
#include <cv_unicode/cv_unicode_format.h>
#include <cv_debug/cv_debug.h>

/*
 *
 */

void cv_utf32be_decoder_init(cv_unicode_decoder * p_this) {
    cv_unicode_decoder_init(p_this, cv_unicode_format_utf32be);
}

/*
 *
 */

void cv_utf32be_decoder_cleanup(cv_unicode_decoder * p_this) {
    cv_unicode_decoder_cleanup(p_this);
}

/*
 *
 */

cv_bool cv_utf32be_decoder_produce(cv_unicode_decoder * p_this,
    unsigned char c_token) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(p_this->i_count <= 4u, cv_debug_code_error);
    cv_debug_assert_(p_this->e_format == cv_unicode_format_utf32be,
        cv_debug_code_error);
    p_this->b_ready = cv_false;
    if (4 > p_this->i_count) {
        p_this->a_accum[p_this->i_count] = c_token;
        p_this->i_count ++;
        if (4 == p_this->i_count) {
            p_this->b_ready = cv_true;
        }
    }
    return p_this->b_ready;
}

/*
 *
 */

cv_bool cv_utf32be_decoder_consume(cv_unicode_decoder * p_this,
    unsigned long * r_output) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && r_output, cv_debug_code_null_ptr);
    cv_debug_assert_(p_this->i_count <= 4u, cv_debug_code_error);
    cv_debug_assert_(p_this->e_format == cv_unicode_format_utf32be,
        cv_debug_code_error);
    if (p_this->b_ready) {
        unsigned long i_output = 0;
        i_output = p_this->a_accum[0u] & 0xff;
        i_output <<= 8u;
        i_output += p_this->a_accum[1u] & 0xff;
        i_output <<= 8u;
        i_output += p_this->a_accum[2u] & 0xff;
        i_output <<= 8u;
        i_output += p_this->a_accum[3u] & 0xff;
        *r_output = i_output;
        p_this->i_count = 0;
        p_this->b_ready = cv_false;
        b_result = cv_true;
    }
    return b_result;
}

/* end-of-file: cv_utf32be_decoder.c */
