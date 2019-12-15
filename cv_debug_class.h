/* See LICENSE for license details */

#ifndef cv_debug_class_h_
#define cv_debug_class_h_

/*
 *
 */

#include <cv_debug_pred.h>
#include <cv_misc/cv_sizeof.h>
#include <cv_misc/cv_null.h>
#include <cv_misc/cv_unused.h>

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
{ cv_null_, cv_null_, 0, 0 }

#define cv_debug_decl_(g_class) \
static cv_debug_class g_class = cv_debug_class_initializer_

void xx_debug_class_construct(
    cv_debug_class * p_class,
    char const * p_file,
    int i_line,
    void * p_buf,
    long i_buf_len);

#define cv_debug_construct_(g_class, p_this) \
    xx_debug_class_construct(&(g_class), __FILE__, __LINE__, \
        (p_this), cv_sizeof_(*(p_this)))

void xx_debug_class_destruct(
    cv_debug_class * p_class,
    char const * p_file,
    int i_line,
    void * p_buf,
    long i_buf_len);

#define cv_debug_destruct_(g_class, p_this) \
    xx_debug_class_destruct(&(g_class), __FILE__, __LINE__, \
        (p_this), cv_sizeof_(*(p_this)))

#else /* #if defined cv_debug_ */

#define cv_debug_decl_(g_class) \
static char g_class

#define cv_debug_construct_(g_class, p_this) \
cv_unused_(g_class)

#define cv_debug_destruct_(g_class, p_this) \
cv_unused_(g_class)

#endif /* #if defined cv_debug_ */

#endif /* #ifndef cv_debug_class_h_ */

/* end-of-file: cv_debug_class.h */
