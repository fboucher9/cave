/* See LICENSE for license details */

#include <cv_misc/cv_convert.h>

#if defined cv_debug_

/*
 *
 */

unsigned char xx_convert_c2u(signed char i_value) {
    return cv_cast_(unsigned char)(i_value);
}

/*
 *
 */

unsigned short xx_convert_s2u(signed short i_value) {
    return cv_cast_(unsigned short)(i_value);
}

/*
 *
 */

unsigned int xx_convert_i2u(signed int i_value) {
    return cv_cast_(unsigned int)(i_value);
}

/*
 *
 */

unsigned long xx_convert_l2u(signed long i_value) {
    return cv_cast_(unsigned long)(i_value);
}

/*
 *
 */

cv_uptr xx_convert_p2u(cv_sptr i_value) {
    return cv_cast_(cv_uptr)(i_value);
}

/*
 *
 */

cv_ull xx_convert_ll2u(cv_sll i_value) {
    return cv_cast_(cv_ull)(i_value);
}

signed char xx_convert_u2c(unsigned char i_value) {
    return cv_cast_(signed char)(i_value);
}

signed short xx_convert_u2s(unsigned short i_value) {
    return cv_cast_(signed short)(i_value);
}

signed int xx_convert_u2i(unsigned int i_value) {
    return cv_cast_(signed int)(i_value);
}

signed long xx_convert_u2l(unsigned long i_value) {
    return cv_cast_(signed long)(i_value);
}

cv_sptr xx_convert_u2p(cv_uptr i_value) {
    return cv_cast_(cv_sptr)(i_value);
}

cv_sll xx_convert_u2ll(cv_ull i_value) {
    return cv_cast_(cv_sll)(i_value);
}

#endif /* #if defined cv_debug_ */

/* end-of-file: cv_convert.c */
