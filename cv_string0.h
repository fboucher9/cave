/* See LICENSE for license details */

#ifndef cv_string0_h_
#define cv_string0_h_

#include <cv_string_pred.h>

#include <cv_string_ptr.h>

struct cv_string0
{
    cv_string_ptr o_buf;
    void * pv_padding[1u];
};

char cv_string0_init(
    cv_string0 * p_this,
    cv_string const * p_string);

void cv_string0_cleanup(
    cv_string0 * p_this);

char const * cv_string0_get(
    cv_string0 const * p_this);

long cv_string0_len(
    char const * p_buf0);

#endif /* #ifndef cv_string0_h_ */
