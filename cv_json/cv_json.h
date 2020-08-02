/* See LICENSE for license details */

#ifndef cv_json_h_
#define cv_json_h_

/*
 *  json file:
 *
 *      true
 *      false
 *      null
 *      number: [-] 0 | [1-9][0-9]*[.[0-9]][Ee][-+][0-9]+
 *      "string \\ with backslash escapes"
 *      [ value , value ]
 *      { "label" : value , "label" : value }
 */

#include <cv_json/cv_json_pred.h>
#include <cv_json/cv_json_ptr.h>
#include <cv_json/cv_json_type.h>
#include <cv_json/cv_json_dec.h>
#include <cv_json/cv_json_enc.h>
#include <cv_misc/cv_bool.h>
#include <cv_algo/cv_list_root.h>
#include <cv_algo/cv_list_node.h>
#include <cv_algo/cv_array.h>

/*
 *
 *
 */

struct cv_json {
    cv_list_node o_list;
    /* -- */
    unsigned e_type;
    int i_padding[3u];
    /* -- */
    union cv_json_data {
        double i_number;
        cv_array o_string;
        cv_list_root o_list;
    } u;
};

cv_json * cv_json_create(void);
cv_json * cv_json_create_copy( cv_json const * p_value);
cv_json * cv_json_create_null(void);
cv_json * cv_json_create_true(void);
cv_json * cv_json_create_false(void);
cv_json * cv_json_create_number( double i_number);
cv_json * cv_json_create_string( cv_array const * p_string);
cv_json * cv_json_create_label( cv_array const * p_label);
cv_json * cv_json_create_array(void);
cv_json * cv_json_create_object(void);
void cv_json_destroy( cv_json * p_this);
cv_bool cv_json_set_copy( cv_json * p_this,
    cv_json const * p_value);
cv_bool cv_json_set_type( unsigned e_type);
cv_bool cv_json_set_null( cv_json * p_this);
cv_bool cv_json_set_true( cv_json * p_this);
cv_bool cv_json_set_false( cv_json * p_this);
cv_bool cv_json_set_number( cv_json * p_this,
    double i_number);
cv_bool cv_json_set_string( cv_json * p_this,
    cv_array const * p_string);
cv_bool cv_json_set_array(void);
cv_bool cv_json_set_object(void);
cv_bool cv_json_join( cv_json * p_root, cv_json * p_node);
cv_bool cv_json_is_null( cv_json const * p_this);
cv_bool cv_json_is_true( cv_json const * p_this);
cv_bool cv_json_is_false( cv_json const * p_this);
cv_bool cv_json_is_number( cv_json const * p_this);
cv_bool cv_json_is_string( cv_json const * p_this);
cv_bool cv_json_is_label( cv_json const * p_this);
cv_bool cv_json_is_array( cv_json const * p_this);
cv_bool cv_json_is_object( cv_json const * p_this);
unsigned cv_json_get_type( cv_json const * p_this);
cv_bool cv_json_get_number( cv_json const * p_this,
    double * r_number);
cv_bool cv_json_get_string( cv_json const * p_this,
    cv_array * r_string);
cv_bool cv_json_get_label( cv_json const * p_this,
    cv_array * r_label);

#endif /* #ifndef cv_json_h_ */

/* end-of-file: cv_json.h */
