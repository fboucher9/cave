/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_glyph_desc.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_screen_glyph_desc",
    sizeof(cv_screen_glyph_desc));

/*
 *
 */

void cv_screen_glyph_desc_init( cv_screen_glyph_desc * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    p_this->i_code = 0;
}

/*
 *
 */

void cv_screen_glyph_desc_cleanup( cv_screen_glyph_desc * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    (void)p_this;
    cv_debug_destruct_(g_class, p_this);
}

/* end-of-file: cv_screen_glyph_desc.c */
