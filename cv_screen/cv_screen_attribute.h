/* See LICENSE for license details */

#ifndef cv_screen_attribute_h_
#define cv_screen_attribute_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>
#include <cv_misc/cv_bool.h>

cv_screen_attribute * cv_screen_attribute_create(
    cv_screen_attribute_desc const * p_attribute_desc);

void cv_screen_attribute_destroy(
    cv_screen_attribute * p_attribute);

cv_bool cv_screen_attribute_query( cv_screen_attribute const * p_attribute,
    cv_screen_attribute_desc * r_attribute);

#endif /* #ifndef cv_screen_attribute_h_ */

/* end-of-file: cv_screen_attribute.h */
