/* See LICENSE for license details */

#include <cv_debug.h>

#if defined cv_debug_

#include <stdio.h>

void cv_debug_msg(
    char const * p_msg0)
{
    printf("*** ouch! %s ***\n",
        p_msg0);
}

#endif /* #if defined cv_debug_ */
