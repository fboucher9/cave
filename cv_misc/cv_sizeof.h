/* See LICENSE for license details */

#ifndef cv_sizeof_h_
#define cv_sizeof_h_

#include <cv_misc/cv_types.h>
#include <cv_misc/cv_cast.h>

/*

Define a macro that calculates size of an expression and returns the result
into an long integer type.  By default the sizeof operator returns
a size_t type but that type requires include of stddef.h header file.  Cast
of sizeof result to integer type reduces include dependencies of interfaces.

*/

#if defined cv_debug_

long xx_sizeof_cast( cv_uptr i_value);

#if ! defined cv_sizeof_
#define cv_sizeof_(expr) xx_sizeof_cast(sizeof(expr))
#endif /* #if ! defined cv_sizeof_ */

#else /* #if defined cv_debug_ */

#if ! defined cv_sizeof_
#define cv_sizeof_(expr) \
    cv_cast_(long, cv_cast_(unsigned long, sizeof(expr)))
#endif /* #if ! defined cv_sizeof_ */

#endif /* #if defined cv_debug_ */

long cv_sizeof_align(
    long i_sizeof,
    long i_alignment);

#endif /* #ifndef cv_sizeof_h_ */
