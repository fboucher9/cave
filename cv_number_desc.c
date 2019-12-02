/* See LICENSE for license details */

#include <cv_number_desc.h>

cv_number_format cv_number_format_dec = {
    0, 0, 0, 0 };

cv_number_format cv_number_format_hex = {
    cv_number_flag_unsigned | cv_number_flag_hexadecimal,
    0, 0, 0 };

cv_number_format cv_number_format_hex2 = {
    cv_number_flag_unsigned | cv_number_flag_hexadecimal,
    0, 2, 0 };

cv_number_format cv_number_format_hex4 = {
    cv_number_flag_unsigned | cv_number_flag_hexadecimal,
    0, 4, 0 };

cv_number_format cv_number_format_hex8 = {
    cv_number_flag_unsigned | cv_number_flag_hexadecimal,
    0, 4, 0 };

/* end-of-file: cv_number_desc.c */
