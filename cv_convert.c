/* See LICENSE for license details */

#include <cv_convert.h>

#if defined cv_debug_

/*
 *
 */

unsigned char xx_char_to_uchar(signed char i_value) {
    return cv_cast_(unsigned char, i_value);
}

/*
 *
 */

unsigned short xx_short_to_ushort(signed short i_value) {
    return cv_cast_(unsigned short, i_value);
}

/*
 *
 */

unsigned int xx_int_to_uint(signed int i_value) {
    return cv_cast_(unsigned int, i_value);
}

/*
 *
 */

unsigned long xx_long_to_ulong(signed long i_value) {
    return cv_cast_(unsigned long, i_value);
}

/*
 *
 */

cv_uptr xx_ptr_to_uptr(cv_sptr i_value) {
    return cv_cast_(cv_uptr, i_value);
}

/*
 *
 */

cv_ull xx_ll_to_ull(cv_sll i_value) {
    return cv_cast_(cv_ull, i_value);
}

signed char xx_uchar_to_char(unsigned char i_value) {
    return cv_cast_(signed char, i_value);
}

signed short xx_ushort_to_short(unsigned short i_value) {
    return cv_cast_(signed short, i_value);
}

signed int xx_uint_to_int(unsigned int i_value) {
    return cv_cast_(signed int, i_value);
}

signed long xx_ulong_to_long(unsigned long i_value) {
    return cv_cast_(signed long, i_value);
}

cv_sptr xx_uptr_to_ptr(cv_uptr i_value) {
    return cv_cast_(cv_sptr, i_value);
}

cv_sll xx_ull_to_ll(cv_ull i_value) {
    return cv_cast_(cv_sll, i_value);
}

#endif /* #if defined cv_debug_ */

/* end-of-file: cv_convert.c */
