/* See LICENSE for license details */

#ifndef cv_options_desc_h_
#define cv_options_desc_h_

#include <cv_options_pred.h>

struct cv_options_desc
{
    char const * const * p_args_min;
    char const * const * p_args_max;
};

char cv_options_desc_init(
    cv_options_desc * p_options_desc);

void cv_options_desc_cleanup(
    cv_options_desc * p_options_desc);

#endif /* #ifndef cv_options_desc_h_ */
