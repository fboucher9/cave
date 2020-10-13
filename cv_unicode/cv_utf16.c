/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_utf16.h>
#include <cv_algo/cv_array_it.h>

/*
 *
 */

cv_bool cv_utf16be_decode(cv_array_it * p_input, unsigned long * r_output) {
    cv_bool b_result = cv_false;
    cv_array_ptr o_ptr;
    if (cv_array_it_get_next_array(p_input, 2, &o_ptr)) {
        unsigned long const i_w1h = o_ptr.pc_uchar[0u];
        unsigned long const i_w1l = o_ptr.pc_uchar[1u];
        unsigned long const i_w1 = (i_w1h << 8u) + i_w1l;
        if ((i_w1 & 0xFC00ul) == 0xD800ul) {
            if (cv_array_it_get_next_array(p_input, 2, &o_ptr)) {
                unsigned long const i_w2h = o_ptr.pc_uchar[0u];
                unsigned long const i_w2l = o_ptr.pc_uchar[1u];
                unsigned long const i_w2 = (i_w2h << 8u) + i_w2l;
                if ((i_w2 & 0xFC00ul) == 0xDC00ul) {
                    *r_output = ((i_w1 & 0x03FFul) << 10u) +
                        ((i_w2 & 0x03FFul) << 0u) + 0x10000ul;
                    b_result = cv_true;
                }
            }
        } else if ((i_w1 & 0xFC00ul) == 0xDC00ul) {
        } else {
            *r_output = i_w1;
            b_result = cv_true;
        }
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_utf16le_decode(cv_array_it * p_input, unsigned long * r_output) {
    cv_bool b_result = cv_false;
    cv_array_ptr o_ptr;
    if (cv_array_it_get_next_array(p_input, 2, &o_ptr)) {
        unsigned long const i_w1h = o_ptr.pc_uchar[1u];
        unsigned long const i_w1l = o_ptr.pc_uchar[0u];
        unsigned long const i_w1 = (i_w1h << 8u) + i_w1l;
        if ((i_w1 & 0xFC00ul) == 0xD800ul) {
            if (cv_array_it_get_next_array(p_input, 2, &o_ptr)) {
                unsigned long const i_w2h = o_ptr.pc_uchar[1u];
                unsigned long const i_w2l = o_ptr.pc_uchar[0u];
                unsigned long const i_w2 = (i_w2h << 8u) + i_w2l;
                if ((i_w2 & 0xFC00ul) == 0xDC00ul) {
                    *r_output = ((i_w1 & 0x03FFul) << 10u) +
                        ((i_w2 & 0x03FFul) << 0u) + 0x10000ul;
                    b_result = cv_true;
                }
            }
        } else if ((i_w1 & 0xFC00ul) == 0xDC00ul) {
            /* out of sync */
        } else {
            *r_output = i_w1;
            b_result = cv_true;
        }
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_utf16be_encode(unsigned long i_input, cv_array_it * p_output) {
    cv_bool b_result = cv_false;
    cv_array_ptr o_ptr;
    if (i_input <= 0xfffful) {
        if (cv_array_it_get_next_array(p_output, 2, &o_ptr)) {
            unsigned long const i_w1h = ((i_input >> 8u) & 0xfful);
            unsigned long const i_w1l = ((i_input >> 0u) & 0xfful);
            o_ptr.p_uchar[0u] = i_w1h & 0xffu;
            o_ptr.p_uchar[1u] = i_w1l & 0xffu;
            b_result = cv_true;
        }
    } else if (i_input <= 0x10fffful) {
        if (cv_array_it_get_next_array(p_output, 4, &o_ptr)) {
            unsigned long const i_temp = i_input - 0x10000ul;
            unsigned long const i_w1 = ((i_temp >> 10u) & 0x3fful) | 0xd800ul;
            unsigned long const i_w2 = ((i_temp >> 0u) & 0x3fful) | 0xdc00ul;
            unsigned long const i_w1h = (i_w1 >> 8u) & 0xfful;
            unsigned long const i_w1l = (i_w1 >> 0u) & 0xfful;
            unsigned long const i_w2h = (i_w2 >> 8u) & 0xfful;
            unsigned long const i_w2l = (i_w2 >> 0u) & 0xfful;
            o_ptr.p_uchar[0u] = i_w1h & 0xffu;
            o_ptr.p_uchar[1u] = i_w1l & 0xffu;
            o_ptr.p_uchar[2u] = i_w2h & 0xffu;
            o_ptr.p_uchar[3u] = i_w2l & 0xffu;
            b_result = cv_true;
        }
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_utf16le_encode(unsigned long i_input, cv_array_it * p_output) {
    cv_bool b_result = cv_false;
    cv_array_ptr o_ptr;
    if (i_input <= 0xfffful) {
        if (cv_array_it_get_next_array(p_output, 2, &o_ptr)) {
            unsigned long const i_w1h = ((i_input >> 8u) & 0xfful);
            unsigned long const i_w1l = ((i_input >> 0u) & 0xfful);
            o_ptr.p_uchar[1u] = i_w1h & 0xffu;
            o_ptr.p_uchar[0u] = i_w1l & 0xffu;
            b_result = cv_true;
        }
    } else if (i_input <= 0x10fffful) {
        if (cv_array_it_get_next_array(p_output, 4, &o_ptr)) {
            unsigned long const i_temp = i_input - 0x10000ul;
            unsigned long const i_w1 = ((i_temp >> 10u) & 0x3fful) | 0xd800ul;
            unsigned long const i_w2 = ((i_temp >> 0u) & 0x3fful) | 0xdc00ul;
            unsigned long const i_w1h = (i_w1 >> 8u) & 0xfful;
            unsigned long const i_w1l = (i_w1 >> 0u) & 0xfful;
            unsigned long const i_w2h = (i_w2 >> 8u) & 0xfful;
            unsigned long const i_w2l = (i_w2 >> 0u) & 0xfful;
            o_ptr.p_uchar[1u] = i_w1h & 0xffu;
            o_ptr.p_uchar[0u] = i_w1l & 0xffu;
            o_ptr.p_uchar[3u] = i_w2h & 0xffu;
            o_ptr.p_uchar[2u] = i_w2l & 0xffu;
            b_result = cv_true;
        }
    }
    return b_result;
}

/* end-of-file: cv_utf16.c */
