/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_device_desc.h>

void cv_screen_device_desc_init(
    struct cv_screen_device_desc * p_this) {
    p_this->p_file = 0;
    p_this->i_key_count = 0;
    p_this->i_attribute_count = 0;
    p_this->i_glyph_count = 0;
    p_this->i_window_count = 0;
    p_this->i_width = 0;
    p_this->i_height = 0;
}

void cv_screen_device_desc_deinit(
    struct cv_screen_device_desc * p_this) {
    (void)p_this;
}

/* end-of-file: cv_screen_device_desc.c */
