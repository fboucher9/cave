/* See LICENSE for license details */

#include <cv_misc/cv_sizeof.h>
#include <cv_misc/cv_limits.h>
#include <cv_debug.h>

/*
 *
 */

#if defined cv_debug_
long xx_sizeof_cast( cv_uptr i_value) {
    cv_debug_assert_(i_value <= cv_signed_long_max_,
        cv_debug_code_invalid_length);
    return (i_value & cv_signed_long_max_);
}
#endif /* #if defined cv_debug_ */

/*
 *
 */

long cv_sizeof_align(
    long i_sizeof,
    long i_alignment)
{
    long i_aligned_sizeof = 0;
    cv_debug_assert_(i_alignment > 0, cv_debug_code_invalid_parameter);
    {
        long const i_remainder = i_sizeof % i_alignment;
        i_aligned_sizeof = i_remainder ?
            i_sizeof + i_alignment - i_remainder : i_sizeof;
    }
    return i_aligned_sizeof;
}

/* end-of-file: cv_sizeof.c */
