/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_unicode_encoder.h>
#include <cv_unicode/cv_unicode_format.h>
#include <cv_unicode/cv_utf8_encoder.h>
#include <cv_unicode/cv_utf16be_encoder.h>
#include <cv_unicode/cv_utf16le_encoder.h>
#include <cv_unicode/cv_utf32be_encoder.h>
#include <cv_unicode/cv_utf32le_encoder.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_unicode_encoder", sizeof(cv_unicode_encoder));

/*
 *
 */

void cv_unicode_encoder_init( cv_unicode_encoder * p_this,
    unsigned char e_format ) {
    cv_debug_construct_(g_class, p_this);
    p_this->i_count = 0;
    p_this->e_format = e_format;
}

/*
 *
 */

void cv_unicode_encoder_cleanup( cv_unicode_encoder * p_this ) {
    (void)p_this;
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

cv_uptr cv_unicode_encoder_produce( cv_unicode_encoder * p_this,
    unsigned long i_input ) {
    cv_uptr i_result = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (cv_unicode_format_utf8 == p_this->e_format) {
        i_result = cv_utf8_encoder_produce(p_this, i_input);
    } else if (cv_unicode_format_utf16be == p_this->e_format) {
        i_result = cv_utf16be_encoder_produce(p_this, i_input);
    } else if (cv_unicode_format_utf16le == p_this->e_format) {
        i_result = cv_utf16le_encoder_produce(p_this, i_input);
    } else if (cv_unicode_format_utf32be == p_this->e_format) {
        i_result = cv_utf32be_encoder_produce(p_this, i_input);
    } else if (cv_unicode_format_utf32le == p_this->e_format) {
        i_result = cv_utf32le_encoder_produce(p_this, i_input);
    } else {
    }
    return i_result;
}

/*
 *
 */

cv_bool cv_unicode_encoder_consume( cv_unicode_encoder * p_this,
    unsigned char * r_output) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && r_output, cv_debug_code_null_ptr);
    if (p_this->i_count) {
        p_this->i_count --;
        *r_output = p_this->a_accum[p_this->i_count];
        b_result = cv_true;
    }
    return b_result;
}

/* end-of-file: cv_unicode_encoder.c */
