/* See LICENSE for license details */

#ifndef cv_screen_device_desc_h_
#define cv_screen_device_desc_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>
#include <cv_file/cv_file_pred.h>

/*
 *
 */

struct cv_screen_device_desc {
    cv_file const * p_file;
    /* -- */
    unsigned short i_key_count;
    unsigned short i_attribute_count;
    unsigned short i_glyph_count;
    unsigned short i_window_count;
    /* -- */
    unsigned short i_width;
    unsigned short i_height;
    unsigned short s_padding[2u];
};

void cv_screen_device_desc_init(
    struct cv_screen_device_desc * p_this);

void cv_screen_device_desc_deinit(
    struct cv_screen_device_desc * p_this);

#endif /* #ifndef cv_screen_device_desc_h_ */

/* end-of-file: cv_screen_device_desc.h */
