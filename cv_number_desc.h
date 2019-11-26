/* See LICENSE for license details */

#ifndef cv_number_desc_h_
#define cv_number_desc_h_

union cv_number_data
{
    signed long i_signed;
    unsigned long i_unsigned;
};

#define cv_number_data_initializer_ { 0 }

/* Verify sizeof data members */
typedef char cv_verify_sizeof_number_data [
    (sizeof(signed long) == sizeof(unsigned long))
    ? 1 : -1 ];

enum cv_number_flag
{
    cv_number_flag_unsigned = 1,

    cv_number_flag_hexadecimal = 2,

    cv_number_flag_upper = 4,

    cv_number_flag_left = 8,

    cv_number_flag_center = 16,

    cv_number_flag_plus = 32,

    cv_number_flag_space = 64

};

struct cv_number_format
{
    short i_width;
    short i_digits;
    short i_precision;
    short i_flags;
};

#define cv_number_format_initializer_ { 0, 0, 0, 0 }

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
