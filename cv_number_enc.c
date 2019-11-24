/* See LICENSE for license details */

/*

*/

#include <cv_number_enc.h>

#include <cv_number_desc.h>

#include <cv_string_it.h>

#include <cv_sizeof.h>

enum cv_number_machine
{
    cv_number_machine_invalid = 0,

    cv_number_machine_before_space = 1,

    cv_number_machine_sign = 2,

    cv_number_machine_prefix = 3,

    cv_number_machine_before_dot = 4,

    cv_number_machine_dot = 5,

    cv_number_machine_after_dot = 6,

    cv_number_machine_suffix = 7,

    cv_number_machine_after_space = 8,

    cv_number_machine_done = 9

};

static unsigned char const g_number_digit_lower[16u] =
{
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'a',
    'b',
    'c',
    'd',
    'e',
    'f'
};

static unsigned char const g_number_digit_upper[16u] =
{
    '0',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    'A',
    'B',
    'C',
    'D',
    'E',
    'F'
};

static cv_bool cv_number_enc_init_digits(
    cv_number_enc * p_this)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        unsigned long i_unsigned = 0;
        if (cv_number_flag_unsigned & p_this->o_desc.o_format.i_flags)
        {
            i_unsigned = p_this->o_desc.o_data.i_unsigned;
            p_this->b_negative = 0;
        }
        else
        {
            if (p_this->o_desc.o_data.i_signed >= 0)
            {
                i_unsigned = cv_cast_(unsigned long, p_this->o_desc.o_data.i_signed);
                p_this->b_negative = 0;
            }
            else
            {
                i_unsigned = cv_cast_(unsigned long, -p_this->o_desc.o_data.i_signed);
                p_this->b_negative = 1;
            }
        }
        p_this->i_digit_count = 0;
        {
            unsigned long const i_base =
                (cv_number_flag_hexadecimal & p_this->o_desc.o_format.i_flags)
                ? 16
                : 10;
            unsigned char const * p_digit_ascii =
                (cv_number_flag_upper & p_this->o_desc.o_format.i_flags)
                ? g_number_digit_upper
                : g_number_digit_lower;
            while (i_unsigned &&
                (p_this->i_digit_count < sizeof(p_this->a_digit)))
            {
                unsigned long const i_digit =
                    cv_cast_(unsigned long, i_unsigned % i_base);
                p_this->a_digit[p_this->i_digit_count ++] =
                    p_digit_ascii[i_digit];
                i_unsigned /= i_base;
            }
            if (0 == p_this->i_digit_count)
            {
                p_this->a_digit[0] = '0';
                p_this->i_digit_count = 1;
            }
        }
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_number_enc_init(
    cv_number_enc * p_this,
    cv_number_desc const * p_desc)
{
    cv_bool b_result = cv_false;
    if (p_this && p_desc)
    {
        p_this->o_desc = *(p_desc);
        p_this->i_state = cv_number_machine_invalid;
        p_this->i_state_count = 0;
        p_this->i_digit_count = 0;
        p_this->b_negative = 0;
        if (cv_number_enc_init_digits(p_this))
        {
            if (p_this->b_negative)
            {
                p_this->i_state = cv_number_machine_sign;
                p_this->i_state_count = 0;
            }
            else
            {
                p_this->i_state = cv_number_machine_before_dot;
                p_this->i_state_count = p_this->i_digit_count;
            }
            b_result = cv_true;
        }
    }
    return b_result;
}

void cv_number_enc_cleanup(
    cv_number_enc * p_this)
{
    if (p_this)
    {
    }
}

static cv_number_status cv_number_enc_step(
    cv_number_enc * p_this,
    cv_string_it * p_string_it)
{
    cv_number_status e_status = cv_number_status_fail;
    if (p_this && p_string_it)
    {
        if (cv_number_machine_sign == p_this->i_state)
        {
            if (cv_string_it_write_char(p_string_it, '-'))
            {
                p_this->i_state = cv_number_machine_before_dot;
                p_this->i_state_count = p_this->i_digit_count;
                e_status = cv_number_status_continue;
            }
            else
            {
                e_status = cv_number_status_full;
            }
        }
        else if (cv_number_machine_before_dot == p_this->i_state)
        {
            if (p_this->i_state_count > 0)
            {
                unsigned char c = '\000';
                if (p_this->i_state_count > p_this->i_digit_count)
                {
                    c = '0';
                }
                else
                {
                    c = cv_cast_(unsigned char,
                        p_this->a_digit[p_this->i_state_count - 1]);
                }

                if (cv_string_it_write_char(p_string_it, c))
                {
                    p_this->i_state_count --;

                    if (p_this->i_state_count > 0)
                    {
                        e_status = cv_number_status_continue;
                    }
                    else
                    {
                        p_this->i_state = cv_number_machine_done;
                        e_status = cv_number_status_done;
                    }
                }
                else
                {
                    e_status = cv_number_status_full;
                }
            }
            else
            {
                p_this->i_state = cv_number_machine_done;
                e_status = cv_number_status_done;
            }
        }
        else if (cv_number_machine_done == p_this->i_state)
        {
            e_status = cv_number_status_done;
        }
        else
        {
        }
    }
    return e_status;
}

cv_number_status cv_number_enc_read(
    cv_number_enc * p_this,
    cv_string_it * p_string_it)
{
    cv_number_status e_status = cv_number_status_continue;

    while (cv_number_status_continue == e_status)
    {
        e_status = cv_number_enc_step(p_this, p_string_it);
    }
    return e_status;
}

/* all-in-one service */
cv_number_status cv_number_enc_convert(
    cv_number_desc const * p_desc,
    cv_string_it * p_string_it)
{
    cv_number_status e_status = cv_number_status_fail;
    if (p_desc && p_string_it)
    {
        cv_number_enc o_number_enc = cv_number_enc_initializer_;
        if (cv_number_enc_init(&o_number_enc, p_desc))
        {
            e_status = cv_number_enc_read(&o_number_enc, p_string_it);
            cv_number_enc_cleanup(&o_number_enc);
        }
    }
    return e_status;
}

