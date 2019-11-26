/* See LICENSE for license details */

/*

*/

#include <cv_number_enc.h>

#include <cv_number_desc.h>

#include <cv_string_it.h>

#include <cv_sizeof.h>

#include <cv_memory.h>

enum cv_number_machine
{
    cv_number_machine_invalid = 0,

    cv_number_machine_before_space,

    cv_number_machine_sign,

    cv_number_machine_before_zero,

    cv_number_machine_before_dot,

    cv_number_machine_dot,

    cv_number_machine_after_zero,

    cv_number_machine_after_dot,

    cv_number_machine_after_space,

    cv_number_machine_done

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
        }
        else
        {
            if (p_this->o_desc.o_data.i_signed >= 0)
            {
                i_unsigned = cv_cast_(unsigned long, p_this->o_desc.o_data.i_signed);
            }
            else
            {
                i_unsigned = cv_cast_(unsigned long, -p_this->o_desc.o_data.i_signed);
                p_this->a_sign[0u] = '-';
                p_this->b_sign = 1;
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
                (p_this->i_digit_count < cv_cast_(short, sizeof(p_this->a_digit))))
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
        cv_memory_zero(p_this, cv_sizeof_(*p_this));
        p_this->o_desc = *(p_desc);
        if (cv_number_enc_init_digits(p_this))
        {
            short i_width = 0;
            if (!p_this->b_sign)
            {
                if (p_this->o_desc.o_format.i_flags & cv_number_flag_plus)
                {
                    p_this->a_sign[0] = '+';
                    p_this->b_sign = 1;
                }
                else if (p_this->o_desc.o_format.i_flags & cv_number_flag_space)
                {
                    p_this->a_sign[0] = ' ';
                    p_this->b_sign = 1;
                }
            }
            if (p_this->o_desc.o_format.i_precision)
            {
                if (p_this->o_desc.o_format.i_precision >=
                    p_this->o_desc.o_format.i_digits)
                {
                    p_this->o_desc.o_format.i_digits =
                        (
                            p_this->o_desc.o_format.i_precision + 1) & 0x7FFF;
                }

                p_this->b_dot = 1;
                if (p_this->o_desc.o_format.i_precision > p_this->i_digit_count)
                {
                    p_this->i_before_zero = 1;
                    p_this->i_after_zero = (
                            p_this->o_desc.o_format.i_precision
                            - p_this->i_digit_count) & 0x7FFF;
                }
                else
                {
                    if (p_this->o_desc.o_format.i_digits > p_this->i_digit_count)
                    {
                        p_this->i_before_zero = (
                                p_this->o_desc.o_format.i_digits
                                - p_this->i_digit_count) & 0x7FFF;
                    }
                }
            }
            else
            {
                if (p_this->o_desc.o_format.i_digits > p_this->i_digit_count)
                {
                    p_this->i_before_zero = ((
                            p_this->o_desc.o_format.i_digits
                            - p_this->i_digit_count) & 0x7FFF);
                }
            }
            i_width = ((p_this->i_digit_count +
                    p_this->i_before_zero +
                    p_this->b_dot +
                    p_this->i_after_zero +
                    p_this->b_sign) & 0x7FFF);
            if (p_this->o_desc.o_format.i_flags & cv_number_flag_left)
            {
                if (p_this->o_desc.o_format.i_width > i_width)
                {
                    p_this->i_after_space = ((
                            p_this->o_desc.o_format.i_width
                            - i_width) & 0x7FFF);
                }
            }
            else if (p_this->o_desc.o_format.i_flags & cv_number_flag_center)
            {
                if (p_this->o_desc.o_format.i_width > i_width)
                {
                    p_this->i_before_space = (((
                            p_this->o_desc.o_format.i_width
                            - i_width + 1) / 2) & 0x7FFF);
                    p_this->i_after_space = ((
                        p_this->o_desc.o_format.i_width
                        - i_width
                        - p_this->i_before_space) & 0x7FFF);
                }
            }
            else
            {
                if (p_this->o_desc.o_format.i_width > i_width)
                {
                    p_this->i_before_space = ((
                            p_this->o_desc.o_format.i_width
                            - i_width) & 0x7FFF);
                }
            }
            p_this->i_state = cv_number_machine_before_space;
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
        if (cv_number_machine_before_space == p_this->i_state)
        {
            if (p_this->i_before_space > 0)
            {
                if (cv_string_it_write_char(p_string_it, ' '))
                {
                    p_this->i_before_space --;
                    e_status = cv_number_status_continue;
                }
                else
                {
                    e_status = cv_number_status_full;
                }
            }
            else
            {
                p_this->i_state = cv_number_machine_sign;
                e_status = cv_number_status_continue;
            }
        }
        else if (cv_number_machine_sign == p_this->i_state)
        {
            if (p_this->b_sign)
            {
                if (cv_string_it_write_char(p_string_it,
                        p_this->a_sign[0u]))
                {
                    p_this->b_sign = 0;
                    e_status = cv_number_status_continue;
                }
                else
                {
                    e_status = cv_number_status_full;
                }
            }
            else
            {
                p_this->i_state = cv_number_machine_before_zero;
                e_status = cv_number_status_continue;
            }
        }
        else if (cv_number_machine_before_zero == p_this->i_state)
        {
            if (p_this->i_before_zero > 0)
            {
                if (cv_string_it_write_char(p_string_it, '0'))
                {
                    p_this->i_before_zero --;
                    e_status = cv_number_status_continue;
                }
                else
                {
                    e_status = cv_number_status_full;
                }
            }
            else
            {
                p_this->i_state = cv_number_machine_before_dot;
                e_status = cv_number_status_continue;
            }
        }
        else if (cv_number_machine_before_dot == p_this->i_state)
        {
            if (p_this->i_digit_count > p_this->o_desc.o_format.i_precision)
            {
                unsigned char const c = p_this->a_digit[
                    p_this->i_digit_count
                    - 1];

                if (cv_string_it_write_char(p_string_it, c))
                {
                    p_this->i_digit_count --;
                    e_status = cv_number_status_continue;
                }
                else
                {
                    e_status = cv_number_status_full;
                }
            }
            else
            {
                p_this->i_state = cv_number_machine_dot;
                e_status = cv_number_status_continue;
            }
        }
        else if (cv_number_machine_dot == p_this->i_state)
        {
            if (p_this->b_dot)
            {
                if (cv_string_it_write_char(p_string_it, '.'))
                {
                    p_this->b_dot = 0;
                    e_status = cv_number_status_continue;
                }
                else
                {
                    e_status = cv_number_status_full;
                }
            }
            else
            {
                p_this->i_state = cv_number_machine_after_zero;
                e_status = cv_number_status_continue;
            }
        }
        else if (cv_number_machine_after_zero == p_this->i_state)
        {
            if (p_this->i_after_zero > 0)
            {
                if (cv_string_it_write_char(p_string_it, '0'))
                {
                    p_this->i_after_zero --;
                    e_status = cv_number_status_continue;
                }
                else
                {
                    e_status = cv_number_status_full;
                }
            }
            else
            {
                p_this->i_state = cv_number_machine_after_dot;
                e_status = cv_number_status_continue;
            }
        }
        else if (cv_number_machine_after_dot == p_this->i_state)
        {
            if (p_this->i_digit_count > 0)
            {
                unsigned char const c = p_this->a_digit[
                    p_this->i_digit_count
                    - 1];

                if (cv_string_it_write_char(p_string_it, c))
                {
                    p_this->i_digit_count --;
                    e_status = cv_number_status_continue;
                }
                else
                {
                    e_status = cv_number_status_full;
                }
            }
            else
            {
                p_this->i_state = cv_number_machine_after_space;
                e_status = cv_number_status_continue;
            }
        }
        else if (cv_number_machine_after_space == p_this->i_state)
        {
            if (p_this->i_after_space > 0)
            {
                if (cv_string_it_write_char(p_string_it, ' '))
                {
                    p_this->i_after_space --;
                    e_status = cv_number_status_continue;
                }
                else
                {
                    e_status = cv_number_status_full;
                }
            }
            else
            {
                p_this->i_state = cv_number_machine_done;
                e_status = cv_number_status_continue;
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

