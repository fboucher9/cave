/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_key.h>
#include <cv_screen/cv_screen_key_desc.h>
#include <cv_debug/cv_debug.h>
#include <cv_object/cv_object.h>
#include <cv_misc/cv_cast.h>
#include <cv_algo/cv_array_tool.h>

/*
 *
 */

struct cv_screen_key {
    cv_screen_key_desc o_desc;
};

static cv_object g_object;

/*
 *
 */

void cv_screen_key_load(void) {
    cv_object_init(&g_object, "cv_screen_key", sizeof(cv_screen_key));
}

/*
 *
 */

void cv_screen_key_unload(void) {
    cv_object_cleanup(&g_object);
}

/*
 *
 */

static cv_screen_key * cv_screen_key_cast(void * p_placement) {
    return cv_cast_(cv_screen_key *)(p_placement);
}

/*
 *
 */

static cv_bool cv_screen_key_init( cv_screen_key * p_this,
    cv_screen_key_desc const * p_desc) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_desc, cv_debug_code_null_ptr);
    cv_object_construct(&g_object, p_this);
    p_this->o_desc = *p_desc;
    b_result = cv_true;
    return b_result;
}

/*
 *
 */

static void cv_screen_key_cleanup( cv_screen_key * p_this ) {
    (void)p_this;
    cv_object_destruct(&g_object, p_this);
}

/*
 *
 */

cv_screen_key * cv_screen_key_create( cv_screen_key_desc const * p_desc) {
    cv_screen_key * p_this = 0;
    cv_debug_assert_(p_desc, cv_debug_code_null_ptr);
    {
        void * const p_placement = cv_object_alloc(&g_object, 0);
        if (p_placement) {
            p_this = cv_screen_key_cast(p_placement);
            if (cv_screen_key_init(p_this, p_desc)) {
            } else {
                cv_object_free(&g_object, p_placement);
                p_this = 0;
            }
        }
    }
    return p_this;
}

/*
 *
 */

void cv_screen_key_destroy( cv_screen_key * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_screen_key_cleanup(p_this);
    cv_object_free(&g_object, p_this);
}

/*
 *
 */

cv_bool cv_screen_key_query( cv_screen_key const * p_this,
    cv_screen_key_desc * r_desc) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && r_desc, cv_debug_code_null_ptr);
    *r_desc = p_this->o_desc;
    b_result = cv_true;
    return b_result;
}

/*
 *
 */

cv_bool cv_screen_key_compare( cv_screen_key const * p_this,
    unsigned char const * p_buffer, cv_uptr i_buffer_len) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    {
        cv_array o_buffer;
        cv_array_init_vector(&o_buffer, p_buffer, i_buffer_len);
        b_result = cv_array_compare(&p_this->o_desc.o_sequence,
            &o_buffer);
        cv_array_cleanup(&o_buffer);
    }
    return b_result;
}

/* end-of-file: cv_screen_key.c */
