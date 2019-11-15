/* See LICENSE for license details */

#ifndef cv_options_it_h_
#define cv_options_it_h_

#include <cv_options_pred.h>

struct cv_options_it
{
    char const * const * p_cur;
    char const * const * p_end;
};

char cv_options_it_init(
    cv_options_it * p_this,
    cv_options const * p_options);

void cv_options_it_cleanup(
    cv_options_it * p_this);

char cv_options_it_next(
    cv_options_it * p_this,
    char const * * r_cur);

#endif /* #ifndef cv_options_it_h_ */
