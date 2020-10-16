/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_utf16be_encoder.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_utf16be_encoder", sizeof(cv_utf16be_encoder));

/*
 *
 */

void cv_utf16be_encoder_init( cv_utf16be_encoder * p_this ) {
    cv_debug_construct_(g_class, p_this);
    p_this->i_produce_index = 0;
    p_this->i_consume_index = 0;
}

/*
 *
 */

void cv_utf16be_encoder_cleanup( cv_utf16be_encoder * p_this ) {
    (void)p_this;
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

cv_uptr cv_utf16be_encoder_produce( cv_utf16be_encoder * p_this,
    unsigned long i_input) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    p_this->i_produce_index = 0;
    /* split input into regions */
    if (i_input < 0x10000ul) {
        if (0xd800ul != (i_input & 0xf800ul)) {
            unsigned long const i_temp = i_input;
            unsigned long const i_temp_h = (i_temp >> 8u) & 0xffu;
            unsigned long const i_temp_l = (i_temp >> 0u) & 0xffu;
            p_this->a_accum[0u] = i_temp_h & 0xffu;
            p_this->a_accum[1u] = i_temp_l & 0xffu;
            p_this->i_produce_index = 2u;
        }
    } else if (i_input <= 0x10fffful) {
        unsigned long const i_temp = i_input - 0x10000ul;
        unsigned long const i_w1 = ((i_temp >> 10u) & 0x3fful) | 0xd800ul;
        unsigned long const i_w2 = ((i_temp >> 0u) & 0x3fful) | 0xdc00ul;
        unsigned long const i_w1h = (i_w1 >> 8u) & 0xffu;
        unsigned long const i_w1l = (i_w1 >> 0u) & 0xffu;
        unsigned long const i_w2h = (i_w2 >> 8u) & 0xffu;
        unsigned long const i_w2l = (i_w2 >> 0u) & 0xffu;
        p_this->a_accum[0u] = i_w1h & 0xffu;
        p_this->a_accum[1u] = i_w1l & 0xffu;
        p_this->a_accum[2u] = i_w2h & 0xffu;
        p_this->a_accum[3u] = i_w2l & 0xffu;
        p_this->i_produce_index = 4u;
    }
    return p_this->i_produce_index;
}

/*
 *
 */

cv_bool cv_utf16be_encoder_consume( cv_utf16be_encoder * p_this,
    unsigned char * r_output) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->i_consume_index < p_this->i_produce_index) {
        *r_output = p_this->a_accum[p_this->i_consume_index];
        p_this->i_consume_index ++;
        b_result = cv_true;
    }
    if (p_this->i_consume_index >= p_this->i_produce_index) {
        p_this->i_consume_index = 0;
        p_this->i_produce_index = 0;
    }
    return b_result;
}

/* end-of-file: cv_utf16be_encoder.c */
