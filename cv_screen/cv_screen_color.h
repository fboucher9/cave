/* See LICENSE for license details */

#ifndef cv_screen_color_h_
#define cv_screen_color_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>

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

void cv_screen_color_init( cv_screen_color * p_this );
void cv_screen_color_cleanup( cv_screen_color * p_this );

#endif /* #ifndef cv_screen_color_h_ */

/* end-of-file: cv_screen_color.h */
