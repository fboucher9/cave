/* See LICENSE for license details */

#ifndef cv_debug_h_
#define cv_debug_h_

#if defined cv_debug_

void cv_debug_msg(
    char const * p_msg0);

#define cv_debug_msg_(p_msg0) cv_debug_msg(p_msg0)

#else /* #if defined cv_debug_ */

#define cv_debug_msg_(p_msg0)

#endif /* #if defined cv_debug_ */

#endif /* #ifndef cv_debug_h_ */
