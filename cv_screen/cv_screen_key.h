/* See LICENSE for license details */

#ifndef cv_screen_key_h_
#define cv_screen_key_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>
#include <cv_misc/cv_bool.h>
#include <cv_misc/cv_types.h>

void cv_screen_key_load(void);

void cv_screen_key_unload(void);

cv_screen_key * cv_screen_key_create( cv_screen_key_desc const * p_desc);

void cv_screen_key_destroy( cv_screen_key * p_this);

cv_bool cv_screen_key_query( cv_screen_key const * p_this,
    cv_screen_key_desc * r_desc);

cv_bool cv_screen_key_compare( cv_screen_key const * p_this,
    unsigned char const * p_buffer, cv_uptr i_buffer_len);

#endif /* #ifndef cv_screen_key_h_ */

/* end-of-file: cv_screen_key.h */
