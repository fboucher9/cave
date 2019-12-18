/* See LICENSE for license details */

#ifndef cv_number_desc_h_
#define cv_number_desc_h_

/*
 *
 */

#include <cv_number_pred.h>
#include <cv_misc/cv_types.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_number_data {
    unsigned long i_unsigned;
    unsigned long b_negative;
};

#define cv_number_data_initializer_ { 0, cv_false }

/* Verify sizeof data members */
typedef char cv_verify_sizeof_number_data [
    (sizeof(signed long) == sizeof(unsigned long))
    ? 1 : -1 ];

enum cv_number_flag {
    cv_number_flag_prefix = 1,
    cv_number_flag_upper = 2,
    cv_number_flag_left = 4,
    cv_number_flag_center = 8,
    cv_number_flag_plus = 16,
    cv_number_flag_space = 32
};

struct cv_number_format {
    short i_flags;
    short i_width;
    short i_digits;
    short i_precision;
    /* -- */
    unsigned int i_base;
    unsigned int i_padding[1u];
};

#define cv_number_format_initializer_ { 0, 0, 0, 0, 0, {0} }

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

void cv_number_desc_init( cv_number_desc * p_this);

void cv_number_desc_cleanup( cv_number_desc * p_this);

#endif /* #ifndef cv_number_desc_h_ */

/* end-of-file: cv_number_desc.h */
