/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_utf32le_encoder.h>
#include <cv_unicode/cv_unicode_encoder.h>
#include <cv_unicode/cv_unicode_format.h>
#include <cv_debug/cv_debug.h>

/*
 *
 */

void cv_utf32le_encoder_init( cv_unicode_encoder * p_this ) {
    cv_unicode_encoder_init(p_this, cv_unicode_format_utf32le);
}

/*
 *
 */

void cv_utf32le_encoder_cleanup( cv_unicode_encoder * p_this ) {
    cv_unicode_encoder_cleanup(p_this);
}

/*
 *
 */

cv_uptr cv_utf32le_encoder_produce( cv_unicode_encoder * p_this,
    unsigned long i_input) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(cv_unicode_format_utf32le == p_this->e_format,
        cv_debug_code_error);
    if (0x10fffful >= i_input) {
        unsigned long const l_temp2 = (i_input >> 16u) & 0xfful;
        unsigned long const l_temp3 = (i_input >> 8u) & 0xfful;
        unsigned long const l_temp4 = (i_input) & 0xfful;
        p_this->a_accum[3u] = l_temp4 & 0xff;
        p_this->a_accum[2u] = l_temp3 & 0xff;
        p_this->a_accum[1u] = l_temp2 & 0xff;
        p_this->a_accum[0u] = 0;
        p_this->i_count = 4;
    }
    return p_this->i_count;
}

/*
 *
 */

cv_bool cv_utf32le_encoder_consume( cv_unicode_encoder * p_this,
    unsigned char * r_output) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && r_output, cv_debug_code_null_ptr);
    cv_debug_assert_(cv_unicode_format_utf32le == p_this->e_format,
        cv_debug_code_error);
    b_result = cv_unicode_encoder_consume(p_this, r_output);
    return b_result;
}

/* end-of-file: cv_utf32le_encoder.c */
