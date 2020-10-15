/* See LICENSE for license details */

#ifndef cv_utf8_decoder_h_
#define cv_utf8_decoder_h_

/*
 *
 */

#include <cv_unicode/cv_unicode_pred.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_utf8_decoder {
    unsigned char a_accum[4u];
    unsigned char i_count;
    cv_bool b_ready;
    char c_padding[2u];
};

void cv_utf8_decoder_init(cv_utf8_decoder * p_this);
void cv_utf8_decoder_cleanup(cv_utf8_decoder * p_this);
cv_bool cv_utf8_decoder_produce(cv_utf8_decoder * p_this,
    unsigned char c_input);
cv_bool cv_utf8_decoder_consume(cv_utf8_decoder * p_this,
    unsigned long * r_output);

#endif /* #ifndef cv_utf8_decoder_h_ */

/* end-of-file: cv_utf8_decoder.h */
