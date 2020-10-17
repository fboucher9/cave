/* See LICENSE for license details */

#ifndef cv_utf8_encoder_h_
#define cv_utf8_encoder_h_

/*
 *
 */

#include <cv_unicode/cv_unicode_pred.h>
#include <cv_unicode/cv_unicode_encoder.h>
#include <cv_misc/cv_bool.h>
#include <cv_misc/cv_types.h>

void cv_utf8_encoder_init(cv_unicode_encoder * p_this);
void cv_utf8_encoder_cleanup(cv_unicode_encoder * p_this);
cv_uptr cv_utf8_encoder_produce(cv_unicode_encoder * p_this,
    unsigned long i_input);
cv_bool cv_utf8_encoder_consume(cv_unicode_encoder * p_this,
    unsigned char * r_output);

#endif /* #ifndef cv_utf8_encoder_h_ */

/* end-of-file: cv_utf8_encoder.h */
