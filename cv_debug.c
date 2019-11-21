/* See LICENSE for license details */

#include <cv_debug.h>

#if defined cv_debug_

#include <cv_unused.h>

#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

void cv_debug_msg(
    char const * p_msg0)
{
#if defined cv_have_libc_
    printf("*** ouch! %s ***\n",
        p_msg0);
#else /* #if defined cv_have_libc_ */
    cv_unused_(p_msg0);
#endif /* #if defined cv_have_libc_ */
}

#endif /* #if defined cv_debug_ */
