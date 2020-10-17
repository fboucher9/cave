/* See LICENSE for license details */

#ifndef cv_utf32be_decoder_h_
#define cv_utf32be_decoder_h_

/*
 *
 */

#include <cv_unicode/cv_unicode_pred.h>
#include <cv_unicode/cv_unicode_decoder.h>

void cv_utf32be_decoder_init(cv_unicode_decoder * p_this);
void cv_utf32be_decoder_cleanup(cv_unicode_decoder * p_this);
cv_bool cv_utf32be_decoder_produce(cv_unicode_decoder * p_this,
    unsigned char c_token);
cv_bool cv_utf32be_decoder_consume(cv_unicode_decoder * p_this,
    unsigned long * r_output);

#endif /* #ifndef cv_utf32be_decoder_h_ */

/* end-of-file: cv_utf32be_decoder.h */
