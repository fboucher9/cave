/* See LICENSE for license details */

#ifndef cv_number_format_h_
#define cv_number_format_h_

/*
 *
 */

#include <cv_number/cv_number_pred.h>

/*
 *
 */

enum cv_number_flag {
    cv_number_flag_prefix = 1,
    cv_number_flag_upper = 2,
    cv_number_flag_left = 4,
    cv_number_flag_center = 8,
    cv_number_flag_plus = 16,
    cv_number_flag_space = 32
};

/*
 *
 */

enum cv_number_base {
    cv_number_base_binary = 2,
    cv_number_base_octal = 8,
    cv_number_base_decimal = 10,
    cv_number_base_hexadecimal = 16
};

/*
 *
 */

struct cv_number_format {
    short i_flags;
    short i_width;
    short i_digits;
    short i_precision;
    /* -- */
    unsigned int i_base;
    unsigned int i_padding[1u];
};

cv_number_format const * cv_number_format_dec(void);

cv_number_format const * cv_number_format_hex(void);

cv_number_format const * cv_number_format_hex2(void);

cv_number_format const * cv_number_format_hex4(void);

cv_number_format const * cv_number_format_hex8(void);

#endif /* #ifndef cv_number_format_h_ */

/* end-of-file: cv_number_format.h */
