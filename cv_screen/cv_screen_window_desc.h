/* See LICENSE for license details */

#ifndef cv_screen_window_desc_h_
#define cv_screen_window_desc_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>

/*
 *
 */

struct cv_screen_window_desc {
    unsigned short i_width;
    unsigned short i_height;
    unsigned short i_left;
    unsigned short i_top;
};

void cv_screen_window_desc_init( cv_screen_window_desc * p_this);

void cv_screen_window_desc_cleanup( cv_screen_window_desc * p_this);

#endif /* #ifndef cv_screen_window_desc_h_ */

/* end-of-file: cv_screen_window_desc.h */
