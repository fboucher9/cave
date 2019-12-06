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
        cv_convert_c2u_(c_value);
    }
    /* Verify cast to unsigned short */ {
        cv_convert_s2u_(c_value);
        cv_convert_s2u_(s_value);
    }
    /* Verify cast to unsigned int */ {
        cv_convert_i2u_(c_value);
        cv_convert_i2u_(s_value);
        cv_convert_i2u_(i_value);
    }
    /* Verify cast to unsigned long */ {
        cv_convert_l2u_(c_value);
        cv_convert_l2u_(s_value);
        cv_convert_l2u_(i_value);
        cv_convert_l2u_(l_value);
    }
    /* Verify cast to uptr */ {
        cv_convert_p2u_(c_value);
        cv_convert_p2u_(s_value);
        cv_convert_p2u_(i_value);
        cv_convert_p2u_(l_value);
        cv_convert_p2u_(p_value);
    }
    /* Verify cast to ull */ {
        cv_convert_ll2u_(c_value);
        cv_convert_ll2u_(s_value);
        cv_convert_ll2u_(i_value);
        cv_convert_ll2u_(l_value);
        cv_convert_ll2u_(p_value);
        cv_convert_ll2u_(ll_value);
    }
}

/* end-of-file: cv_convert_test.c */
