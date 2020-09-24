/* See LICENSE for license details */

#ifndef cv_limits_h_
#define cv_limits_h_

/*
 *  Module: cv_limits.h
 *
 *  Description: Limits for base types.
 */

#include <cv_misc/cv_cast.h>
#include <cv_misc/cv_types.h>

#define cv_char_min_ cv_cast_(char)(0x00)
#define cv_char_max_ cv_cast_(char)(0x7f)
#define cv_signed_char_min_ cv_cast_(signed char)(-0x80)
#define cv_signed_char_max_ cv_cast_(signed char)(0x7f)
#define cv_unsigned_char_min_ cv_cast_(unsigned char)(0x00U)
#define cv_unsigned_char_max_ cv_cast_(unsigned char)(0xffU)
#define cv_signed_short_min_ cv_cast_(signed short)(-0x8000)
#define cv_signed_short_max_ cv_cast_(signed short)(0x7fff)
#define cv_unsigned_short_min_ cv_cast_(unsigned short)(0x0000U)
#define cv_unsigned_short_max_ cv_cast_(unsigned short)(0xffffU)
#define cv_signed_int_min_ cv_cast_(signed int)(-0x8000)
#define cv_signed_int_max_ cv_cast_(signed int)(0x7fff)
#define cv_unsigned_int_min_ cv_cast_(unsigned int)(0x0000U)
#define cv_unsigned_int_max_ cv_cast_(unsigned int)(0xffffU)
#define cv_signed_long_min_ cv_cast_(signed long)(-0x80000000L)
#define cv_signed_long_max_ cv_cast_(signed long)(0x7fffffffL)
#define cv_unsigned_long_min_ cv_cast_(unsigned long)(0x00000000UL)
#define cv_unsigned_long_max_ cv_cast_(unsigned long)(0xffffffffUL)
#define cv_unsigned_ptr_min_ (cv_cast_(cv_uptr)(0))
#define cv_unsigned_ptr_max_ (~cv_unsigned_ptr_min_)
#define cv_signed_ptr_max_ cv_cast_(cv_sptr)(cv_unsigned_ptr_max_ >> 1)
#define cv_signed_ptr_min_ cv_cast_(cv_sptr)(~(cv_unsigned_ptr_max_ >> 1))

#endif /* #ifndef cv_limits_h_ */

/* end-of-file: cv_limits.h */
