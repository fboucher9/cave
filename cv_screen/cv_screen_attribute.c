/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_attribute.h>
#include <cv_screen/cv_screen_attribute_desc.h>
#include <cv_debug/cv_debug.h>
#include <cv_misc/cv_cast.h>
#include <cv_heap/cv_heap.h>

/*
 *
 */

struct cv_screen_attribute {
    cv_screen_attribute_desc o_desc;
    /* -- */
};

cv_debug_decl_(g_class, "cv_screen_attribute", sizeof(cv_screen_attribute));

/*
 *
 */

static cv_screen_attribute * cv_screen_attribute_cast(void * p_placement) {
    return cv_cast_(cv_screen_attribute *)(p_placement);
}

/*
 *
 */

static cv_bool cv_screen_attribute_init(
    cv_screen_attribute * p_this,
    cv_screen_attribute_desc const * p_attribute_desc) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_attribute_desc, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_screen_attribute_desc_init(&p_this->o_desc);
    p_this->o_desc = *p_attribute_desc;
    b_result = cv_true;
    return b_result;
}

/*
 *
 */

static void cv_screen_attribute_cleanup(
    cv_screen_attribute * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_screen_attribute_desc_cleanup(&p_this->o_desc);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

cv_screen_attribute * cv_screen_attribute_create(
    cv_screen_attribute_desc const * p_attribute_desc) {
    cv_screen_attribute * p_this = 0;
    cv_debug_assert_(p_attribute_desc, cv_debug_code_null_ptr);
    p_this = cv_screen_attribute_cast(cv_heap_alloc(
        sizeof(cv_screen_attribute), "cv_screen_attribute", 0));
    if (p_this) {
        if (cv_screen_attribute_init(p_this, p_attribute_desc)) {
        } else {
            cv_heap_free(p_this);
            p_this = 0;
        }
    }
    return p_this;
}

/*
 *
 */

void cv_screen_attribute_destroy(
    cv_screen_attribute * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_screen_attribute_cleanup(p_this);
    cv_heap_free(p_this);
}

/*
 *
 */

cv_bool cv_screen_attribute_query(
    cv_screen_attribute const * p_this,
    cv_screen_attribute_desc * r_attribute) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    *r_attribute = p_this->o_desc;
    b_result = cv_true;
    return b_result;
}

/* end-of-file: cv_screen_attribute.c */
