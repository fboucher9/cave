/* See LICENSE for license details */

#ifndef cv_screen_attribute_h_
#define cv_screen_attribute_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_screen_color {
    unsigned short i_red;
    unsigned short i_green;
    /* -- */
    unsigned short i_blue;
    unsigned short i_padding[1u];
};

/*
 *
 */

struct cv_screen_attribute_desc {
    struct cv_screen_color o_foreground;
    /* -- */
    struct cv_screen_color o_background;
    /* -- */
    char b_underline;
    char b_reverse;
    char b_blink;
    char c_padding[5u];
};

struct cv_screen_attribute * cv_screen_attribute_create(
    struct cv_screen_attribute_desc const * p_attribute_desc);

void cv_screen_attribute_destroy(
    struct cv_screen_attribute * p_attribute);

cv_bool cv_screen_attribute_query(
    struct cv_screen_attribute const * p_attribute,
    struct cv_screen_attribute_desc * r_attribute);

#endif /* #ifndef cv_screen_attribute_h_ */

/* end-of-file: cv_screen_attribute.h */
