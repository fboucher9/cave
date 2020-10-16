/* See LICENSE for license details */

#ifndef cv_utf16be_encoder_h_
#define cv_utf16be_encoder_h_

/*
 *
 */

#include <cv_unicode/cv_unicode_pred.h>
#include <cv_misc/cv_bool.h>
#include <cv_misc/cv_types.h>

/*
 *
 */

struct cv_utf16be_encoder {

    /* Storage for accumulated bytes */
    unsigned char a_accum[4u];

    /* Number of bytes produced in accumulator */
    unsigned char i_produce_index;

    /* Number of bytes consumed from accumulator */
    unsigned char i_consume_index;

    /* Align to 64-bits */
    unsigned char c_padding[2u];

};

void cv_utf16be_encoder_init( cv_utf16be_encoder * p_this );
void cv_utf16be_encoder_cleanup( cv_utf16be_encoder * p_this );
cv_uptr cv_utf16be_encoder_produce( cv_utf16be_encoder * p_this,
    unsigned long i_input);
cv_bool cv_utf16be_encoder_consume( cv_utf16be_encoder * p_this,
    unsigned char * r_output);

#endif /* #ifndef cv_utf16be_encoder_h_ */

/* end-of-file: cv_utf16be_encoder.h */
