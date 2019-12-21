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
    char const * p_file;
    /* -- */
    long i_init_count;
    long i_line;
};

#define cv_debug_class_initializer_ \
{ 0, 0, 0, 0 }

#define cv_debug_decl_(g_class) \
static cv_debug_class g_class = cv_debug_class_initializer_

void xx_debug_class_construct(
    cv_debug_class * p_class,
    char const * p_file,
    int i_line,
    void * p_buf,
    cv_uptr i_buf_len);

#define cv_debug_construct_(g_class, p_this) \
    xx_debug_class_construct(&(g_class), __FILE__, __LINE__, \
        (p_this), sizeof(*(p_this)))

void xx_debug_class_destruct(
    cv_debug_class * p_class,
    char const * p_file,
    int i_line,
    void * p_buf,
    cv_uptr i_buf_len);

#define cv_debug_destruct_(g_class, p_this) \
    xx_debug_class_destruct(&(g_class), __FILE__, __LINE__, \
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
