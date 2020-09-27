/* See LICENSE for license details */

#ifndef cv_debug_class_h_
#define cv_debug_class_h_

/*
 *
 */

#include <cv_debug/cv_debug_pred.h>
#include <cv_misc/cv_types.h>

#if defined cv_debug_

/*
 *
 */

struct cv_debug_class {
    cv_debug_class * p_next;
    char const * p_name;
    cv_sptr i_init_count;
};

#define cv_debug_decl_(g_class, p_name) \
static cv_debug_class g_class = {0, (p_name), 0}

void xx_debug_class_construct(
    cv_debug_class * p_class,
    void * p_buf,
    cv_uptr i_buf_len);

#define cv_debug_construct_(g_class, p_this) \
    xx_debug_class_construct(&(g_class), \
        (p_this), sizeof(*(p_this)))

void xx_debug_class_destruct(
    cv_debug_class * p_class,
    void * p_buf,
    cv_uptr i_buf_len);

#define cv_debug_destruct_(g_class, p_this) \
    xx_debug_class_destruct(&(g_class), \
        (p_this), sizeof(*(p_this)))

#else /* #if defined cv_debug_ */

#define cv_debug_decl_(g_class) \
static char g_class

#define cv_debug_construct_(g_class, p_this) \
(void)(g_class)

#define cv_debug_destruct_(g_class, p_this) \
(void)(g_class)

#endif /* #if defined cv_debug_ */

#endif /* #ifndef cv_debug_class_h_ */

/* end-of-file: cv_debug_class.h */
