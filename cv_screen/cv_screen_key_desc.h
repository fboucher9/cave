/* See LICENSE for license details */

#ifndef cv_screen_key_desc_h_
#define cv_screen_key_desc_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>
#include <cv_misc/cv_bool.h>
#include <cv_algo/cv_array.h>

/*
 *
 */

struct cv_screen_key_desc {
    cv_bool b_modifier_shift;
    cv_bool b_modifier_control;
    cv_bool b_modifier_alt;
    char c_padding[5u];
    /* -- */
    cv_array o_sequence;
    /* -- */
    cv_array o_name;
};

void cv_screen_key_desc_init( cv_screen_key_desc * p_this );
void cv_screen_key_desc_cleanup( cv_screen_key_desc * p_this );

#endif /* #ifndef cv_screen_key_desc_h_ */

/* end-of-file: cv_screen_key_desc.h */
