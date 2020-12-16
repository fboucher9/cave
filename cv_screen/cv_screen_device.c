/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_device.h>
#include <cv_screen/cv_screen_device_desc.h>
#include <cv_screen/cv_screen_key.h>
#include <cv_screen/cv_screen_linux.h>
#include <cv_screen/cv_screen_window.h>
#include <cv_screen/cv_screen_window_desc.h>
#include <cv_heap/cv_heap.h>
#include <cv_runtime.h>
#include <cv_file/cv_file.h>
#include <cv_debug/cv_debug.h>
#include <cv_misc/cv_cast.h>

/*
 *
 */

struct cv_screen_device {
    cv_screen_device_desc o_desc;
    /* -- */
#if defined cv_linux_
    cv_screen_raw * p_raw;
#endif /* #if defined cv_linux_ */
    /* -- */
    cv_screen_attribute * * p_attribute_table;
    /* -- */
    cv_screen_glyph * * p_glyph_table;
    /* -- */
    cv_screen_key * * p_key_table;
    /* -- */
    cv_screen_window * * p_window_table;
    /* -- */
    cv_bool b_enabled;
    unsigned char i_input_cache_len;
    unsigned char e_input_cache_state;
    char c_padding[5u];
    /* -- */
    unsigned char a_input_cache[32u];
    /* -- */
    unsigned short * p_root_glyph_rect;
    /* -- */
    unsigned short * p_root_attribute_rect;
};

cv_debug_decl_(g_screen_device, "cv_screen_device",
    sizeof(cv_screen_device));

union cv_screen_device_ptr {
    void const * pc_void;
    void * p_void;
    cv_screen_device const * pc_device;
    cv_screen_device * p_device;
};

/*
 *
 */

static cv_bool init_attribute_table( cv_screen_device * p_this ) {
    cv_bool b_result = cv_true;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->o_desc.i_attribute_count) {
        cv_uptr const i_placement_len =
            sizeof(cv_screen_attribute *) * p_this->o_desc.i_attribute_count;
        void * const p_placement = cv_heap_alloc(i_placement_len,
            "attribute_table", 0);
        if (p_placement) {
            p_this->p_attribute_table = cv_cast_(cv_screen_attribute * *)(
                p_placement);
            {
                unsigned short i_index = 0;
                while (i_index < p_this->o_desc.i_attribute_count) {
                    p_this->p_attribute_table[i_index] = 0;
                    i_index ++;
                }
            }
            b_result = cv_true;
        }
    } else {
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

static void cleanup_attribute_table( cv_screen_device * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->p_attribute_table) {
        void * const p_placement = p_this->p_attribute_table;
        cv_heap_free(p_placement);
        p_this->p_attribute_table = 0;
    }
}

/*
 *
 */

static cv_bool init_glyph_table( cv_screen_device * p_this ) {
    cv_bool b_result = cv_true;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->o_desc.i_glyph_count) {
        cv_uptr const i_placement_len =
            sizeof(cv_screen_glyph *) * p_this->o_desc.i_glyph_count;
        void * const p_placement = cv_heap_alloc(i_placement_len,
            "glyph_table", 0);
        if (p_placement) {
            p_this->p_glyph_table =
                cv_cast_(cv_screen_glyph * *)(p_placement);
            {
                unsigned short i_index = 0;
                while (i_index < p_this->o_desc.i_glyph_count) {
                    p_this->p_glyph_table[i_index] = 0;
                    i_index ++;
                }
            }
            b_result = cv_true;
        }
    } else {
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

static void cleanup_glyph_table( cv_screen_device * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->p_glyph_table) {
        void * const p_placement = p_this->p_glyph_table;
        cv_heap_free(p_placement);
        p_this->p_glyph_table = 0;
    }
}

/*
 *
 */

static cv_bool init_key_table( cv_screen_device * p_this ) {
    cv_bool b_result = cv_true;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->o_desc.i_key_count) {
        cv_uptr const i_placement_len =
            sizeof(cv_screen_key *) * p_this->o_desc.i_key_count;
        void * const p_placement = cv_heap_alloc(i_placement_len,
            "key_table", 0);
        if (p_placement) {
            p_this->p_key_table =
                cv_cast_(cv_screen_key * *)(p_placement);
            {
                unsigned short i_index = 0;
                while (i_index < p_this->o_desc.i_key_count) {
                    p_this->p_key_table[i_index] = 0;
                    i_index ++;
                }
            }
            b_result = cv_true;
        }
    } else {
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

static void cleanup_key_table( cv_screen_device * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->p_key_table) {
        void * const p_placement = p_this->p_key_table;
        cv_heap_free(p_placement);
        p_this->p_key_table = 0;
    }
}

/*
 *
 */

static cv_bool init_window_table( cv_screen_device * p_this ) {
    cv_bool b_result = cv_true;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->o_desc.i_window_count) {
        cv_uptr const i_placement_len =
            sizeof(cv_screen_window *) * p_this->o_desc.i_window_count;
        void * const p_placement = cv_heap_alloc(i_placement_len,
            "window_table", 0);
        if (p_placement) {
            p_this->p_window_table =
                cv_cast_(cv_screen_window * *)(p_placement);
            {
                unsigned short i_index = 0;
                while (i_index < p_this->o_desc.i_window_count) {
                    p_this->p_window_table[i_index] = 0;
                    i_index ++;
                }
            }
            b_result = cv_true;
        }
    } else {
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

static void cleanup_window_table( cv_screen_device * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->p_window_table) {
        void * const p_placement = p_this->p_window_table;
        cv_heap_free(p_placement);
        p_this->p_window_table = 0;
    }
}

/*
 *
 */

static void clear_root_rect( cv_screen_device * p_this) {
    cv_uptr i_cursor_max = p_this->o_desc.i_width;
    i_cursor_max *= p_this->o_desc.i_height;
    {
        cv_uptr i_cursor_offset = 0;
        while (i_cursor_offset < i_cursor_max) {
            p_this->p_root_glyph_rect[i_cursor_offset] = 0;
            p_this->p_root_attribute_rect[i_cursor_offset] = 0;
            i_cursor_offset ++;
        }
    }
}

/*
 *
 */

static cv_bool init_root_rect( cv_screen_device * p_this ) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    {
        cv_uptr i_placement_len = sizeof(unsigned short);
        i_placement_len *= p_this->o_desc.i_width;
        i_placement_len *= p_this->o_desc.i_height;
        {
            void * p_glyph_placement = cv_heap_alloc(i_placement_len,
                "root_glyph_rect", 0);
            if (p_glyph_placement) {
                void * p_attribute_placement = cv_heap_alloc(i_placement_len,
                    "root_attribute_rect", 0);
                if (p_attribute_placement) {
                    p_this->p_root_glyph_rect =
                        cv_cast_(unsigned short *)(p_glyph_placement);
                    p_this->p_root_attribute_rect =
                        cv_cast_(unsigned short *)(p_attribute_placement);
                    clear_root_rect(p_this);
                    b_result = cv_true;
                    if (!b_result) {
                        if (p_attribute_placement) {
                            cv_heap_free(p_attribute_placement);
                            p_attribute_placement = 0;
                        }
                    }
                }
                if (!b_result) {
                    if (p_glyph_placement) {
                        cv_heap_free(p_glyph_placement);
                        p_glyph_placement = 0;
                    }
                }
            }
        }
    }
    return b_result;
}

/*
 *
 */

static void cleanup_root_rect( cv_screen_device * p_this ) {
    if (p_this->p_root_glyph_rect) {
        cv_heap_free(p_this->p_root_glyph_rect);
        p_this->p_root_glyph_rect = 0;
    }
    if (p_this->p_root_attribute_rect) {
        cv_heap_free(p_this->p_root_attribute_rect);
        p_this->p_root_attribute_rect = 0;
    }
}

/*
 *
 */

static cv_bool copy_descriptor( cv_screen_device * p_this,
    cv_screen_device_desc const * p_desc) {
    cv_bool b_result = cv_false;
    p_this->o_desc = *p_desc;
    b_result = cv_true;
    return b_result;
}

/*
 *
 */

static cv_bool cv_screen_device_init(
    cv_screen_device * p_this,
    cv_screen_device_desc const * p_desc) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_desc, cv_debug_code_null_ptr);
    cv_debug_construct_(g_screen_device, p_this);
    if (copy_descriptor(p_this, p_desc)) {
#if defined cv_linux_
        p_this->p_raw = 0;
#endif /* #if defined cv_linux_ */
        if (init_attribute_table(p_this)) {
            if (init_glyph_table(p_this)) {
                if (init_key_table(p_this)) {
                    if (init_window_table(p_this)) {
                        if (init_root_rect(p_this)) {
                            p_this->b_enabled = cv_false;
                            p_this->i_input_cache_len = 0;
                            p_this->e_input_cache_state = 0;
                            b_result = cv_true;
                            if (!b_result) {
                                cleanup_root_rect(p_this);
                            }
                        }
                        if (!b_result) {
                            cleanup_window_table(p_this);
                        }
                    }
                    if (!b_result) {
                        cleanup_key_table(p_this);
                    }
                }
                if (!b_result) {
                    cleanup_glyph_table(p_this);
                }
            }
            if (!b_result) {
                cleanup_attribute_table(p_this);
            }
        }
    }
    return b_result;
}

/*
 *
 */

static void cv_screen_device_cleanup(
    cv_screen_device * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cleanup_root_rect(p_this);
    cleanup_window_table(p_this);
    cleanup_key_table(p_this);
    cleanup_glyph_table(p_this);
    cleanup_attribute_table(p_this);
    cv_debug_destruct_(g_screen_device, p_this);
}

/*
 *
 */

cv_screen_device * cv_screen_device_create(
    cv_screen_device_desc const * p_desc) {
    union cv_screen_device_ptr o_device_ptr = {0};
    o_device_ptr.p_void = cv_heap_alloc(sizeof(cv_screen_device),
        "screen_device", 0);
    if (o_device_ptr.p_void) {
        if (cv_screen_device_init(o_device_ptr.p_device, p_desc)) {
        } else {
            cv_heap_free(o_device_ptr.p_void);
            o_device_ptr.p_void = 0;
        }
    }
    return o_device_ptr.p_device;
}

/*
 *
 */

void cv_screen_device_destroy(cv_screen_device * p_this) {
    union cv_screen_device_ptr o_device_ptr = {0};
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    o_device_ptr.p_device = p_this;
    cv_screen_device_cleanup(o_device_ptr.p_device);
    cv_heap_free(o_device_ptr.p_void);
}

/*
 *
 */

cv_bool cv_screen_device_enter(cv_screen_device * p_this) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (!p_this->b_enabled) {
#if defined cv_linux_
        if (!p_this->p_raw) {
            p_this->p_raw = cv_screen_raw_create(p_this->o_desc.p_file);
        }
        if (p_this->p_raw) {
            p_this->b_enabled = cv_true;
            b_result = cv_true;
        }
#else /* #if defined cv_linux_ */
        (void)p_this;
        b_result = cv_false;
#endif /* #if defined cv_linux_ */
    } else {
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

void cv_screen_device_leave(cv_screen_device * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->b_enabled) {
#if defined cv_linux_
        if (p_this->p_raw) {
            cv_screen_raw_destroy(p_this->p_raw);
            p_this->p_raw = 0;
        }
#endif /* #if defined cv_linux_ */
        p_this->b_enabled = cv_false;
    }
}

/*
 *
 */

void cv_screen_device_set_key(cv_screen_device * p_this,
    unsigned short i_index, cv_screen_key * p_key) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_key_count) {
        p_this->p_key_table[i_index] = p_key;
    }
}

/*
 *
 */

cv_screen_key * cv_screen_device_get_key(
    cv_screen_device * p_this, unsigned short i_index) {
    cv_screen_key * p_key = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_key_count) {
        p_key = p_this->p_key_table[i_index];
    }
    return p_key;
}

/*
 *
 */

void cv_screen_device_set_attribute(cv_screen_device * p_this,
    unsigned short i_index, cv_screen_attribute * p_attribute) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_attribute_count) {
        p_this->p_attribute_table[i_index] = p_attribute;
    }
}

/*
 *
 */

cv_screen_attribute * cv_screen_device_get_attribute(
    cv_screen_device * p_this, unsigned short i_index) {
    cv_screen_attribute * p_attribute = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_attribute_count) {
        p_attribute = p_this->p_attribute_table[i_index];
    }
    return p_attribute;
}

/*
 *
 */

void cv_screen_device_set_glyph(cv_screen_device * p_this,
    unsigned short i_index, cv_screen_glyph * p_glyph) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_glyph_count) {
        p_this->p_glyph_table[i_index] = p_glyph;
    }
}

/*
 *
 */

cv_screen_glyph * cv_screen_device_get_glyph(
    cv_screen_device * p_this, unsigned short i_index) {
    cv_screen_glyph * p_glyph = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_glyph_count) {
        p_glyph = p_this->p_glyph_table[i_index];
    }
    return p_glyph;
}

/*
 *
 */

cv_screen_key * cv_screen_device_lookup_key(
    cv_screen_device * p_this, unsigned char const * p_buffer,
    cv_uptr i_buffer_len) {
    cv_screen_key * p_key = 0;
    unsigned short i_key_index = 0;
    while (!p_key && (i_key_index < p_this->o_desc.i_key_count)) {
        if (cv_screen_key_compare(p_this->p_key_table[i_key_index],
                p_buffer, i_buffer_len)) {
            p_key = p_this->p_key_table[i_key_index];
        } else {
            i_key_index ++;
        }
    }
    return p_key;
}

/*
 *
 */

void cv_screen_device_set_window(cv_screen_device * p_this,
    unsigned short i_index, cv_screen_window * p_window) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_window_count) {
        p_this->p_window_table[i_index] = p_window;
    }
}

/*
 *
 */

cv_screen_window * cv_screen_device_get_window(
    cv_screen_device * p_this, unsigned short i_index) {
    cv_screen_window * p_window = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_window_count) {
        p_window = p_this->p_window_table[i_index];
    }
    return p_window;
}

/*
 *
 */

static cv_bool cv_screen_device_read_token(
    cv_screen_device * p_this, unsigned char * r_token) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && r_token, cv_debug_code_null_ptr);
    {
        unsigned char a_buffer[1u];
        cv_array o_array;
        cv_array_init_vector(&o_array, a_buffer, sizeof(a_buffer));
        {
            cv_sptr const i_read_result = cv_file_read(
                p_this->o_desc.p_file, &o_array);
            if (i_read_result > 0) {
                *r_token = a_buffer[0u];
                b_result = cv_true;
            }
        }
        cv_array_cleanup(&o_array);
    }
    return b_result;
}

/*
 *
 */

static cv_bool cv_screen_device_is_complete_sequence(
    unsigned char const * pc_uchar,
    cv_uptr i_buffer_iterator) {
    cv_bool b_result = cv_false;
    if (i_buffer_iterator >= 1) {
        /* Detect that we have accumulated enough data */
        if (0x1b == pc_uchar[0u]) {
            if (i_buffer_iterator >= 2) {
                if ('[' == pc_uchar[1u]) {
                    if (i_buffer_iterator >= 3) {
                        if ((0x20u <= pc_uchar[i_buffer_iterator - 1]) &&
                            (0x3fu >= pc_uchar[i_buffer_iterator - 1])) {
                        } else {
                            b_result = cv_true;
                        }
                    }
                } else if ('O' == pc_uchar[1u]) {
                    if (i_buffer_iterator >= 3) {
                        b_result = cv_true;
                    }
                } else if ('P' == pc_uchar[1u]) {
                    if (i_buffer_iterator >= 3) {
                        b_result = cv_true;
                    }
                } else {
                    if ((0x20u <= pc_uchar[1u]) &&
                        (0x2fu >= pc_uchar[1u])) {
                    } else {
                        b_result = cv_true;
                    }
                }
            }
        } else if (0xc0 == (pc_uchar[0u] & 0xe0)) {
            if (i_buffer_iterator >= 2) {
                b_result = cv_true;
            }
        } else if (0xe0 == (pc_uchar[0u] & 0xf0)) {
            if (i_buffer_iterator >= 3) {
                b_result = cv_true;
            }
        } else if (0xf0 == (pc_uchar[0u] & 0xf8)) {
            if (i_buffer_iterator >= 4) {
                b_result = cv_true;
            }
        } else {
            b_result = cv_true;
        }
    }
    return b_result;
}

/*
 *
 */

cv_uptr cv_screen_device_read(cv_screen_device * p_this,
    cv_array const * p_buffer) {
    cv_uptr i_buffer_iterator = 0;
    unsigned char c_token = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    /* read from input one byte at a time */
    if (cv_screen_device_read_token(p_this, &c_token)) {
        if (p_this->i_input_cache_len < sizeof(p_this->a_input_cache)) {
            p_this->a_input_cache[p_this->i_input_cache_len] =
                c_token;
            p_this->i_input_cache_len ++;
            /* read until a full character or escape sequence is read */
            if (cv_screen_device_is_complete_sequence(
                    p_this->a_input_cache,
                    p_this->i_input_cache_len)) {
                cv_uptr const i_buffer_len = cv_array_len(p_buffer);
                if (i_buffer_len >= p_this->i_input_cache_len) {
                    while ((i_buffer_iterator < p_this->i_input_cache_len) &&
                        (i_buffer_iterator < i_buffer_len)) {
                        p_buffer->o_min.p_uchar[i_buffer_iterator] =
                            p_this->a_input_cache[i_buffer_iterator];
                        i_buffer_iterator ++;
                    }
                }
                p_this->i_input_cache_len = 0;
            }
        } else {
            p_this->i_input_cache_len = 0;
        }
    }
    return i_buffer_iterator;
}

/* compare input sequence with table of keys */
/* return found key */

/*
 *
 */

static void render_window(cv_screen_device * p_this,
    cv_screen_window * p_window) {
    /* copy the window into the root rect */
    cv_screen_window_desc o_window_desc;
    unsigned short * p_window_glyph = 0;
    unsigned short * p_window_attr = 0;
    if (cv_screen_window_query(p_window,
            &o_window_desc,
            &p_window_glyph,
            &p_window_attr)) {
        unsigned short i_cursor_y = 0;
        /* for all lines of window */
        while (i_cursor_y < o_window_desc.i_height) {
            /* for all columns of window */
            unsigned short i_cursor_x = 0;
            while (i_cursor_x < o_window_desc.i_width) {
                cv_uptr i_offset = 0;
                unsigned short i_glyph = 0;
                unsigned short i_attr = 0;
                i_offset = i_cursor_y;
                i_offset *= o_window_desc.i_width;
                i_offset += i_cursor_x;
                i_glyph = p_window_glyph[i_offset];
                i_attr = p_window_attr[i_offset];
                (void)i_attr;
                if (i_glyph) {
                    cv_uptr i_root_offset = 0;
                    i_root_offset = o_window_desc.i_top;
                    i_root_offset += i_cursor_y;
                    i_root_offset *= p_this->o_desc.i_width;
                    i_root_offset += o_window_desc.i_left;
                    i_root_offset += i_cursor_x;
                    p_this->p_root_glyph_rect[i_root_offset] = i_glyph;
                }
                i_cursor_x ++;
            }
            i_cursor_y ++;
        }
    }
}

/*
 *
 */

static void render_all_window(cv_screen_device * p_this) {
    unsigned short i_window_index = 0;
    while (i_window_index < p_this->o_desc.i_window_count) {
        cv_screen_window * p_window = 0;
        p_window = p_this->p_window_table[i_window_index];
        if (p_window) {
            render_window(p_this, p_window);
        }
        i_window_index ++;
    }
}

/*
 *
 */

static void print_char(cv_screen_device * p_this, unsigned char c_value) {
    cv_array o_array;
    cv_array_init_vector(&o_array, &c_value, 1);
    cv_file_write(p_this->o_desc.p_file, &o_array);
    cv_array_cleanup(&o_array);
}

/*
 *
 */

void cv_screen_device_apply(cv_screen_device * p_this) {
    (void)p_this;
    /* first step is to render an image of all the windows */
    /* start with empty screen */
    /* render windows from bottom to top */
    /* Each pixel has an attribute and a glyph */
    /* clear the screen? */
    /* move cursor to home */
    /* for all characters of screen */
    /* set attribute */
    /* set glyph */

    /* clear the front buffer */
    clear_root_rect(p_this);

    /* render the front buffer */
    render_all_window(p_this);

    {
        unsigned short i_cursor_y = 0;
        /* for all lines of window */
        while (i_cursor_y < p_this->o_desc.i_height) {
            /* for all columns of window */
            unsigned short i_cursor_x = 0;
            print_char(p_this, '[');
            while (i_cursor_x < p_this->o_desc.i_width) {
                unsigned long i_offset = 0;
                unsigned short i_glyph = 0;
                i_offset = i_cursor_y;
                i_offset *= p_this->o_desc.i_width;
                i_offset += i_cursor_x;
                i_glyph = p_this->p_root_glyph_rect[i_offset];
                /* unsigned short i_attr = 0; */
                /*i_attr = p_root_attr[i_offset];
                (void)i_attr; */
                if (i_glyph) {
                    print_char(p_this, i_glyph & 0x7fu);
                } else {
                    print_char(p_this, '.');
                }
                i_cursor_x ++;
            }
            print_char(p_this, ']');
            i_cursor_y ++;
            if (i_cursor_y < p_this->o_desc.i_height) {
                print_char(p_this, '\r');
                print_char(p_this, '\n');
            }
        }
        print_char(p_this, '\r');
        print_char(p_this, 0x1b);
        print_char(p_this, '[');
        if (p_this->o_desc.i_height >= 10) {
            unsigned int i_temp = p_this->o_desc.i_height;
            i_temp /= 10;
            i_temp %= 10;
            i_temp += '0';
            print_char(p_this, i_temp & 0xff);
        }
        {
            unsigned int i_temp = p_this->o_desc.i_height;
            i_temp %= 10;
            i_temp += '0';
            print_char(p_this, i_temp & 0xff);
        }
        print_char(p_this, 'A');
    }
}

/* end-of-file: cv_screen_device.c */
