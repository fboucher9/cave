/* See LICENSE for license details */

#ifndef cv_debug_h_
#define cv_debug_h_

#include <cv_debug/cv_debug_pred.h>
#include <cv_debug/cv_debug_code.h>
#include <cv_debug/cv_debug_class.h>
#include <cv_misc/cv_bool.h>

#if defined cv_debug_

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
    xx_debug_assert(!!(expr), (p_msg0), __FILE__, __LINE__)

void xx_debug_break(
    cv_debug_code e_code,
    char const * p_file,
    int i_line);

#define cv_debug_break_(p_msg0) \
    xx_debug_break((p_msg0), __FILE__, __LINE__)

#else /* #if defined cv_debug_ */

#define cv_debug_msg_(p_msg0)

#define cv_debug_assert_(expr, p_msg0) (void)(expr)

#define cv_debug_break_(p_msg0)

#endif /* #if defined cv_debug_ */

#endif /* #ifndef cv_debug_h_ */
