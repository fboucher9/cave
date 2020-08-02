/* See LICENSE for license details */

/*
 *
 */

#include <cv_json/cv_json.h>

/*
 *
 */

cv_bool cv_json_is_null( cv_json const * p_this) {
    return (cv_json_type_null == p_this->e_type);
}

/* end-of-file: cv_json.c */
