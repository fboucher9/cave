/* See LICENSE for license details */

#ifndef cv_debug_h_
#define cv_debug_h_

#include <cv_unused.h>

#include <cv_bool.h>

#if defined cv_debug_

typedef enum cv_debug_code {
    cv_debug_code_null_ptr = 1,
    cv_debug_code_error,
    cv_debug_code_already_loaded,
    cv_debug_code_already_unloaded,
    cv_debug_code_not_loaded,
    cv_debug_code_invalid_length,
    cv_debug_code_alternative,
    cv_debug_code_out_of_memory,
    cv_debug_code_not_empty,
    cv_debug_code_not_implemented,
    cv_debug_code_invalid_parameter,
    cv_debug_code_dont_panic
} cv_debug_code;

void xx_debug_msg(
    cv_debug_code e_code);

#define cv_debug_msg_(p_msg0) \
    xx_debug_msg((p_msg0))

void xx_debug_assert(
    cv_bool b_expr,
    cv_debug_code e_code);

#define cv_debug_assert_(expr, p_msg0) \
    xx_debug_assert((expr), (p_msg0))

void xx_debug_break(
    cv_debug_code e_code);

#define cv_debug_break_(p_msg0) \
    xx_debug_break((p_msg0))

void xx_debug_init(
    void * p_buf,
    long i_buf_len);

#define cv_debug_init_(p_buf, i_buf_len) \
    xx_debug_init((p_buf), (i_buf_len))

void xx_debug_cleanup(
    void * p_buf,
    long i_buf_len);

#define cv_debug_cleanup_(p_buf, i_buf_len) \
    xx_debug_cleanup((p_buf), (i_buf_len))

#else /* #if defined cv_debug_ */

#define cv_debug_msg_(p_msg0)

#define cv_debug_assert_(expr, p_msg0) cv_unused_(expr)

#define cv_debug_break_(p_msg0)

#define cv_debug_init_(p_buf, i_buf_len)

#define cv_debug_cleanup_(p_buf, i_buf_len)

#endif /* #if defined cv_debug_ */

#endif /* #ifndef cv_debug_h_ */
