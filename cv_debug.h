/* See LICENSE for license details */

#ifndef cv_debug_h_
#define cv_debug_h_

#include <cv_unused.h>

#include <cv_algo/cv_array_pred.h>

#include <cv_bool.h>

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
