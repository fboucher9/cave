/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_plugin.h>
#include <cv_screen/cv_screen_glyph.h>
#include <cv_screen/cv_screen_key.h>

/*
 *
 */

cv_bool cv_screen_load(void) {
    cv_bool b_result = cv_false;
    cv_screen_glyph_load();
    cv_screen_key_load();
    b_result = cv_true;
    return b_result;
}

/*
 *
 */

void cv_screen_unload(void) {
    cv_screen_key_unload();
    cv_screen_glyph_unload();
}

