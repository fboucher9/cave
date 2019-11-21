/* See LICENSE for license details */

#ifndef cv_string_h_
#define cv_string_h_

/*

Utilities for character strings.  The cv_string structure represents an array
of characters with pointers to first and last characters of the array.  The
length is the difference between the two pointers.  The dual pointer strategy
is used to simplify alignment of the structure, no padding warnings.  The
string is not necessarily zero terminated.  Use the cv_string0 object to
convert a string to a zero-terminated string.

*/

#include <cv_string_pred.h>

#include <cv_string_ptr.h>

struct cv_string
{
    cv_string_ptr o_min;
    cv_string_ptr o_max;
};

#define cv_string_initializer_ { cv_string_ptr_null_, cv_string_ptr_null_ }

char cv_string_init(
    cv_string * p_string,
    void const * p_ref_min,
    void const * p_ref_max);

char cv_string_init0(
    cv_string * p_string,
    char const * p_ref0);

void cv_string_cleanup(
    cv_string * p_string);

long cv_string_len(
    cv_string const * p_string);

#endif /* #ifndef cv_string_h_ */
