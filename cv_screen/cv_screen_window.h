/* See LICENSE for license details */

#ifndef cv_screen_window_h_
#define cv_screen_window_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>
#include <cv_misc/cv_bool.h>

cv_screen_window * cv_screen_window_create(
    cv_screen_window_desc const * p_window_desc);

void cv_screen_window_destroy( cv_screen_window * p_window);

/* cursor position */
void cv_screen_window_goto(cv_screen_window * p_window,
    unsigned short i_cursor_x, unsigned short i_cursor_y);

/* attribute */
void cv_screen_window_attribute( cv_screen_window * p_window,
    unsigned short i_attribute_index);

/* text */
void cv_screen_window_write(cv_screen_window * p_window,
    unsigned short i_glyph_index);

cv_bool cv_screen_window_query(cv_screen_window * p_window,
    cv_screen_window_desc * r_desc,
    unsigned short * * r_glyph_table,
    unsigned short * * r_attribute_table);

#endif /* #ifndef cv_screen_window_h_ */

/* end-of-file: cv_screen_window.h */
