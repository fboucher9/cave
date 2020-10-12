/* See LICENSE for license details */

#ifndef cv_json_dec_h_
#define cv_json_dec_h_

/*
 *  Module: cv_json_dec.h
 *
 *  Description: Decode ascii buffer to json value.
 */

#include <cv_json/cv_json_pred.h>
#include <cv_algo/cv_array_pred.h>
#include <cv_misc/cv_bool.h>

void cv_json_dec_array( cv_array const * p_document, cv_json * p_value );

void cv_json_dec_array_it( cv_array_it * p_document, cv_json * p_value );

#endif /* #ifndef cv_json_dec_h_ */

/* end-of-file: cv_json_dec.h */
