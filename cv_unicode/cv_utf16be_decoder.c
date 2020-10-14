/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_utf16be_decoder.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_utf16be_decoder", sizeof(cv_utf16be_decoder));

/*
 *
 */

void cv_utf16be_decoder_init(cv_utf16be_decoder * p_this) {
    cv_debug_construct_(g_class, p_this);
    p_this->i_count = 0;
    p_this->b_output_ready = cv_false;
}

/*
 *
 */

void cv_utf16be_decoder_cleanup(cv_utf16be_decoder * p_this) {
    (void)p_this;
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

cv_bool cv_utf16be_decoder_produce(cv_utf16be_decoder * p_this,
    unsigned char c_token) {
    cv_bool b_result = cv_false;
    unsigned long i_output = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->b_output_ready) {
        b_result = cv_false;
    } else {
        if (0 == p_this->i_count) {
            /* Accumulator is empty, fill it up */
            p_this->a_accum[0u] = c_token;
            p_this->i_count = 1;
        } else if (1 == p_this->i_count) {
            /* Special case for 0xd800 and 0xdc00 */
            if (0xd8 == (p_this->a_accum[0u] & 0xfc)) {
                p_this->a_accum[1u] = c_token;
                p_this->i_count = 2;
            } else {
                if (0xdc != (p_this->a_accum[0u] & 0xfc)) {
                    i_output = p_this->a_accum[0u];
                    i_output <<= 8u;
                    i_output += c_token;
                    p_this->i_output = i_output;
                    p_this->b_output_ready = cv_true;
                }
                p_this->i_count = 0;
            }
        } else if (2 == p_this->i_count) {
            p_this->a_accum[2u] = c_token;
            p_this->i_count = 3;
        } else if (3 == p_this->i_count) {
            if (0xdc == (p_this->a_accum[2u] & 0xfc)) {
                i_output = p_this->a_accum[0u] & 0x03;
                i_output <<= 8u;
                i_output += p_this->a_accum[1u];
                i_output <<= 2u;
                i_output += (p_this->a_accum[2u] & 0x03);
                i_output <<= 8u;
                i_output += c_token;
                i_output += 0x10000ul;
                p_this->i_output = i_output;
                p_this->b_output_ready = cv_true;
            }
            p_this->i_count = 0;
        }
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_utf16be_decoder_consume(cv_utf16be_decoder * p_this,
    unsigned long * r_output) {
    cv_bool b_result = cv_false;
    if (p_this->b_output_ready) {
        *r_output = p_this->i_output;
        p_this->i_output = 0;
        p_this->b_output_ready = cv_false;
        b_result = cv_true;
    }
    return b_result;
}
