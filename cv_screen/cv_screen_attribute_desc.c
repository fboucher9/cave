/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_attribute_desc.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_attribute_desc_class, "cv_screen_attribute_desc",
    sizeof(cv_screen_attribute_desc));

/*
 *
 */

void cv_screen_attribute_desc_init(
    cv_screen_attribute_desc * p_this) {
    cv_debug_construct_(g_attribute_desc_class, p_this);
    cv_screen_color_init(&p_this->o_foreground);
    cv_screen_color_init(&p_this->o_background);
    p_this->b_underline = cv_false;
    p_this->b_reverse = cv_false;
    p_this->b_blink = cv_false;
}

/*
 *
 */

void cv_screen_attribute_desc_cleanup(
    cv_screen_attribute_desc * p_this) {
    cv_screen_color_cleanup(&p_this->o_background);
    cv_screen_color_cleanup(&p_this->o_foreground);
    cv_debug_destruct_(g_attribute_desc_class, p_this);
}

/* end-of-file: cv_screen_attribute_desc.c */
