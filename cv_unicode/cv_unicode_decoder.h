/* See LICENSE for license details */

#ifndef cv_unicode_decoder_h_
#define cv_unicode_decoder_h_

/*
 *
 */

#include <cv_unicode/cv_unicode_pred.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_unicode_decoder {

    /* Temporary storage for bytes until enough bytes are found */
    unsigned char a_accum[4u];

    /* Number of bytes accumulated */
    unsigned char i_count;

    /* Indicate that output is ready */
    unsigned char b_ready;

    /* Format of input (see cv_unicode_format.h) */
    unsigned char e_format;

    /* Align to 64-bits */
    unsigned char c_padding[1u];
};

void cv_unicode_decoder_init( cv_unicode_decoder * p_this,
    unsigned char e_format);
void cv_unicode_decoder_cleanup( cv_unicode_decoder * p_this );
cv_bool cv_unicode_decoder_produce( cv_unicode_decoder * p_this,
    unsigned char i_input);
cv_bool cv_unicode_decoder_consume( cv_unicode_decoder * p_this,
    unsigned long * r_output);

#endif /* #ifndef cv_unicode_decoder_h_ */

/* end-of-file: cv_unicode_decoder.h */
