/* See LICENSE for license details */

#ifndef cv_convert_h_
#define cv_convert_h_

/*
 *  Module: cv_convert.h
 *
 *  Description: Conversions for fundamental types.
 */

#include <cv_misc/cv_types.h>
#include <cv_misc/cv_cast.h>

#if defined cv_debug_

unsigned char xx_convert_c2u(signed char i_value);

unsigned short xx_convert_s2u(signed short i_value);

unsigned int xx_convert_i2u(signed int i_value);

unsigned long xx_convert_l2u(signed long i_value);

cv_uptr xx_convert_p2u(cv_sptr i_value);

cv_ull xx_convert_ll2u(cv_sll i_value);

signed char xx_convert_u2c(unsigned char i_value);

signed short xx_convert_u2s(unsigned short i_value);

signed int xx_convert_u2i(unsigned int i_value);

signed long xx_convert_u2l(unsigned long i_value);

cv_sptr xx_convert_u2p(cv_uptr i_value);

cv_sll xx_convert_u2ll(cv_ull i_value);

#define cv_convert_c2u_(expr) xx_convert_c2u(expr)

#define cv_convert_s2u_(expr) xx_convert_s2u(expr)

#define cv_convert_i2u_(expr) xx_convert_i2u(expr)

#define cv_convert_l2u_(expr) xx_convert_l2u(expr)

#define cv_convert_p2u_(expr) xx_convert_p2u(expr)

#define cv_convert_ll2u_(expr) xx_convert_ll2u(expr)

#define cv_convert_u2c_(expr) xx_convert_u2c(expr)

#define cv_convert_u2s_(expr) xx_convert_u2s(expr)

#define cv_convert_u2i_(expr) xx_convert_u2i(expr)

#define cv_convert_u2l_(expr) xx_convert_u2l(expr)

#define cv_convert_u2p_(expr) xx_convert_u2p(expr)

#define cv_convert_u2ll_(expr) xx_convert_u2ll(expr)

#else /* #if defined cv_debug_ */

#define cv_convert_c2u_(expr) \
    cv_cast_(unsigned char)(cv_cast_(signed char)(expr))

#define cv_convert_s2u_(expr) \
    cv_cast_(unsigned short)(cv_cast_(signed short)(expr))

#define cv_convert_i2u_(expr) \
    cv_cast_(unsigned int)(cv_cast_(signed int)(expr))

#define cv_convert_l2u_(expr) \
    cv_cast_(unsigned long)(cv_cast_(signed long)(expr))

#define cv_convert_p2u_(expr) \
    cv_cast_(cv_uptr)(cv_cast_(cv_sptr)(expr))

#define cv_convert_ll2u_(expr) \
    cv_cast_(cv_ull)(cv_cast_(cv_sll)(expr))

#define cv_convert_u2c_(expr) \
    cv_cast_(signed char)(cv_cast_(unsigned char)(expr))

#define cv_convert_u2s_(expr) \
    cv_cast_(signed short)(cv_cast_(unsigned short)(expr))

#define cv_convert_u2i_(expr) \
    cv_cast_(signed int)(cv_cast_(unsigned int)(expr))

#define cv_convert_u2l_(expr) \
    cv_cast_(signed long)(cv_cast_(unsigned long)(expr))

#define cv_convert_u2p_(expr) \
    cv_cast_(cv_sptr)(cv_cast_(cv_uptr)(expr))

#define cv_convert_u2ll_(expr) \
    cv_cast_(cv_sll)(cv_cast_(cv_ull)(expr))

#endif /* #if defined cv_debug_ */

#endif /* #ifndef cv_convert_h_ */

/* end-of-file: cv_convert.h */
