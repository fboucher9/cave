/* See LICENSE for license details */

#ifndef cv_main_h_
#define cv_main_h_

#include <cv_options_pred.h>

typedef char (cv_main_func)(
    cv_options const * p_options);

char cv_main_dispatch(
    cv_options_desc const * p_options_desc,
    cv_main_func * p_func);

#endif /* #ifndef cv_main_h_ */
