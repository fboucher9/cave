/* See LICENSE for license details */

#ifndef cv_debug_h_
#define cv_debug_h_

#include <cv_misc/cv_unused.h>

#include <cv_algo/cv_array_pred.h>

#include <cv_misc/cv_bool.h>

#include <cv_misc/cv_sizeof.h>

#include <cv_algo/cv_array_tool.h>

void cv_debug_load(void);

void cv_debug_unload(void);

#if defined cv_debug_

typedef cv_array const * cv_debug_code;
extern cv_debug_code cv_debug_code_null_ptr;
extern cv_debug_code cv_debug_code_error;
extern cv_debug_code cv_debug_code_already_loaded;
extern cv_debug_code cv_debug_code_already_unloaded;
extern cv_debug_code cv_debug_code_not_loaded;
extern cv_debug_code cv_debug_code_invalid_length;
extern cv_debug_code cv_debug_code_alternative;
extern cv_debug_code cv_debug_code_out_of_memory;
extern cv_debug_code cv_debug_code_not_empty;
extern cv_debug_code cv_debug_code_not_implemented;
extern cv_debug_code cv_debug_code_invalid_parameter;
extern cv_debug_code cv_debug_code_dont_panic;
extern cv_debug_code cv_debug_code_leak;

void xx_debug_msg(
    cv_debug_code e_code,
    char const * p_file,
    int i_line);

#define cv_debug_msg_(p_msg0) \
    xx_debug_msg((p_msg0), __FILE__, __LINE__)

void xx_debug_assert(
    cv_bool b_expr,
    cv_debug_code e_code,
    char const * p_file,
    int i_line);

#define cv_debug_assert_(expr, p_msg0) \
    xx_debug_assert((expr), (p_msg0), __FILE__, __LINE__)

void xx_debug_break(
    cv_debug_code e_code,
    char const * p_file,
    int i_line);

#define cv_debug_break_(p_msg0) \
    xx_debug_break((p_msg0), __FILE__, __LINE__)

typedef struct cv_debug_class cv_debug_class;

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

void xx_debug_init(
    cv_debug_class * p_class,
    char const * p_file,
    int i_line,
    void * p_buf,
    long i_buf_len);

#define cv_debug_construct_(g_class, p_this) \
    xx_debug_init(&(g_class), __FILE__, __LINE__, \
        (p_this), cv_sizeof_(*(p_this)))

void xx_debug_cleanup(
    cv_debug_class * p_class,
    char const * p_file,
    int i_line,
    void * p_buf,
    long i_buf_len);

#define cv_debug_destruct_(g_class, p_this) \
    xx_debug_cleanup(&(g_class), __FILE__, __LINE__, \
        (p_this), cv_sizeof_(*(p_this)))

#else /* #if defined cv_debug_ */

#define cv_debug_msg_(p_msg0)

#define cv_debug_assert_(expr, p_msg0) cv_unused_(expr)

#define cv_debug_break_(p_msg0)

#define cv_debug_decl_(g_class) \
static char g_class

#define cv_debug_construct_(g_class, p_this) \
(void)(g_class)

#define cv_debug_destruct_(g_class, p_this) \
(void)(g_class)

#endif /* #if defined cv_debug_ */

#endif /* #ifndef cv_debug_h_ */
