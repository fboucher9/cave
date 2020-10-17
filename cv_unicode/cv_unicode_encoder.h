/* See LICENSE for license details */

#ifndef cv_unicode_encoder_h_
#define cv_unicode_encoder_h_

/*
 *
 */

#include <cv_unicode/cv_unicode_pred.h>
#include <cv_misc/cv_bool.h>
#include <cv_misc/cv_types.h>

/*
 *
 */

struct cv_unicode_encoder {

    /* Accumulator for output bytes */
    unsigned char a_accum[4u];

    /* Number of bytes in accumulator */
    unsigned char i_count;

    /* Format (see cv_unicode_format.h) */
    unsigned char e_format;

    /* Align to 64-bits */
    char c_padding[2u];

};

void cv_unicode_encoder_init( cv_unicode_encoder * p_this,
    unsigned char e_format );
void cv_unicode_encoder_cleanup( cv_unicode_encoder * p_this );
cv_uptr cv_unicode_encoder_produce( cv_unicode_encoder * p_this,
    unsigned long i_input );
cv_bool cv_unicode_encoder_consume( cv_unicode_encoder * p_this,
    unsigned char * r_output);

#endif /* #ifndef cv_unicode_encoder_h_ */

/* end-of-file: cv_unicode_encoder.h */
