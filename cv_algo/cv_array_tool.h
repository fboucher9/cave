/* See LICENSE for license details */

#ifndef cv_array_tool_h_
#define cv_array_tool_h_

/*

Module: cv_array_tool.h

Description: Collection of tools related to arrays.

*/

#include <cv_algo/cv_array.h>

#define cv_array_text_initializer_(name) \
cv_array_initializer_(name, name + sizeof(name))

cv_bool cv_array_compare(
    cv_array const * p_left,
    cv_array const * p_right);

void cv_array_zero(
    cv_array const * p_this);

void cv_array_fill(
    cv_array const * p_this,
    unsigned char c_value);

void cv_array_copy(
    cv_array const * p_dst,
    cv_array const * p_src);

#endif /* #ifndef cv_array_tool_h_ */
