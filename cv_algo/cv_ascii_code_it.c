/* See LICENSE for license details */

#include <cv_algo/cv_ascii_code_it.h>

void cv_ascii_code_it_init(cv_ascii_code_it * p_this) {
    cv_ascii_code_init(&p_this->o_base);
}

void cv_ascii_code_it_cleanup(cv_ascii_code_it * p_this) {
    cv_ascii_code_cleanup(&p_this->o_base);
}

void cv_ascii_code_it_alias(cv_ascii_code_it * p_this,
    cv_ascii_code const * p_ref) {
    p_this->o_base = *p_ref;
}

cv_bool cv_ascii_code_it_next(cv_ascii_code_it * p_this,
    char const * * r_cur) {
    cv_bool b_result = cv_false;
    if (p_this->o_base.p_min != p_this->o_base.p_max) {
        *r_cur = p_this->o_base.p_min;
        p_this->o_base.p_min ++;
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_ascii_code_it_prev(cv_ascii_code_it * p_this,
    char const * * r_cur) {
    cv_bool b_result = cv_false;
    if (p_this->o_base.p_min != p_this->o_base.p_max) {
        p_this->o_base.p_max --;
        *r_cur = p_this->o_base.p_max;
        b_result = cv_true;
    }
    return b_result;
}

/* end-of-file: cv_ascii_code_it.c */
