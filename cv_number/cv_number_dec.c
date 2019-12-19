/* See LICENSE for license details */

/*
 *  Module: cv_number_dec.c
 *
 *  Description: Decode the text representation of numbers.
 */

#include <cv_number/cv_number_dec.h>
#include <cv_debug/cv_debug.h>
#include <cv_algo/cv_array_it.h>

cv_debug_decl_(g_class);

/*
 *
 */

enum dec_machine {
    dec_machine_invalid = 0,
    dec_machine_leading_whitespace,
    dec_machine_sign,
    dec_machine_first_zero,
    dec_machine_before_digit,
    dec_machine_dot,
    dec_machine_after_digit,
    dec_machine_trailing_whitespace
};

/*
 *
 */

void cv_number_dec_init(
    cv_number_dec * p_this,
    unsigned int i_base) {
    cv_debug_construct_(g_class, p_this);
    cv_number_desc_init(&p_this->o_desc);
    p_this->i_state = dec_machine_leading_whitespace;
    p_this->o_desc.o_format.i_base = i_base;
}

/*
 *
 */

void cv_number_dec_cleanup(
    cv_number_dec * p_this) {
    cv_number_desc_cleanup(&p_this->o_desc);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

static cv_bool cv_number_dec_lookup_digit(unsigned char i_value,
    unsigned long * r_digit) {
    cv_bool b_result = cv_false;
    unsigned long i_digit = 0;
    if (('0' <= i_value) && ('9' >= i_value)) {
        i_digit = i_value;
        i_digit = i_digit - '0';
        *r_digit = i_digit;
        b_result = cv_true;
    } else if (('a' <= i_value) && ('f' >= i_value)) {
        i_digit = i_value;
        i_digit = i_digit - ('a' - 10);
        *r_digit = i_digit;
        b_result = cv_true;
    } else if (('A' <= i_value) && ('F' >= i_value)) {
        i_digit = i_value;
        i_digit = i_digit - ('A' - 10);
        *r_digit = i_digit;
        b_result = cv_true;
    } else {
        b_result = cv_false;
    }
    return b_result;
}

/*
 *
 */

static int cv_number_dec_process_after_digit(
    cv_number_dec * p_this,
    unsigned char i_value) {
    unsigned long i_digit = 0;
    if (cv_number_dec_lookup_digit(i_value, &i_digit)) {
        if (i_digit < p_this->o_desc.o_format.i_base) {
            if (('A' <= i_value) && ('F' >= i_value)) {
                p_this->o_desc.o_format.i_flags |= cv_number_flag_upper;
            }
            p_this->o_desc.o_format.i_width ++;
            p_this->o_desc.o_format.i_digits ++;
            p_this->o_desc.o_format.i_precision ++;
            p_this->o_desc.o_data.i_unsigned =
                ((p_this->o_desc.o_data.i_unsigned * p_this->o_desc.o_format.i_base)
                    + i_digit);
            p_this->i_state = dec_machine_after_digit;
            return cv_number_status_continue;
        } else {
            p_this->i_state = dec_machine_invalid;
            return cv_number_status_fail;
        }
    } else {
        p_this->i_state = dec_machine_trailing_whitespace;
        return cv_number_status_done;
    }
}

/*
 *
 */

static int cv_number_dec_process_dot(
    cv_number_dec * p_this,
    unsigned char i_value) {
    return cv_number_dec_process_after_digit(p_this, i_value);
}

/*
 *
 */

static int cv_number_dec_process_before_digit(
    cv_number_dec * p_this,
    unsigned char i_value) {
    unsigned long i_digit = 0;
    if (cv_number_dec_lookup_digit(i_value, &i_digit)) {
        if (i_digit < p_this->o_desc.o_format.i_base) {
            if (('A' <= i_value) && ('F' >= i_value)) {
                p_this->o_desc.o_format.i_flags |= cv_number_flag_upper;
            }
            p_this->o_desc.o_format.i_width ++;
            p_this->o_desc.o_format.i_digits ++;
            p_this->o_desc.o_data.i_unsigned =
                ((p_this->o_desc.o_data.i_unsigned * p_this->o_desc.o_format.i_base)
                    + i_digit);
            p_this->i_state = dec_machine_before_digit;
            return cv_number_status_continue;
        } else {
            p_this->i_state = dec_machine_invalid;
            return cv_number_status_fail;
        }
    } else if ('.' == i_value) {
        p_this->o_desc.o_format.i_width ++;
        p_this->i_state = dec_machine_dot;
        return cv_number_status_continue;
    } else {
        p_this->i_state = dec_machine_trailing_whitespace;
        return cv_number_status_done;
    }
}

/*
 *
 */

static int cv_number_dec_process_first_zero(
    cv_number_dec * p_this,
    unsigned char i_value) {
    /* Ignore hex prefix? */
    if (('x' == i_value) || ('X' == i_value)) {
        if ('X' == i_value) {
            p_this->o_desc.o_format.i_flags |= cv_number_flag_upper;
        }
        p_this->o_desc.o_format.i_flags |= cv_number_flag_prefix;
        p_this->o_desc.o_format.i_base = 16;
        p_this->o_desc.o_format.i_width --;
        p_this->o_desc.o_format.i_digits --;
        p_this->i_state = dec_machine_before_digit;
        return cv_number_status_continue;
    } else {
        return cv_number_dec_process_before_digit(p_this, i_value);
    }
}

/*
 *
 */

static int cv_number_dec_process_sign(
    cv_number_dec * p_this,
    unsigned char i_value) {
    if ('0' == i_value) {
        p_this->o_desc.o_format.i_width ++;
        p_this->o_desc.o_format.i_digits ++;
        p_this->i_state = dec_machine_first_zero;
        return cv_number_status_continue;
    } else {
        return cv_number_dec_process_before_digit(p_this, i_value);
    }
}

/*
 *
 */

static int cv_number_dec_process_leading_whitespace(
    cv_number_dec * p_this,
    unsigned char i_value) {
    if ((' ' == i_value) || ('\t' == i_value) ||
        ('\r' == i_value) || ('\n' == i_value)) {
        p_this->o_desc.o_format.i_width ++;
        p_this->i_state = dec_machine_leading_whitespace;
        return cv_number_status_continue;
    } else if (('-' == i_value) || ('+' == i_value)) {
        if ('+' == i_value) {
            p_this->o_desc.o_format.i_flags |= cv_number_flag_plus;
        }
        p_this->o_desc.o_data.b_negative = ('-' == i_value);
        p_this->o_desc.o_format.i_width ++;
        p_this->i_state = dec_machine_sign;
        return cv_number_status_continue;
    } else {
        return cv_number_dec_process_sign(p_this, i_value);
    }
}

/*
 *
 */

int cv_number_dec_step(
    cv_number_dec * p_this,
    cv_array_it * p_array_it) {
    if (dec_machine_invalid == p_this->i_state) {
        return cv_number_status_fail;
    } else if (dec_machine_trailing_whitespace == p_this->i_state) {
        return cv_number_status_done;
    } else {
        unsigned char i_value = 0;
        if (cv_array_it_read_next_char(p_array_it, &i_value)) {
            if (dec_machine_leading_whitespace == p_this->i_state) {
                return cv_number_dec_process_leading_whitespace(
                    p_this, i_value);
            } else if (dec_machine_sign == p_this->i_state) {
                /* expect digit or dot */
                return cv_number_dec_process_sign(
                    p_this, i_value);
            } else if (dec_machine_first_zero == p_this->i_state) {
                return cv_number_dec_process_first_zero(
                    p_this, i_value);
            } else if (dec_machine_before_digit == p_this->i_state) {
                return cv_number_dec_process_before_digit(
                    p_this, i_value);
            } else if (dec_machine_dot == p_this->i_state) {
                return cv_number_dec_process_dot(
                    p_this, i_value);
            } else if (dec_machine_after_digit == p_this->i_state) {
                return cv_number_dec_process_after_digit(
                    p_this, i_value);
            } else {
                p_this->i_state = dec_machine_invalid;
                return cv_number_status_fail;
            }
        } else {
            return cv_number_status_more_data;
        }
    }
}

/* end-of-file: cv_number_dec.c */
