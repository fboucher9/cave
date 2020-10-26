/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_window.h>
#include <cv_screen/cv_screen_window_desc.h>
#include <cv_debug/cv_debug.h>
#include <cv_heap/cv_heap.h>
#include <cv_misc/cv_cast.h>
#include <cv_runtime.h>

/*
 *
 */

struct cv_screen_window {
    cv_screen_window_desc o_desc;
    /* -- */
    /* glyph table */
    unsigned short * p_glyph_table;
    /* attribute table */
    unsigned short * p_attribute_table;
    /* -- */
    /* drawing context */
    unsigned short i_cursor_x;
    unsigned short i_cursor_y;
    unsigned short i_attribute;
    unsigned short s_padding[1u];
};

cv_debug_decl_(g_class, "cv_screen_window", sizeof(cv_screen_window));

/*
 *
 */

static cv_bool init_glyph_table( cv_screen_window * p_window ) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_window, cv_debug_code_null_ptr);
    {
        unsigned const i_width = p_window->o_desc.i_width;
        unsigned const i_height = p_window->o_desc.i_height;
        cv_uptr const i_glyph_table_len = i_width * i_height *
            sizeof(unsigned short);
        p_window->p_glyph_table = cv_cast_(unsigned short *)cv_heap_alloc(
            i_glyph_table_len, "window_glyph_table", 0);
        if (p_window->p_glyph_table) {
            cv_runtime_memset(p_window->p_glyph_table, 0, i_glyph_table_len);
            b_result = cv_true;
        }
    }
    return b_result;
}

/*
 *
 */

static void cleanup_glyph_table( cv_screen_window * p_window ) {
    cv_debug_assert_(p_window, cv_debug_code_null_ptr);
    if (p_window->p_glyph_table) {
        cv_heap_free(p_window->p_glyph_table);
        p_window->p_glyph_table = 0;
    }
}

/*
 *
 */

static cv_bool init_attribute_table( cv_screen_window * p_window ) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_window, cv_debug_code_null_ptr);
    {
        unsigned const i_width = p_window->o_desc.i_width;
        unsigned const i_height = p_window->o_desc.i_height;
        cv_uptr const i_attribute_table_len = i_width * i_height *
            sizeof(unsigned short);
        p_window->p_attribute_table = cv_cast_(unsigned short *)cv_heap_alloc(
            i_attribute_table_len, "window_attr_table", 0);
        if (p_window->p_attribute_table) {
            cv_runtime_memset(p_window->p_attribute_table, 0,
                i_attribute_table_len);
            b_result = cv_true;
        }
    }
    return b_result;
}

/*
 *
 */

static void cleanup_attribute_table( cv_screen_window * p_window ) {
    cv_debug_assert_(p_window, cv_debug_code_null_ptr);
    if (p_window->p_attribute_table) {
        cv_heap_free(p_window->p_attribute_table);
        p_window->p_attribute_table = 0;
    }
}

/*
 *
 */

static cv_screen_window * cv_screen_window_cast( void * p_placement ) {
    return cv_cast_(cv_screen_window *)(p_placement);
}

/*
 *
 */

static cv_bool cv_screen_window_init( cv_screen_window * p_window,
    cv_screen_window_desc const * p_window_desc) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_window && p_window_desc, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_window);
    p_window->o_desc = *p_window_desc;
    p_window->p_glyph_table = 0;
    p_window->p_attribute_table = 0;
    p_window->i_cursor_x = 0;
    p_window->i_cursor_y = 0;
    p_window->i_attribute = 0;
    if (init_glyph_table(p_window)) {
        if (init_attribute_table(p_window)) {
            b_result = cv_true;
            if (!b_result) {
                cleanup_attribute_table(p_window);
            }
        }
        if (!b_result) {
            cleanup_glyph_table(p_window);
        }
    }
    return b_result;
}

/*
 *
 */

static void cv_screen_window_cleanup( cv_screen_window * p_window ) {
    cv_debug_assert_(p_window, cv_debug_code_null_ptr);
    cleanup_attribute_table(p_window);
    cleanup_glyph_table(p_window);
}

/*
 *
 */

cv_screen_window * cv_screen_window_create(
    cv_screen_window_desc const * p_window_desc) {
    cv_screen_window * p_window = 0;
    cv_debug_assert_(p_window_desc, cv_debug_code_null_ptr);
    {
        cv_uptr const i_placement_len = sizeof(cv_screen_window);
        void * const p_placement = cv_heap_alloc(i_placement_len,
            "cv_screen_window", 0);
        if (p_placement) {
            p_window = cv_screen_window_cast(p_placement);
            if (cv_screen_window_init(p_window, p_window_desc)) {
            } else {
                cv_heap_free(p_placement);
                p_window = 0;
            }
        }
    }
    return p_window;
}

/*
 *
 */

void cv_screen_window_destroy( cv_screen_window * p_window) {
    cv_screen_window_cleanup(p_window);
    cv_heap_free(p_window);
}

/*
 *
 */

void cv_screen_window_goto(cv_screen_window * p_window,
    unsigned short i_cursor_x, unsigned short i_cursor_y) {
    p_window->i_cursor_x = i_cursor_x;
    p_window->i_cursor_y = i_cursor_y;
}

/*
 *
 */

void cv_screen_window_attribute( cv_screen_window * p_window,
    unsigned short i_attribute_index) {
    p_window->i_attribute = i_attribute_index;
}

/*
 *
 */

void cv_screen_window_write(cv_screen_window * p_window,
    unsigned short i_glyph_index) {
    unsigned const i_cursor_x = p_window->i_cursor_x;
    unsigned const i_cursor_y = p_window->i_cursor_y;
    unsigned const i_offset =
        i_cursor_y * p_window->o_desc.i_width +
        i_cursor_x;
    p_window->p_glyph_table[i_offset] = i_glyph_index;
    p_window->p_attribute_table[i_offset] = p_window->i_attribute;
}

/*
 *
 */

cv_bool cv_screen_window_query(cv_screen_window * p_window,
    cv_screen_window_desc * r_desc,
    unsigned short * * r_glyph_table,
    unsigned short * * r_attribute_table) {
    cv_bool b_result = cv_false;
    *r_desc = p_window->o_desc;
    *r_glyph_table = p_window->p_glyph_table;
    *r_attribute_table = p_window->p_attribute_table;
    b_result = cv_true;
    return b_result;
}

/* end-of-file: cv_screen_window.c */
