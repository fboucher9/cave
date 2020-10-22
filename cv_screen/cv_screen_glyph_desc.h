/* See LICENSE for license details */

#ifndef cv_screen_glyph_desc_h_
#define cv_screen_glyph_desc_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>

/*
 *
 */

struct cv_screen_glyph_desc {
    unsigned long i_code;
    unsigned long l_padding[1u];
};

void cv_screen_glyph_desc_init( cv_screen_glyph_desc * p_this);
void cv_screen_glyph_desc_cleanup( cv_screen_glyph_desc * p_this);

#endif /* #ifndef cv_screen_glyph_desc_h_ */

/* end-of-file: cv_screen_glyph_desc.h */
