/* See LICENSE for license details */

#ifndef cv_number_desc_h_
#define cv_number_desc_h_

#include <cv_number_pred.h>

#include <cv_types.h>

union cv_number_data
{
    cv_sll ll_align;
    signed long i_signed;
    unsigned long i_unsigned;
};

#define cv_number_data_initializer_ { 0 }

/* Verify sizeof data members */
typedef char cv_verify_sizeof_number_data [
    (sizeof(signed long) == sizeof(unsigned long))
    ? 1 : -1 ];

enum cv_number_flag {
    cv_number_flag_unsigned = 1,
    cv_number_flag_hexadecimal = 2,
    cv_number_flag_upper = 4,
    cv_number_flag_left = 8,
    cv_number_flag_center = 16,
    cv_number_flag_plus = 32,
    cv_number_flag_space = 64
};

struct cv_number_format {
    short i_flags;
    short i_width;
    short i_digits;
    short i_precision;
};

#define cv_number_format_initializer_ { 0, 0, 0, 0 }

cv_number_format const * cv_number_format_dec(void);

cv_number_format const * cv_number_format_hex(void);

cv_number_format const * cv_number_format_hex2(void);

cv_number_format const * cv_number_format_hex4(void);

cv_number_format const * cv_number_format_hex8(void);

struct cv_number_desc
{
    cv_number_data o_data;
    /* -- */
    cv_number_format o_format;
};

#define cv_number_desc_initializer_ \
{ cv_number_data_initializer_, cv_number_format_initializer_ }

#endif /* #ifndef cv_number_desc_h_ */

/* end-of-file: cv_number_desc.h */
