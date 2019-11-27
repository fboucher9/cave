/* See LICENSE for license details */

#include <cv_debug.h>

#if defined cv_debug_

#include <cv_runtime.h>

void cv_debug_msg(
    char const * p_msg0)
{
    cv_runtime_printf("*** ouch! %s ***\n",
        p_msg0);
}

void cv_debug_assert(
    cv_bool b_expr,
    char const * p_msg0)
{
    if (!b_expr)
    {
        cv_debug_break(p_msg0);
    }
}

void cv_debug_break(
    char const * p_msg0)
{
    cv_runtime_printf("*** assert! %s ***\n",
        p_msg0);
}

#endif /* #if defined cv_debug_ */
