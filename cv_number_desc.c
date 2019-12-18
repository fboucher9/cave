/* See LICENSE for license details */

#include <cv_number_desc.h>
#include <cv_misc/cv_unused.h>

/*
 *
 */

void cv_number_desc_init( cv_number_desc * p_this) {
    p_this->o_data.i_unsigned = 0;
    p_this->o_data.b_negative = 0;
    p_this->o_format.i_flags = 0;
    p_this->o_format.i_width = 0;
    p_this->o_format.i_digits = 0;
    p_this->o_format.i_precision = 0;
    p_this->o_format.i_base = 0;
}

/*
 *
 */

void cv_number_desc_cleanup( cv_number_desc * p_this) {
    cv_unused_(p_this);
}

/* end-of-file: cv_number_desc.c */
