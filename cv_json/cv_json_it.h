/* See LICENSE for license details */

#ifndef cv_json_it_h_
#define cv_json_it_h_

/*
 *
 */

#include <cv_json/cv_json_pred.h>
#include <cv_algo/cv_list_it.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_json_it {
    cv_list_it o_list_it;
};

void cv_json_it_init( cv_json_it * p_this, cv_json const * p_value);
void cv_json_it_cleanup( cv_json_it * p_this);
cv_bool cv_json_it_first( cv_json_it * p_this, cv_json_ptr * r_json_ptr);
cv_bool cv_json_it_next( cv_json_it * p_this, cv_json_ptr * r_json_ptr);
cv_bool cv_json_it_last( cv_json_it * p_this, cv_json_ptr * r_json_ptr);
cv_bool cv_json_it_prev( cv_json_it * p_this, cv_json_ptr * r_json_ptr);

#endif /* #ifndef cv_json_it_h_ */

/* end-of-file: cv_json_it.h */
