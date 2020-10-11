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
#include <cv_misc/cv_bool.h>
#include <cv_algo/cv_array_pred.h>

void cv_json_load(void);
void cv_json_unload(void);
cv_json * cv_json_create(void);
void cv_json_destroy( cv_json * p_this);
void cv_json_move( cv_json * p_this, cv_json * p_other);
void cv_json_set_type( cv_json * p_this, unsigned e_type);
void cv_json_set_number( cv_json * p_this, double i_number);
cv_bool cv_json_set_label( cv_json * p_this, cv_array const * p_string);
cv_bool cv_json_set_string( cv_json * p_this, cv_array const * p_string);
void cv_json_move_label( cv_json * p_this, cv_array_heap * r_string);
void cv_json_move_string( cv_json * p_this, cv_array_heap * r_string);
void cv_json_join( cv_json * p_node, cv_json * p_root);
unsigned cv_json_get_type( cv_json const * p_this);
double cv_json_get_number( cv_json const * p_this);
void cv_json_get_label( cv_json const * p_this, cv_array * r_string);
void cv_json_get_string( cv_json const * p_this, cv_array * r_string);

#endif /* #ifndef cv_json_h_ */

/* end-of-file: cv_json.h */
