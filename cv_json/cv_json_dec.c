/* See LICENSE for license details */

/*
 *
 */

#include <cv_json/cv_json_dec.h>
#include <cv_json/cv_json.h>
#include <cv_json/cv_json_type.h>

/*
 *
 */

enum parser_state {
    state_idle = 0,
    state_number_prefix,
    state_number_mantisse,
    state_number_fraction,
    state_number_exponent,
    state_string_normal,
    state_string_escape,
    state_string_unicode1,
    state_string_unicode2,
    state_string_unicode3,
    state_string_unicode4,
    state_string_after,
    state_string_label,
    state_number_sign,
    state_number_zero,
    state_number_dec_digit,
    state_number_frac_digit,
    state_number_exp_prefix,
    state_number_exp_sign,
    state_number_exp_digit,
    state_number_hex_digit,
    state_end
};

/*
 *
 */

typedef struct parser {
    unsigned e_state;
    unsigned i_accum_len;
    unsigned i_stack_len;
    unsigned ui_padding[1u];
    /* -- */
    cv_json * a_stack[8u];
    /* -- */
    unsigned char a_accum[256u];
} parser;

/*
 *
 */

static void parser_init(parser * p_this) {
    p_this->e_state = state_idle;
}

/*
 *
 */

static void parser_cleanup(parser * p_this) {
    (void)p_this;
}

/*
 *
 */

static void parser_accumulate(parser * p_this, unsigned char c_token) {
    if (p_this->i_accum_len < 256u) {
        p_this->a_accum[p_this->i_accum_len] = c_token;
        p_this->i_accum_len ++;
    }
}

/*
 *
 */

static void parser_step(parser * p_this,
    unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    do {
        b_repeat = cv_false;
        if (state_idle == p_this->e_state) {
            if (' ' == c_token) {
            } else if ('\t' == c_token) {
            } else if ('\r' == c_token) {
            } else if ('\n' == c_token) {
            } else if (',' == c_token) {
            } else if (':' == c_token) {
            } else if ('\"' == c_token) {
                p_this->e_state = state_string_normal;
            } else if ('-' == c_token) {
                /* process sign */
                p_this->e_state = state_number_sign;
            } else if ('+' == c_token) {
                /* process sign */
                p_this->e_state = state_number_sign;
            } else if ('0' == c_token) {
                p_this->e_state = state_number_zero;
            } else if (('1' <= c_token) && ('9' >= c_token)) {
                p_this->e_state = state_number_dec_digit;
                b_repeat = cv_true;
            } else if ('.' == c_token) {
                p_this->e_state = state_number_frac_digit;
            } else if ('[' == c_token) {
                /* create an array node */
                /* add to stack of nodes */
                p_this->e_state = state_idle;
            } else if ('{' == c_token) {
                /* create an object node */
                /* add to stack of nodes */
                p_this->e_state = state_idle;
            } else if (']' == c_token) {
                /* complete this array */
                p_this->e_state = state_idle;
            } else if ('}' == c_token) {
                /* complete this object */
                p_this->e_state = state_idle;
            } else {
                /* could be null, true, false or error */
            }
        } else if (state_string_normal == p_this->e_state) {
            if ('\"' == c_token) {
                /* if parent is object and label is required */
                /* flush the accumulated string */
                /* create a string node */
                if (0 == p_this->i_stack_len) {
                    cv_json * p_value = cv_json_create();
                    if (p_value) {
                        cv_array o_string;
                        cv_array_init_vector(&o_string,
                            p_this->a_accum,
                            p_this->i_accum_len);
                        cv_json_set_type(p_value, cv_json_type_string);
                        cv_json_set_string(p_value, &o_string);
                        cv_array_cleanup(&o_string);
                        p_this->a_stack[0u] = p_value;
                    }
                    p_this->e_state = state_end;
                } else {
                    p_this->e_state = state_idle;
                }
            } else if ('\\' == c_token) {
                p_this->e_state = state_string_escape;
            } else {
                /* store token into chunk list... */
                parser_accumulate(p_this, c_token);
            }
        } else if (state_string_escape == p_this->e_state) {
            if (('u' == c_token) ||
                ('U' == c_token)) {
                p_this->e_state = state_string_unicode1;
            } else if ('t' == c_token) {
                parser_accumulate(p_this, '\t');
                p_this->e_state = state_string_normal;
            } else if ('b' == c_token) {
                parser_accumulate(p_this, '\b');
                p_this->e_state = state_string_normal;
            } else if ('r' == c_token) {
                parser_accumulate(p_this, '\r');
                p_this->e_state = state_string_normal;
            } else if ('n' == c_token) {
                parser_accumulate(p_this, '\n');
                p_this->e_state = state_string_normal;
            } else {
                parser_accumulate(p_this, c_token);
                p_this->e_state = state_string_normal;
            }
        } else if (state_string_unicode1 == p_this->e_state) {
            /* store this character into unicode accumulator */
            p_this->e_state = state_string_unicode2;
        } else if (state_string_unicode2 == p_this->e_state) {
            /* store this character into unicode accumulator */
            p_this->e_state = state_string_unicode3;
        } else if (state_string_unicode3 == p_this->e_state) {
            /* store this character into unicode accumulator */
            p_this->e_state = state_string_unicode4;
        } else if (state_string_unicode4 == p_this->e_state) {
            /* store this character into unicode accumulator */
            parser_accumulate(p_this, '!');
            p_this->e_state = state_string_normal;
        } else if (state_number_sign == p_this->e_state) {
            if ('0' == c_token) {
                p_this->e_state = state_number_zero;
            } else if (('1' <= c_token) && ('9' >= c_token)) {
                p_this->e_state = state_number_dec_digit;
                b_repeat = cv_true;
            } else {
                /* error ? */
                p_this->e_state = state_idle;
            }
        } else if (state_number_zero == p_this->e_state) {
            if (('x' == c_token) ||
                ('X' == c_token)) {
                p_this->e_state = state_number_hex_digit;
            } else if (('0' <= c_token) && ('9' >= c_token)) {
                p_this->e_state = state_number_dec_digit;
                b_repeat = cv_true;
            } else if ('.' == c_token) {
                p_this->e_state = state_number_frac_digit;
            } else {
                /* error ? */
                p_this->e_state = state_idle;
            }
        } else if (state_number_dec_digit == p_this->e_state) {
            if (('0' <= c_token) && ('9' >= c_token)) {
                /* process the digit */
                p_this->e_state = state_number_dec_digit;
            } else if ('.' == c_token) {
                p_this->e_state = state_number_frac_digit;
            } else if (('e' == c_token) ||
                ('E' == c_token)) {
            } else {
                /* error ? */
                p_this->e_state = state_idle;
            }
        } else if (state_number_frac_digit == p_this->e_state) {
            if (('0' <= c_token) && ('9' >= c_token)) {
                p_this->e_state = state_number_frac_digit;
            } else if (('e' == c_token) ||
                ('E' == c_token)) {
                p_this->e_state = state_number_exp_prefix;
            } else {
                /* error ? */
                p_this->e_state = state_idle;
            }
        } else if (state_number_exp_prefix == p_this->e_state) {
            if ('-' == c_token) {
                p_this->e_state = state_number_exp_digit;
            } else if ('+' == c_token) {
                p_this->e_state = state_number_exp_digit;
            } else if (('0' <= c_token) && ('9' >= c_token)) {
                p_this->e_state = state_number_exp_digit;
                b_repeat = cv_true;
            } else {
                /* error ? */
                p_this->e_state = state_idle;
            }
        } else if (state_number_hex_digit == p_this->e_state) {
            if (('0' <= c_token) && ('9' >= c_token)) {
                /* process digit */
                p_this->e_state = state_number_hex_digit;
            } else if (('a' <= c_token) && ('f' >= c_token)) {
                /* process digit */
                p_this->e_state = state_number_hex_digit;
            } else if (('A' <= c_token) && ('F' >= c_token)) {
                /* process digit */
                p_this->e_state = state_number_hex_digit;
            } else {
                /* error ? */
                p_this->e_state = state_idle;
            }
        } else {
            /* error ? */
        }
    } while (b_repeat);
}

static void parser_flush(parser * p_this) {
    if (state_string_after == p_this->e_state) {
    }
}

/*
 *
 */

static void parser_run(parser * p_this,
    cv_array_it * p_document) {
    unsigned char c_token = 0;
    while (cv_array_it_read_next_char(p_document, &c_token)) {
        parser_step(p_this, c_token);
    }
    parser_flush(p_this);
}

/*
 *
 */

cv_json * cv_json_dec( cv_array_it * p_document ) {
    cv_json * p_result = 0;
    parser o_parser = {0};
    parser_init(&o_parser);
    parser_run(&o_parser, p_document);
    p_result = o_parser.a_stack[0];
    parser_cleanup(&o_parser);
    return p_result;
}

