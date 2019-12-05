/* See LICENSE for license details */

/*
 *
 */

#include <cv_convert_test.h>
#include <cv_convert.h>
#include <cv_test_print.h>
#include <cv_unused.h>

/*
 *
 */

void cv_convert_test(void) {
    signed char const c_value = 100;
    signed short const s_value = 10000;
    signed int const i_value = 20000;
    signed long const l_value = 1000000L;
    cv_sptr p_value = 2000000L;
    cv_sll ll_value = cv_cast_(cv_sll, 2000000L) * cv_cast_(cv_sll, 1000000L);
    /* Verify cast to unsigned char */ {
        cv_char_to_uchar_(c_value);
    }
    /* Verify cast to unsigned short */ {
        cv_short_to_ushort_(c_value);
        cv_short_to_ushort_(s_value);
    }
    /* Verify cast to unsigned int */ {
        cv_int_to_uint_(c_value);
        cv_int_to_uint_(s_value);
        cv_int_to_uint_(i_value);
    }
    /* Verify cast to unsigned long */ {
        cv_long_to_ulong_(c_value);
        cv_long_to_ulong_(s_value);
        cv_long_to_ulong_(i_value);
        cv_long_to_ulong_(l_value);
    }
    /* Verify cast to uptr */ {
        cv_ptr_to_uptr_(c_value);
        cv_ptr_to_uptr_(s_value);
        cv_ptr_to_uptr_(i_value);
        cv_ptr_to_uptr_(l_value);
        cv_ptr_to_uptr_(p_value);
    }
    /* Verify cast to ull */ {
        cv_ll_to_ull_(c_value);
        cv_ll_to_ull_(s_value);
        cv_ll_to_ull_(i_value);
        cv_ll_to_ull_(l_value);
        cv_ll_to_ull_(p_value);
        cv_ll_to_ull_(ll_value);
    }
}

/* end-of-file: cv_convert_test.c */
