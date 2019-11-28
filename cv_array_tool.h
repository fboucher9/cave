/* See LICENSE for license details */

#ifndef cv_array_tool_h_
#define cv_array_tool_h_

/*

Module: cv_array_tool.h

Description: Collection of tools related to arrays.

*/

#include <cv_array.h>

#define cv_array_text_initializer_(name) \
cv_array_initializer_(name, name + sizeof(name))

cv_bool cv_array_compare(
    cv_array const * p_left,
    cv_array const * p_right);

#endif /* #ifndef cv_array_tool_h_ */
