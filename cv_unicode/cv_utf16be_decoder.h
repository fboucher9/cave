/* See LICENSE for license details */

#ifndef cv_utf16be_decoder_h_
#define cv_utf16be_decoder_h_

/*
 *
 */

#include <cv_unicode/cv_unicode_pred.h>
#include <cv_misc/cv_bool.h>

/*
 *  Structure: cv_utf16be_decoder
 *
 *  State machine for decode of a UTF-16 stream.  The stream is fed one byte
 *  at a time and one code point is output.
 */

struct cv_utf16be_decoder {

    /* Temporary storage for bytes until enough bytes are found */
    unsigned char a_accum[4u];

    /* Number of bytes accumulated */
    unsigned char i_count;

    /* Indicate that output is ready */
    cv_bool b_ready;

    /* Align to 64-bits */
    unsigned char c_padding[2u];

};

void cv_utf16be_decoder_init(cv_utf16be_decoder * p_this);
void cv_utf16be_decoder_cleanup(cv_utf16be_decoder * p_this);
cv_bool cv_utf16be_decoder_produce(cv_utf16be_decoder * p_this,
    unsigned char c_token);
cv_bool cv_utf16be_decoder_consume(cv_utf16be_decoder * p_this,
    unsigned long * r_output);

#endif /* #ifndef cv_utf16be_decoder_h_ */

/* end-of-file: cv_utf16be_decoder.h */
