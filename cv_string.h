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

#include <cv_array.h>

#include <cv_bool.h>

struct cv_string
{
    cv_array o_array;
};

#define cv_string_initializer_ { cv_array_initializer_ }

cv_bool cv_string_init(
    cv_string * p_string);

cv_bool cv_string_setup0(
    cv_string * p_string,
    char const * p_ref0,
    long i_ref0_max_len);

cv_bool cv_string_setup(
    cv_string * p_string,
    void const * p_ref_min,
    void const * p_ref_max);

void cv_string_cleanup(
    cv_string * p_string);

long cv_string_len(
    cv_string const * p_string);

#endif /* #ifndef cv_string_h_ */
