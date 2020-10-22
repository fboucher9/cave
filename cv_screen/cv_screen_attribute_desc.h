/* See LICENSE for license details */

#ifndef cv_screen_attribute_desc_h_
#define cv_screen_attribute_desc_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>
#include <cv_screen/cv_screen_color.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_screen_attribute_desc {
    cv_screen_color o_foreground;
    /* -- */
    cv_screen_color o_background;
    /* -- */
    cv_bool b_underline;
    cv_bool b_reverse;
    cv_bool b_blink;
    char c_padding[5u];
};

void cv_screen_attribute_desc_init(
    cv_screen_attribute_desc * p_this);

void cv_screen_attribute_desc_cleanup(
    cv_screen_attribute_desc * p_this);

#endif /* #ifndef cv_screen_attribute_desc_h_ */

/* end-of-file: cv_screen_attribute_desc.h */
