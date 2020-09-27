/* See LICENSE for license details */

/*
 *
 */

#include <cv_json/cv_json_it.h>
#include <cv_json/cv_json_node.h>
#include <cv_json/cv_json_ptr.h>

/*
 *
 */

void cv_json_it_init( cv_json_it * p_this, cv_json const * p_value) {
    cv_list_it_init(&p_this->o_list_it, &p_value->o_root);
}

/*
 *
 */

void cv_json_it_cleanup( cv_json_it * p_this) {
    cv_list_it_cleanup(&p_this->o_list_it);
}

/*
 *
 */

cv_bool cv_json_it_first( cv_json_it * p_this, cv_json_ptr * r_json_ptr) {
    return cv_list_it_first(&p_this->o_list_it, &r_json_ptr->o_list_ptr);
}

/*
 *
 */

cv_bool cv_json_it_next( cv_json_it * p_this, cv_json_ptr * r_json_ptr) {
    return cv_list_it_next(&p_this->o_list_it, &r_json_ptr->o_list_ptr);
}

/*
 *
 */

cv_bool cv_json_it_last( cv_json_it * p_this, cv_json_ptr * r_json_ptr) {
    return cv_list_it_last(&p_this->o_list_it, &r_json_ptr->o_list_ptr);
}

/*
 *
 */

cv_bool cv_json_it_prev( cv_json_it * p_this, cv_json_ptr * r_json_ptr) {
    return cv_list_it_prev(&p_this->o_list_it, &r_json_ptr->o_list_ptr);
}

/* end-of-file: cv_json_it.c */
