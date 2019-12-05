/* See LICENSE for license details */

#include <cv_convert.h>

#if defined cv_debug_

/*
 *
 */

unsigned char xx_convert_to_uchar(signed char i_value) {
    return cv_cast_(unsigned char, i_value);
}

/*
 *
 */

unsigned short xx_convert_to_ushort(signed short i_value) {
    return cv_cast_(unsigned short, i_value);
}

/*
 *
 */

unsigned int xx_convert_to_uint(signed int i_value) {
    return cv_cast_(unsigned int, i_value);
}

/*
 *
 */

unsigned long xx_convert_to_ulong(signed long i_value) {
    return cv_cast_(unsigned long, i_value);
}

/*
 *
 */

cv_uptr xx_convert_to_uptr(cv_sptr i_value) {
    return cv_cast_(cv_uptr, i_value);
}

/*
 *
 */

cv_ull xx_convert_to_ull(cv_sll i_value) {
    return cv_cast_(cv_ull, i_value);
}

signed char xx_convert_to_char(unsigned char i_value) {
    return cv_cast_(signed char, i_value);
}

signed short xx_convert_to_short(unsigned short i_value) {
    return cv_cast_(signed short, i_value);
}

signed int xx_convert_to_int(unsigned int i_value) {
    return cv_cast_(signed int, i_value);
}

signed long xx_convert_to_long(unsigned long i_value) {
    return cv_cast_(signed long, i_value);
}

cv_sptr xx_convert_to_ptr(cv_uptr i_value) {
    return cv_cast_(cv_sptr, i_value);
}

cv_sll xx_convert_to_ll(cv_ull i_value) {
    return cv_cast_(cv_sll, i_value);
}

unsigned long xx_truncate_to_ulong(cv_ull i_value) {
    return cv_cast_(unsigned long, i_value);
}

short xx_truncate_to_short(cv_sll i_value) {
    return cv_cast_(short, i_value);
}

long xx_truncate_to_long(cv_sll i_value) {
    return cv_cast_(long, i_value);
}

#endif /* #if defined cv_debug_ */

/* end-of-file: cv_convert.c */
