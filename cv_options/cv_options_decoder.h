/* See LICENSE for license details */

#ifndef cv_options_decoder_h_
#define cv_options_decoder_h_

#include <cv_options/cv_options_pred.h>
#include <cv_algo/cv_chunk_root.h>
#include <cv_algo/cv_array_pred.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_options_decoder {
    cv_chunk_root o_chunk_root;
    /* -- */
    cv_bool b_white_space;
    cv_bool a_padding[7u];
};

void cv_options_decoder_init( cv_options_decoder * p_this );
void cv_options_decoder_cleanup( cv_options_decoder * p_this );
cv_bool cv_options_decoder_write_char( cv_options_decoder * p_this,
    unsigned char c_input, cv_options * p_options);
cv_bool cv_options_decoder_write_array( cv_options_decoder * p_this,
    cv_array const * p_input, cv_options * p_options);

#endif /* #ifndef cv_options_decoder_h_ */

/* end-of-file: cv_options_decoder.h */
