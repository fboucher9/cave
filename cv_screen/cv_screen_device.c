/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_device.h>
#include <cv_screen/cv_screen_device_desc.h>
#include <cv_screen/cv_screen_linux.h>
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
    char c_padding[7u];
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
                        p_this->b_enabled = cv_false;
                        b_result = cv_true;
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
    cleanup_window_table(p_this);
    cleanup_key_table(p_this);
    cleanup_glyph_table(p_this);
    cleanup_attribute_table(p_this);
    cv_debug_destruct_(g_screen_device, p_this);
}

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

void cv_screen_device_destroy(cv_screen_device * p_this) {
    union cv_screen_device_ptr o_device_ptr = {0};
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    o_device_ptr.p_device = p_this;
    cv_screen_device_cleanup(o_device_ptr.p_device);
    cv_heap_free(o_device_ptr.p_void);
}

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

void cv_screen_device_set_key(cv_screen_device * p_this,
    unsigned short i_index, cv_screen_key * p_key) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_key_count) {
        p_this->p_key_table[i_index] = p_key;
    }
}

cv_screen_key * cv_screen_device_get_key(
    cv_screen_device * p_this, unsigned short i_index) {
    cv_screen_key * p_key = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_key_count) {
        p_key = p_this->p_key_table[i_index];
    }
    return p_key;
}

void cv_screen_device_set_attribute(cv_screen_device * p_this,
    unsigned short i_index, cv_screen_attribute * p_attribute) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_attribute_count) {
        p_this->p_attribute_table[i_index] = p_attribute;
    }
}

cv_screen_attribute * cv_screen_device_get_attribute(
    cv_screen_device * p_this, unsigned short i_index) {
    cv_screen_attribute * p_attribute = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_attribute_count) {
        p_attribute = p_this->p_attribute_table[i_index];
    }
    return p_attribute;
}

void cv_screen_device_set_glyph(cv_screen_device * p_this,
    unsigned short i_index, cv_screen_glyph * p_glyph) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_glyph_count) {
        p_this->p_glyph_table[i_index] = p_glyph;
    }
}

cv_screen_glyph * cv_screen_device_get_glyph(
    cv_screen_device * p_this, unsigned short i_index) {
    cv_screen_glyph * p_glyph = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_glyph_count) {
        p_glyph = p_this->p_glyph_table[i_index];
    }
    return p_glyph;
}

void cv_screen_device_set_window(cv_screen_device * p_this,
    unsigned short i_index, cv_screen_window * p_window) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (i_index < p_this->o_desc.i_window_count) {
        p_this->p_window_table[i_index] = p_window;
    }
}

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

cv_bool cv_screen_device_read(cv_screen_device * p_this,
    unsigned short * r_key) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    /* read from input one byte at a time */
    {
        unsigned char a_buffer[1u];
        cv_array o_array;
        cv_array_init_vector(&o_array, a_buffer, sizeof(a_buffer));
        {
            cv_sptr const i_read_result = cv_file_read(
                p_this->o_desc.p_file, &o_array);
            if (i_read_result > 0) {
                *r_key = a_buffer[0u];
                b_result = cv_true;
            }
        }
        cv_array_cleanup(&o_array);
    }
    /* read until a full character or escape sequence is read */
    /* compare input sequence with table of keys */
    /* return found key */
    return b_result;
}

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
}

/* end-of-file: cv_screen_device.c */
