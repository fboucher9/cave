/* See LICENSE for license details */

#ifndef cv_screen_glyph_h_
#define cv_screen_glyph_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>
#include <cv_misc/cv_bool.h>

void cv_screen_glyph_load(void);

void cv_screen_glyph_unload(void);

cv_screen_glyph * cv_screen_glyph_create(
    cv_screen_glyph_desc const * p_desc);

void cv_screen_glyph_destroy( cv_screen_glyph * p_this);

cv_bool cv_screen_glyph_query( cv_screen_glyph const * p_this,
    cv_screen_glyph_desc * r_desc);

#endif /* #ifndef cv_screen_glyph_h_ */

/* end-of-file: cv_screen_glyph.h */
