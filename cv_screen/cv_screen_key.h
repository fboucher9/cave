/* See LICENSE for license details */

#ifndef cv_screen_key_h_
#define cv_screen_key_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_screen_key_desc {
    unsigned long i_code;
    unsigned long l_padding[1u];
    /* -- */
    char b_modifier_shift;
    char b_modifier_control;
    char b_modifier_alt;
    char c_padding[5u];
};

cv_screen_key * cv_screen_key_create(
    cv_screen_key_desc const * p_desc);

void cv_screen_key_destroy( cv_screen_key * p_this);

cv_bool cv_screen_key_query( cv_screen_key const * p_this,
    cv_screen_key_desc * r_desc);

#endif /* #ifndef cv_screen_key_h_ */

/* end-of-file: cv_screen_key.h */
