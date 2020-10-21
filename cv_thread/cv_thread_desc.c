/* See LICENSE for license details */

#include <cv_thread/cv_thread_desc.h>

#include <cv_memory.h>

#include <cv_debug/cv_debug.h>

#include <cv_object/cv_object.h>

#include <cv_misc/cv_cast.h>

static cv_object g_thread_desc_object;

void cv_thread_desc_load(void) {
    cv_object_init(&g_thread_desc_object, "cv_thread_desc",
        sizeof(cv_thread_desc));
}

void cv_thread_desc_unload(void) {
    cv_object_cleanup(&g_thread_desc_object);
}

cv_thread_desc * cv_thread_desc_cast(void * p_placement) {
    return cv_cast_(cv_thread_desc *)(p_placement);
}

void cv_thread_desc_init(
    cv_thread_desc * p_this) {
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_object_construct(&g_thread_desc_object, p_this);
    p_this->o_callback.p_func = 0;
    p_this->o_callback.p_context = 0;
    cv_array_init(&p_this->o_name);
}

void cv_thread_desc_cleanup(
    cv_thread_desc * p_this) {
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_array_cleanup(&p_this->o_name);
    cv_object_destruct(&g_thread_desc_object, p_this);
}

cv_thread_desc * cv_thread_desc_create(void) {
    cv_thread_desc * p_this = 0;
    void * p_placement = cv_object_alloc(&g_thread_desc_object, 0);
    if (p_placement) {
        p_this = cv_thread_desc_cast(p_placement);
        cv_thread_desc_init(p_this);
    }
    return p_this;
}

void cv_thread_desc_destroy( cv_thread_desc * p_this) {
    cv_thread_desc_cleanup(p_this);
    cv_object_free(&g_thread_desc_object, p_this);
}
