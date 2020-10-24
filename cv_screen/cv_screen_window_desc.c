/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_window_desc.h>

/*
 *
 */

void cv_screen_window_desc_init( cv_screen_window_desc * p_this) {
    p_this->i_width = 0;
    p_this->i_height = 0;
    p_this->i_left = 0;
    p_this->i_top = 0;
}

/*
 *
 */

void cv_screen_window_desc_cleanup( cv_screen_window_desc * p_this) {
    (void)p_this;
}

/* end-of-file: cv_screen_window_desc.c */
