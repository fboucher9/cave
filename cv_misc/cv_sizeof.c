/* See LICENSE for license details */

#include <cv_misc/cv_sizeof.h>
#include <cv_debug/cv_debug.h>

/*
 *
 */

cv_uptr cv_sizeof_align(
    cv_uptr i_sizeof,
    cv_uptr i_alignment)
{
    cv_uptr i_aligned_sizeof = 0;
    cv_debug_assert_(i_alignment > 0, cv_debug_code_invalid_parameter);
    {
        cv_uptr const i_remainder = i_sizeof % i_alignment;
        i_aligned_sizeof = i_remainder ?
            i_sizeof + i_alignment - i_remainder : i_sizeof;
    }
    return i_aligned_sizeof;
}

/* end-of-file: cv_sizeof.c */
