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

cv_debug_decl_(g_screen_device, "cv_screen_device");

/*
 *
 */

struct cv_screen_device {
    struct cv_screen_device_desc o_desc;
    /* -- */
#if defined cv_linux_
    struct cv_screen_raw * p_raw;
#endif /* #if defined cv_linux_ */
    /* -- */
    cv_bool b_enabled;
    char c_padding[7u];
};

union cv_screen_device_ptr {
    void const * pc_void;
    void * p_void;
    struct cv_screen_device const * pc_device;
    struct cv_screen_device * p_device;
};

/*
 *
 */

static cv_bool cv_screen_device_init(
    struct cv_screen_device * p_this,
    struct cv_screen_device_desc const * p_desc) {
    cv_bool b_result = cv_false;
    cv_debug_construct_(g_screen_device, p_this);
    p_this->o_desc = *p_desc;
#if defined cv_linux_
    p_this->p_raw = 0;
#endif /* #if defined cv_linux_ */
    b_result = 1;
    return b_result;
}

static void cv_screen_device_cleanup(
    struct cv_screen_device * p_this) {
    (void)p_this;
    cv_debug_destruct_(g_screen_device, p_this);
}

struct cv_screen_device * cv_screen_device_create(
    struct cv_screen_device_desc const * p_desc) {
    union cv_screen_device_ptr o_device_ptr = {0};
    o_device_ptr.p_void = cv_heap_alloc(sizeof(struct cv_screen_device),
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

void cv_screen_device_destroy(struct cv_screen_device * p_this) {
    union cv_screen_device_ptr o_device_ptr = {0};
    o_device_ptr.p_device = p_this;
    cv_screen_device_cleanup(o_device_ptr.p_device);
    cv_heap_free(o_device_ptr.p_void);
}

cv_bool cv_screen_device_enter(struct cv_screen_device * p_this) {
    cv_bool b_result = cv_false;
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

void cv_screen_device_leave(struct cv_screen_device * p_this) {
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

void cv_screen_device_set_key(struct cv_screen_device * p_this,
    unsigned short i_index, struct cv_screen_key * p_key) {
    (void)p_this;
    (void)i_index;
    (void)p_key;
}

struct cv_screen_key * cv_screen_device_get_key(
    struct cv_screen_device * p_this, unsigned short i_index) {
    (void)p_this;
    (void)i_index;
    return 0;
}

void cv_screen_device_set_attribute(struct cv_screen_device * p_this,
    unsigned short i_index, struct cv_screen_attribute * p_attribute) {
    (void)p_this;
    (void)i_index;
    (void)p_attribute;
}

struct cv_screen_attribute * cv_screen_device_get_attribute(
    struct cv_screen_device * p_this, unsigned short i_index) {
    (void)p_this;
    (void)i_index;
    return 0;
}

void cv_screen_device_set_glyph(struct cv_screen_device * p_this,
    unsigned short i_index, struct cv_screen_glyph * p_glyph) {
    (void)p_this;
    (void)i_index;
    (void)p_glyph;
}

struct cv_screen_glyph * cv_screen_device_get_glyph(
    struct cv_screen_device * p_this, unsigned short i_index) {
    (void)p_this;
    (void)i_index;
    return 0;
}

void cv_screen_device_set_window(struct cv_screen_device * p_this,
    unsigned short i_index, struct cv_screen_window * p_window) {
    (void)p_this;
    (void)i_index;
    (void)p_window;
}

struct cv_screen_window * cv_screen_device_get_window(
    struct cv_screen_device * p_this, unsigned short i_index) {
    (void)p_this;
    (void)i_index;
    return 0;
}

cv_bool cv_screen_device_read(struct cv_screen_device * p_this,
    unsigned short * r_key) {
    (void)p_this;
    (void)r_key;
    return cv_false;
}

void cv_screen_device_apply(struct cv_screen_device * p_this) {
    (void)p_this;
}

/* end-of-file: cv_screen_device.c */
