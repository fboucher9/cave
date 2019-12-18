/* See LICENSE for license details */

#include <cv_number_desc.h>
#include <cv_misc/cv_unused.h>

cv_number_format const * cv_number_format_dec(void) {
    static cv_number_format g_format_dec = {
        0, 0, 0, 0, 10, {0} };
    return &g_format_dec;
}

cv_number_format const * cv_number_format_hex(void) {
    static cv_number_format g_format_hex = {
        0, 0, 0, 0, 16, {0} };
    return &g_format_hex;
}

cv_number_format const * cv_number_format_hex2(void) {
    static cv_number_format g_format_hex2 = {
        0, 0, 2, 0, 16, {0} };
    return &g_format_hex2;
}

cv_number_format const * cv_number_format_hex4(void) {
    static cv_number_format g_format_hex4 = {
        0, 0, 4, 0, 16, {0} };
    return &g_format_hex4;
}

cv_number_format const * cv_number_format_hex8(void) {
    static cv_number_format g_format_hex8 = {
        0, 0, 8, 0, 16, {0} };
    return &g_format_hex8;
}

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
