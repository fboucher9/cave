/* See LICENSE for license details */

#ifndef cv_debug_h_
#define cv_debug_h_

#include <cv_unused.h>

#include <cv_bool.h>

#if defined cv_debug_

void cv_debug_msg(
    char const * p_msg0);

#define cv_debug_msg_(p_msg0) cv_debug_msg(p_msg0)

void cv_debug_assert(
    cv_bool b_expr,
    char const * p_msg0);

#define cv_debug_assert_(expr, p_msg0) cv_debug_assert(expr, p_msg0);

void cv_debug_break(
    char const * p_msg0);

#define cv_debug_break_(p_msg0) cv_debug_break(p_msg0);

#else /* #if defined cv_debug_ */

#define cv_debug_msg_(p_msg0)

#define cv_debug_assert_(expr, p_msg0) cv_unused_(expr)

#define cv_debug_break_(p_msg0)

#endif /* #if defined cv_debug_ */

#endif /* #ifndef cv_debug_h_ */
