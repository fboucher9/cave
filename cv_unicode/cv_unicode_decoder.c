/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_unicode_decoder.h>
#include <cv_unicode/cv_unicode_format.h>
#include <cv_unicode/cv_utf8_decoder.h>
#include <cv_unicode/cv_utf16be_decoder.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_unicode_decoder", sizeof(cv_unicode_decoder));

/*
 *
 */

void cv_unicode_decoder_init( cv_unicode_decoder * p_this,
    unsigned char e_format) {
    cv_debug_construct_(g_class, p_this);
    p_this->i_count = 0;
    p_this->b_ready = cv_false;
    p_this->e_format = e_format;
}

/*
 *
 */

void cv_unicode_decoder_cleanup( cv_unicode_decoder * p_this ) {
    (void)p_this;
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

cv_bool cv_unicode_decoder_produce( cv_unicode_decoder * p_this,
    unsigned char i_input) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (cv_unicode_format_utf8 == p_this->e_format) {
        b_result = cv_utf8_decoder_produce(p_this, i_input);
    } else if (cv_unicode_format_utf16be == p_this->e_format) {
        b_result = cv_utf16be_decoder_produce(p_this, i_input);
    } else {
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_unicode_decoder_consume( cv_unicode_decoder * p_this,
    unsigned long * r_output) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (cv_unicode_format_utf8 == p_this->e_format) {
        b_result = cv_utf8_decoder_consume(p_this, r_output);
    } else if (cv_unicode_format_utf16be == p_this->e_format) {
        b_result = cv_utf16be_decoder_consume(p_this, r_output);
    } else {
    }
    return b_result;
}

/* end-of-file: cv_unicode_decoder.c */
