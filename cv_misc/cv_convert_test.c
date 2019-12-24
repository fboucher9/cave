/* See LICENSE for license details */

/*
 *
 */

#include <cv_misc/cv_convert_test.h>
#include <cv_misc/cv_convert.h>
#include <cv_test_print.h>

/*
 *
 */

void cv_convert_test(void) {
    signed char const c_value = 100;
    signed short const s_value = 10000;
    signed int const i_value = 20000;
    signed long const l_value = 1000000L;
    cv_sptr p_value = 2000000L;
    cv_sll ll_value = 2000000L;
    ll_value *= 1000000L;
    /* Verify cast to unsigned char */ {
        unsigned char u_result = 0;
        u_result = cv_convert_c2u_(c_value);
        (void)(u_result);
    }
    /* Verify cast to unsigned short */ {
        unsigned short u_result = 0;
        u_result = cv_convert_s2u_(c_value);
        u_result = cv_convert_s2u_(s_value);
        (void)(u_result);
    }
    /* Verify cast to unsigned int */ {
        unsigned int u_result = 0;
        u_result = cv_convert_i2u_(c_value);
        u_result = cv_convert_i2u_(s_value);
        u_result = cv_convert_i2u_(i_value);
        (void)(u_result);
    }
    /* Verify cast to unsigned long */ {
        unsigned long u_result = 0;
        u_result = cv_convert_l2u_(c_value);
        u_result = cv_convert_l2u_(s_value);
        u_result = cv_convert_l2u_(i_value);
        u_result = cv_convert_l2u_(l_value);
        (void)(u_result);
    }
    /* Verify cast to uptr */ {
        cv_uptr u_result = 0;
        u_result = cv_convert_p2u_(c_value);
        u_result = cv_convert_p2u_(s_value);
        u_result = cv_convert_p2u_(i_value);
        u_result = cv_convert_p2u_(l_value);
        u_result = cv_convert_p2u_(p_value);
        (void)(u_result);
    }
    /* Verify cast to ull */ {
        cv_ull u_result = 0;
        u_result = cv_convert_ll2u_(c_value);
        u_result = cv_convert_ll2u_(s_value);
        u_result = cv_convert_ll2u_(i_value);
        u_result = cv_convert_ll2u_(l_value);
        u_result = cv_convert_ll2u_(p_value);
        u_result = cv_convert_ll2u_(ll_value);
        (void)(u_result);
    }
    /* Verify cast to signed char */ {
        signed char i_result = 0;
        i_result = cv_convert_u2c_(123u);
        (void)i_result;
    }
    /* Verify cast to signed short */ {
        signed short i_result = 0;
        i_result = cv_convert_u2s_(123u);
        (void)i_result;
    }
    /* Verify cast to signed int */ {
        signed int i_result = 0;
        i_result = cv_convert_u2i_(123u);
        (void)i_result;
    }
    /* Verify cast to signed long */ {
        signed long i_result = 0;
        i_result = cv_convert_u2l_(123u);
        (void)i_result;
    }
    /* Verify cast to signed ptr */ {
        cv_sptr i_result = 0;
        i_result = cv_convert_u2p_(123u);
        (void)i_result;
    }
    /* Verify cast to sll */ {
        cv_sll i_result = 0;
        i_result = cv_convert_u2ll_(123u);
        (void)i_result;
    }
}

/* end-of-file: cv_convert_test.c */
