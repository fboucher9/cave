/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_utf8_encoder.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_utf8_encoder", sizeof cv_utf8_encoder);

/*
 *
 */

void cv_utf8_encoder_init(cv_utf8_encoder * p_this) {
    cv_debug_construct_(g_class, p_this);
    p_this->i_write_index = 0;
    p_this->i_read_index = 0;
}

/*
 *
 */

void cv_utf8_encoder_cleanup(cv_utf8_encoder * p_this) {
    (void)p_this;
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

unsigned cv_utf8_encoder_produce(cv_utf8_encoder * p_this,
    unsigned long i_input) {
}

/*
 *
 */

cv_bool cv_utf8_encoder_consume(cv_utf8_encoder * p_this,
    unsigned char * r_output) {
}

/* end-of-file: cv_utf8_encoder.c */
