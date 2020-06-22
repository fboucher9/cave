/* See LICENSE for license details */

#ifndef cv_screen_window_h_
#define cv_screen_window_h_

/*
 *
 */

struct cv_screen_window_desc {
    unsigned short i_width;
    unsigned short i_height;
    unsigned short i_left;
    unsigned short i_top;
};

struct cv_screen_window * cv_screen_window_create(
    struct cv_screen_window_desc const * p_window_desc);

void cv_screen_window_destroy( struct cv_screen_window * p_window);

/* cursor position */
void cv_screen_window_goto(struct cv_screen_window * p_window,
    unsigned short i_cursor_x, unsigned short i_cursor_y);

/* attribute */
void cv_screen_window_attribute( struct cv_screen_window * p_window,
    unsigned short i_attribute_index);

/* text */
void cv_screen_window_write(struct cv_screen_window * p_window,
    unsigned short i_glyph_index);

#endif /* #ifndef cv_screen_window_h_ */

/* end-of-file: cv_screen_window.h */
