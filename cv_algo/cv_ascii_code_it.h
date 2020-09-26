/* See LICENSE for license details */

#ifndef cv_ascii_code_it_h_
#define cv_ascii_code_it_h_

#include <cv_algo/cv_ascii_code.h>

struct cv_ascii_code_it {
    cv_ascii_code o_base;
};

void cv_ascii_code_it_init(cv_ascii_code_it * p_this);
void cv_ascii_code_it_cleanup(cv_ascii_code_it * p_this);
void cv_ascii_code_it_alias(cv_ascii_code_it * p_this,
    cv_ascii_code const * p_ref);
cv_bool cv_ascii_code_it_next(cv_ascii_code_it * p_this,
    char const * * r_cur);
cv_bool cv_ascii_code_it_prev(cv_ascii_code_it * p_this,
    char const * * r_cur);

#endif /* #ifndef cv_ascii_code_it_h_ */

/* end-of-file: cv_ascii_code_it.h */
