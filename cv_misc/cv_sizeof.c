/* See LICENSE for license details */

#include <cv_misc/cv_sizeof.h>

long cv_sizeof_align(
    long i_sizeof,
    long i_alignment)
{
    long const i_remainder = i_sizeof % i_alignment;

    long const i_aligned_sizeof = i_remainder ?
        i_sizeof + i_alignment - i_remainder : i_sizeof;

    return i_aligned_sizeof;
}

/* end-of-file: cv_sizeof.c */
