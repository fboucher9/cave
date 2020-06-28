/* See LICENSE for license details */

#ifndef cv_screen_glyph_h_
#define cv_screen_glyph_h_

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

struct cv_screen_glyph * cv_screen_glyph_create(
    struct cv_screen_glyph_desc const * p_desc);

void cv_screen_glyph_destroy( struct cv_screen_glyph * p_this);

cv_bool cv_screen_glyph_query( struct cv_screen_glyph const * p_this,
    struct cv_screen_glyph_desc * r_desc);

#endif /* #ifndef cv_screen_glyph_h_ */

/* end-of-file: cv_screen_glyph.h */
