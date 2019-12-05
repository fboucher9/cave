/* See LICENSE for license details */

#ifndef cv_convert_h_
#define cv_convert_h_

/*
 *  Module: cv_convert.h
 *
 *  Description: Conversions for fundamental types.
 */

#include <cv_types.h>
#include <cv_cast.h>

#if defined cv_debug_

unsigned char xx_char_to_uchar(signed char i_value);

unsigned short xx_short_to_ushort(signed short i_value);

unsigned int xx_int_to_uint(signed int i_value);

unsigned long xx_long_to_ulong(signed long i_value);

cv_uptr xx_ptr_to_uptr(cv_sptr i_value);

cv_ull xx_ll_to_ull(cv_sll i_value);

signed char xx_uchar_to_char(unsigned char i_value);

signed short xx_ushort_to_short(unsigned short i_value);

signed int xx_uint_to_int(unsigned int i_value);

signed long xx_ulong_to_long(unsigned long i_value);

cv_sptr xx_uptr_to_ptr(cv_uptr i_value);

cv_sll xx_ull_to_ll(cv_ull i_value);

#define cv_char_to_uchar_(expr) xx_char_to_uchar(expr)

#define cv_short_to_ushort_(expr) xx_short_to_ushort(expr)

#define cv_int_to_uint_(expr) xx_int_to_uint(expr)

#define cv_long_to_ulong_(expr) xx_long_to_ulong(expr)

#define cv_ptr_to_uptr_(expr) xx_ptr_to_uptr(expr)

#define cv_ll_to_ull_(expr) xx_ll_to_ull(expr)

#define cv_uchar_to_char_(expr) xx_uchar_to_char(expr)

#define cv_ushort_to_short_(expr) xx_ushort_to_short(expr)

#define cv_uint_to_int_(expr) xx_uint_to_int(expr)

#define cv_ulong_to_long_(expr) xx_ulong_to_long(expr)

#define cv_uptr_to_ptr_(expr) xx_uptr_to_ptr(expr)

#define cv_ull_to_ll_(expr) xx_ull_to_ll(expr)

#else /* #if defined cv_debug_ */

#define cv_char_to_uchar_(expr) cv_cast_(unsigned char, expr)

#define cv_short_to_ushort_(expr) cv_cast_(unsigned short, expr)

#define cv_int_to_uint_(expr) cv_cast_(unsigned int, expr)

#define cv_long_to_ulong_(expr) cv_cast_(unsigned long, expr)

#define cv_ptr_to_uptr_(expr) cv_cast_(cv_uptr, expr)

#define cv_ll_to_ull_(expr) cv_cast_(cv_ull, expr)

#define cv_uchar_to_char_(expr) cv_cast_(signed char, expr)

#define cv_ushort_to_short_(expr) cv_cast_(signed short, expr)

#define cv_uint_to_int_(expr) cv_cast_(signed int, expr)

#define cv_ulong_to_long_(expr) cv_cast_(signed long, expr)

#define cv_uptr_to_ptr_(expr) cv_cast_(cv_sptr, expr)

#define cv_ull_to_ll_(expr) cv_cast_(cv_sll, expr)

#endif /* #if defined cv_debug_ */

#endif /* #ifndef cv_convert_h_ */

/* end-of-file: cv_convert.h */
