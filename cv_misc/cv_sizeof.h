/* See LICENSE for license details */

#ifndef cv_sizeof_h_
#define cv_sizeof_h_

#include <cv_misc/cv_types.h>

/*

Define a macro that calculates size of an expression and returns the result
into an long integer type.  By default the sizeof operator returns
a size_t type but that type requires include of stddef.h header file.  Cast
of sizeof result to integer type reduces include dependencies of interfaces.

*/

cv_uptr cv_sizeof_align(
    cv_uptr i_sizeof,
    cv_uptr i_alignment);

#endif /* #ifndef cv_sizeof_h_ */
