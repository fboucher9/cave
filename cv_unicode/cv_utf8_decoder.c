/* See LICENSE for license details */

#include <cv_unicode/cv_utf8_decoder.h>
#include <cv_unicode/cv_unicode_decoder.h>
#include <cv_unicode/cv_unicode_format.h>
#include <cv_debug/cv_debug.h>

/*
 *
 */

void cv_utf8_decoder_init(cv_unicode_decoder * p_this) {
    cv_unicode_decoder_init(p_this, cv_unicode_format_utf8);
}

/*
 *
 */

void cv_utf8_decoder_cleanup(cv_unicode_decoder * p_this) {
    cv_unicode_decoder_cleanup(p_this);
}

/*
 *
 */

cv_bool cv_utf8_decoder_produce(cv_unicode_decoder * p_this,
    unsigned char c_input) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    p_this->b_ready = cv_false;
    /* Synchronize first byte */
    if (0x80 != (c_input & 0xc0)) {
        /* Any accumulated data is lost */
        p_this->i_count = 0;
    }
    p_this->a_accum[p_this->i_count] = c_input;
    p_this->i_count ++;
    /* Detect if the number is ready */
    if (0x00 == (p_this->a_accum[0u] & 0x80)) {
        if (1 == p_this->i_count) {
            p_this->b_ready = cv_true;
        }
    } else if (0xc0 == (p_this->a_accum[0u] & 0xe0)) {
        if (2 == p_this->i_count) {
            p_this->b_ready = cv_true;
        }
    } else if (0xe0 == (p_this->a_accum[0u] & 0xf0)) {
        if (3 == p_this->i_count) {
            p_this->b_ready = cv_true;
        }
    } else if (0xf0 == (p_this->a_accum[0u] & 0xf8)) {
        if (4 == p_this->i_count) {
            p_this->b_ready = cv_true;
        }
    } else {
        p_this->i_count = 0;
    }
    return p_this->b_ready;
}

/*
 *
 */

cv_bool cv_utf8_decoder_consume(cv_unicode_decoder * p_this,
    unsigned long * r_output) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->b_ready) {
        unsigned long i_output = 0;
        {
            static unsigned char const g_first_mask[4u] = {
                0x7f, 0x1f, 0x0f, 0x07 };
            i_output = p_this->a_accum[0u] & g_first_mask[p_this->i_count - 1];
        }
        {
            unsigned char i_index = 1;
            while (i_index < p_this->i_count) {
                i_output <<= 6;
                i_output += p_this->a_accum[i_index] & 0x3f;
                i_index ++;
            }
        }
        *r_output = i_output;
        p_this->i_count = 0;
        p_this->b_ready = cv_false;
        b_result = cv_true;
    }
    return b_result;
}

/* end-of-file: cv_utf8_decoder.c */