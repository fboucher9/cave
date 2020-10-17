/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_utf16le_decoder.h>
#include <cv_unicode/cv_unicode_format.h>
#include <cv_debug/cv_debug.h>

/*
 *
 */

void cv_utf16le_decoder_init(cv_unicode_decoder * p_this) {
    cv_unicode_decoder_init(p_this, cv_unicode_format_utf16le);
}

/*
 *
 */

void cv_utf16le_decoder_cleanup(cv_unicode_decoder * p_this) {
    cv_unicode_decoder_cleanup(p_this);
}

/*
 *
 */

cv_bool cv_utf16le_decoder_produce(cv_unicode_decoder * p_this,
    unsigned char c_token) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(p_this->i_count <= 4u, cv_debug_code_error);
    cv_debug_assert_(p_this->e_format == cv_unicode_format_utf16le,
        cv_debug_code_error);
    p_this->b_ready = cv_false;
    if (0 == p_this->i_count) {
        p_this->a_accum[0u] = c_token;
        p_this->i_count = 1;
    } else if (1 == p_this->i_count) {
        /* Special case for 0xd800 and 0xdc00 */
        if (0xd8 == (c_token & 0xfc)) {
            p_this->a_accum[1u] = c_token;
            p_this->i_count = 2;
        } else if (0xdc == (c_token & 0xfc)) {
            p_this->i_count = 0;
        } else {
            p_this->a_accum[1u] = c_token;
            p_this->i_count = 2;
            p_this->b_ready = cv_true;
        }
    } else if (2 == p_this->i_count) {
        p_this->a_accum[2u] = c_token;
        p_this->i_count = 3;
    } else if (3 == p_this->i_count) {
        if (0xdc == (c_token & 0xfc)) {
            p_this->a_accum[3u] = c_token;
            p_this->i_count = 4;
            p_this->b_ready = cv_true;
        } else {
            p_this->i_count = 0;
        }
    }
    return p_this->b_ready;
}

/*
 *
 */

cv_bool cv_utf16le_decoder_consume(cv_unicode_decoder * p_this,
    unsigned long * r_output) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && r_output, cv_debug_code_null_ptr);
    cv_debug_assert_(p_this->i_count <= 4u, cv_debug_code_error);
    cv_debug_assert_(p_this->e_format == cv_unicode_format_utf16le,
        cv_debug_code_error);
    if (p_this->b_ready) {
        unsigned long i_output = 0;
        if (2 == p_this->i_count) {
            i_output = p_this->a_accum[1u];
            i_output <<= 8u;
            i_output += p_this->a_accum[0u];
            *r_output = i_output;
        } else if (4 == p_this->i_count) {
            i_output = p_this->a_accum[1u] & 0x03;
            i_output <<= 8u;
            i_output += p_this->a_accum[0u];
            i_output <<= 2u;
            i_output += (p_this->a_accum[3u] & 0x03);
            i_output <<= 8u;
            i_output += p_this->a_accum[2u];
            i_output += 0x10000ul;
            *r_output = i_output;
        }
        p_this->i_count = 0;
        p_this->b_ready = cv_false;
        b_result = cv_true;
    }
    return b_result;
}

/* end-of-file: cv_utf16le_decoder.c */
