/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_glyph.h>
#include <cv_screen/cv_screen_glyph_desc.h>
#include <cv_object/cv_object.h>
#include <cv_debug/cv_debug.h>
#include <cv_misc/cv_cast.h>

/*
 *
 */

struct cv_screen_glyph {
    cv_unique o_unique;
    /* -- */
    cv_screen_glyph_desc o_desc;
};

static cv_object g_screen_glyph_object;

/*
 *
 */

void cv_screen_glyph_load(void) {
    cv_object_init(&g_screen_glyph_object, "cv_screen_glyph",
        sizeof(cv_screen_glyph));
}

/*
 *
 */

void cv_screen_glyph_unload(void) {
    cv_object_cleanup(&g_screen_glyph_object);
}

/*
 *
 */

static cv_screen_glyph * cv_screen_glyph_cast(void * p_placement) {
    return cv_cast_(cv_screen_glyph *)(p_placement);
}

/*
 *
 */

static cv_bool cv_screen_glyph_init( cv_screen_glyph * p_this,
    cv_screen_glyph_desc const * p_desc,
    cv_unique const * p_unique) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_desc, cv_debug_code_null_ptr);
    cv_object_construct(&g_screen_glyph_object, p_this);
    cv_unique_init(&p_this->o_unique);
    cv_screen_glyph_desc_init(&p_this->o_desc);
    p_this->o_unique = *p_unique;
    p_this->o_desc = *p_desc;
    b_result = cv_true;
    return b_result;
}

/*
 *
 */

static void cv_screen_glyph_cleanup( cv_screen_glyph * p_this ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_screen_glyph_desc_cleanup(&p_this->o_desc);
    cv_unique_cleanup(&p_this->o_unique);
    cv_object_destruct(&g_screen_glyph_object, p_this);
}

/*
 *
 */

cv_screen_glyph * cv_screen_glyph_create(
    cv_screen_glyph_desc const * p_desc) {
    cv_screen_glyph * p_this = 0;
    cv_unique o_unique;
    cv_unique_init(&o_unique);
    {
        void * p_placement = cv_object_alloc(&g_screen_glyph_object, &o_unique);
        if (p_placement) {
            p_this = cv_screen_glyph_cast(p_placement);
            if (cv_screen_glyph_init(p_this, p_desc, &o_unique)) {
            } else {
                if (p_placement) {
                    cv_object_free(&g_screen_glyph_object, p_placement);
                    p_placement = 0;
                }
            }
        }
    }
    cv_unique_cleanup(&o_unique);
    return p_this;
}

/*
 *
 */

void cv_screen_glyph_destroy( cv_screen_glyph * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_screen_glyph_cleanup( p_this );
    cv_object_free(&g_screen_glyph_object, p_this);
}

/*
 *
 */

cv_bool cv_screen_glyph_query( cv_screen_glyph const * p_this,
    cv_screen_glyph_desc * r_desc) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && r_desc, cv_debug_code_null_ptr);
    *r_desc = p_this->o_desc;
    b_result = cv_true;
    return b_result;
}

/* end-of-file: cv_screen_glyph.c */
