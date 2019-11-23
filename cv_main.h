/* See LICENSE for license details */

#ifndef cv_main_h_
#define cv_main_h_

#include <cv_options_pred.h>

cv_options * cv_main_init(
    int argc,
    char const * const * argv);

void cv_main_cleanup(
    cv_options * p_options);

#endif /* #ifndef cv_main_h_ */
