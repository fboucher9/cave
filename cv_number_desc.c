/* See LICENSE for license details */

#include <cv_number_desc.h>

cv_number_format const * cv_number_format_dec(void) {
    static cv_number_format g_format_dec = {
        0, 0, 0, 0 };
    return &g_format_dec;
}

cv_number_format const * cv_number_format_hex(void) {
    static cv_number_format g_format_hex = {
        cv_number_flag_unsigned | cv_number_flag_hexadecimal,
        0, 0, 0 };
    return &g_format_hex;
}

cv_number_format const * cv_number_format_hex2(void) {
    static cv_number_format g_format_hex2 = {
        cv_number_flag_unsigned | cv_number_flag_hexadecimal,
        0, 2, 0 };
    return &g_format_hex2;
}

cv_number_format const * cv_number_format_hex4(void) {
    static cv_number_format g_format_hex4 = {
        cv_number_flag_unsigned | cv_number_flag_hexadecimal,
        0, 4, 0 };
    return &g_format_hex4;
}

cv_number_format const * cv_number_format_hex8(void) {
    static cv_number_format g_format_hex8 = {
        cv_number_flag_unsigned | cv_number_flag_hexadecimal,
        0, 4, 0 };
    return &g_format_hex8;
}

/* end-of-file: cv_number_desc.c */
