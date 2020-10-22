/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_color.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_color_class, "cv_screen_color", sizeof(cv_screen_color));

/*
 *
 */

void cv_screen_color_init( cv_screen_color * p_this ) {
    cv_debug_construct_(g_color_class, p_this);
    p_this->i_red = 0;
    p_this->i_green = 0;
    p_this->i_blue = 0;
}

/*
 *
 */

void cv_screen_color_cleanup( cv_screen_color * p_this ) {
    (void)p_this;
    cv_debug_destruct_(g_color_class, p_this);
}

