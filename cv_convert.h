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

unsigned char xx_convert_to_uchar(signed char i_value);

unsigned short xx_convert_to_ushort(signed short i_value);

unsigned int xx_convert_to_uint(signed int i_value);

unsigned long xx_convert_to_ulong(signed long i_value);

cv_uptr xx_convert_to_uptr(cv_sptr i_value);

cv_ull xx_convert_to_ull(cv_sll i_value);

signed char xx_convert_to_char(unsigned char i_value);

signed short xx_convert_to_short(unsigned short i_value);

signed int xx_convert_to_int(unsigned int i_value);

signed long xx_convert_to_long(unsigned long i_value);

cv_sptr xx_convert_to_ptr(cv_uptr i_value);

cv_sll xx_convert_to_ll(cv_ull i_value);

unsigned long xx_truncate_to_ulong(cv_ull i_value);

short xx_truncate_to_short(cv_sll i_value);

long xx_truncate_to_long(cv_sll i_value);

#define cv_convert_to_uchar_(expr) xx_convert_to_uchar(expr)

#define cv_convert_to_ushort_(expr) xx_convert_to_ushort(expr)

#define cv_convert_to_uint_(expr) xx_convert_to_uint(expr)

#define cv_convert_to_ulong_(expr) xx_convert_to_ulong(expr)

#define cv_convert_to_uptr_(expr) xx_convert_to_uptr(expr)

#define cv_convert_to_ull_(expr) xx_convert_to_ull(expr)

#define cv_convert_to_char_(expr) xx_convert_to_char(expr)

#define cv_convert_to_short_(expr) xx_convert_to_short(expr)

#define cv_convert_to_int_(expr) xx_convert_to_int(expr)

#define cv_convert_to_long_(expr) xx_convert_to_long(expr)

#define cv_convert_to_ptr_(expr) xx_convert_to_ptr(expr)

#define cv_convert_to_ll_(expr) xx_convert_to_ll(expr)

#define cv_truncate_to_ulong_(expr) xx_truncate_to_ulong(expr)

#define cv_truncate_to_short_(expr) xx_truncate_to_short(expr)

#define cv_truncate_to_long_(expr) xx_truncate_to_long(expr)

#else /* #if defined cv_debug_ */

#define cv_convert_to_uchar_(expr) cv_cast_(unsigned char, expr)

#define cv_convert_to_ushort_(expr) cv_cast_(unsigned short, expr)

#define cv_convert_to_uint_(expr) cv_cast_(unsigned int, expr)

#define cv_convert_to_ulong_(expr) cv_cast_(unsigned long, expr)

#define cv_convert_to_uptr_(expr) cv_cast_(cv_uptr, expr)

#define cv_convert_to_ull_(expr) cv_cast_(cv_ull, expr)

#define cv_convert_to_char_(expr) cv_cast_(signed char, expr)

#define cv_convert_to_short_(expr) cv_cast_(signed short, expr)

#define cv_convert_to_int_(expr) cv_cast_(signed int, expr)

#define cv_convert_to_long_(expr) cv_cast_(signed long, expr)

#define cv_convert_to_ptr_(expr) cv_cast_(cv_sptr, expr)

#define cv_convert_to_ll_(expr) cv_cast_(cv_sll, expr)

#define cv_truncate_to_ulong_(expr) cv_cast_(unsigned long, expr)

#define cv_truncate_to_short_(expr) cv_cast_(short, expr)

#define cv_truncate_to_long_(expr) cv_cast_(long, expr)

#endif /* #if defined cv_debug_ */

#endif /* #ifndef cv_convert_h_ */

/* end-of-file: cv_convert.h */
