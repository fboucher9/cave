/* See LICENSE for license details */

#ifndef cv_ascii_tool_h_
#define cv_ascii_tool_h_

/*
 *  Module: cv_ascii_tool.h
 *
 *  Description:
 *
 *      Array of ASCII characters.  The char type is used to represent an ASCII
 *      character.
 *
 *  Comments:
 *
 *      For portability and compatibility reasons the char type may only hold
 *      values between 0 and 127.  For values above 127, use the cv_unicode
 *      module instead.
 *
 *      For portability, a pointer to char may not be cast to other types
 *      without affecting the values referenced by the pointer.  To convert
 *      cv_ascii to cv_unicode requires a special copy which casts each char to
 *      unsigned char.
 *
 *      For portability, a pointer to const char is not the same as a non-const
 *      pointer.  Please avoid union for pointers and please use the cast
 *      operator or an implicit conversion for pointers.
 */

#include <cv_algo/cv_ascii_pred.h>
#include <cv_misc/cv_types.h>
#include <cv_misc/cv_bool.h>

cv_bool cv_ascii_compare( cv_ascii_code const * p_left,
    cv_ascii_code const * p_right);
void cv_ascii_zero( cv_ascii_data const * p_this);
void cv_ascii_fill( cv_ascii_data const * p_this, char c_value);
void cv_ascii_copy( cv_ascii_data const * p_left,
    cv_ascii_code const * p_right);

#endif /* #ifndef cv_ascii_tool_h_ */

/* end-of-file: cv_ascii_tool.h */
