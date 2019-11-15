/* See LICENSE for license details */

#ifndef cv_options_h_
#define cv_options_h_

#include <cv_options_pred.h>

cv_options * cv_options_create(
    cv_options_desc const * p_options_desc);

void cv_options_destroy(
    cv_options * p_this);

char cv_options_query(
    cv_options const * p_this,
    cv_options_desc * p_desc);

#endif /* #ifndef cv_options_h_ */

