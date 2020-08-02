/* See LICENSE for license details */

#ifndef cv_json_type_h_
#define cv_json_type_h_

/*
 *
 */

#include <cv_json/cv_json_pred.h>

/*
 *
 */

enum cv_json_type {
    /* null value */
    cv_json_type_null = 1,
    /* boolean value equal to true */
    cv_json_type_true,
    /* boolean value equal to false */
    cv_json_type_false,
    /* floating-point number */
    cv_json_type_number,
    /* ascii string, with utf-16 code points */
    cv_json_type_string,
    /* ascii string, with utf-16 code points */
    cv_json_type_label,
    /* list of values, corresponds to [ token */
    cv_json_type_array,
    /* list of labels and values, corresponds to { token */
    cv_json_type_object
};

#endif /* #ifndef cv_json_type_h_ */

/* end-of-file: cv_json_type.h */
