/* See LICENSE for license details */

/*
 *
 */

#include <cv_json/cv_json_dec.h>
#include <cv_json/cv_json.h>
#include <cv_json/cv_json_type.h>
#include <cv_algo/cv_array_0.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_runtime.h>
#include <stdio.h>

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
    state_word,
    state_end
};

/*
 *
 */

enum parser_const {
    parser_stack_max = 8,
    parser_accum_max = 256
};

/*
 *
 */

typedef struct parser {
    unsigned e_state;
    unsigned i_accum_len;
    /* -- */
    unsigned i_stack_len;
    unsigned e_number_type;
    /* -- */
    unsigned b_word_started;
    unsigned b_string_started;
    /* -- */
    unsigned i_label_len;
    unsigned i_padding[1u];
    /* -- */
    cv_json * p_final;
    /* -- */
    cv_json * a_stack[parser_stack_max];
    /* -- */
    unsigned char a_accum[parser_accum_max];
    /* -- */
    unsigned char a_label[parser_accum_max];
} parser;

/*
 *
 */

static void parser_init(parser * p_this) {
    p_this->e_state = state_idle;
    p_this->i_accum_len = 0;
    p_this->i_stack_len = 0;
    p_this->e_number_type = 0;
    p_this->b_word_started = 0;
    p_this->b_string_started = 0;
    p_this->p_final = 0;
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
    if (p_this->i_accum_len < parser_accum_max) {
        p_this->a_accum[p_this->i_accum_len] = c_token;
        p_this->i_accum_len ++;
    }
}

/*
 *
 */

static void parser_push(parser * p_this, cv_json * p_value) {
    if (p_this->i_label_len) {
        cv_array o_label;
        cv_array_init_vector(&o_label,
            p_this->a_label,
            p_this->i_label_len);
        cv_json_set_label(p_value, &o_label);
        cv_array_cleanup(&o_label);
        p_this->i_label_len = 0;
    }
    if (0 == p_this->i_stack_len) {
        p_this->p_final = p_value;
        p_this->e_state = state_end;
    } else {
        cv_json_join(p_value,
            p_this->a_stack[p_this->i_stack_len - 1]);
        p_this->e_state = state_idle;
    }
}

/*
 *
 */

static void parser_flush_string(parser * p_this) {
    /* flush the accumulated string */
    /* create a string node */
    if (p_this->b_string_started) {
        cv_json * p_value = cv_json_create();
        p_this->e_state = state_idle;
        if (p_value) {
            cv_array o_string;
            cv_array_init_vector(&o_string,
                p_this->a_accum,
                p_this->i_accum_len);
            cv_json_set_type(p_value, cv_json_type_string);
            cv_json_set_string(p_value, &o_string);
            cv_array_cleanup(&o_string);
            parser_push(p_this, p_value);
        }
        p_this->b_string_started = 0;
    }
}

/*
 *
 */

static void parser_flush_number(parser * p_this) {
    if (p_this->e_number_type) {
        cv_json * p_value = cv_json_create();
        if (p_value) {
            double i_value = 0.0;
            {
                cv_array o_accum;
                cv_array_0 o_accum_0;
                cv_array_init_vector(&o_accum,
                    p_this->a_accum,
                    p_this->i_accum_len);
                cv_array_0_init(&o_accum_0, &o_accum, "json_number", 0);
                {
                    char const * p_accum_0 = cv_array_0_get(&o_accum_0);
                    if (p_accum_0) {
                        sscanf(p_accum_0, "%lf", &i_value);
                    }
                }
                cv_array_0_cleanup(&o_accum_0);
                cv_array_cleanup(&o_accum);
            }
            cv_json_set_type(p_value, cv_json_type_number);
            cv_json_set_number(p_value, i_value);
            parser_push(p_this, p_value);
        }
        p_this->e_number_type = 0;
    }
}

/*
 *
 */

static void parser_flush_word(parser * p_this) {
    (void)p_this;
    if (p_this->b_word_started) {
        cv_json * p_value = cv_json_create();
        if (p_value) {
            static unsigned char const a_ref_null[] = {
                'n', 'u', 'l', 'l'
            };
            static unsigned char const a_ref_false[] = {
                'f', 'a', 'l', 's', 'e'
            };
            static unsigned char const a_ref_true[] = {
                't', 'r', 'u', 'e'
            };
            static cv_array const g_ref_null =
                cv_array_initializer_(a_ref_null,
                    a_ref_null + sizeof(a_ref_null));
            static cv_array const g_ref_false =
                cv_array_initializer_(a_ref_false,
                    a_ref_false + sizeof(a_ref_false));
            static cv_array const g_ref_true =
                cv_array_initializer_(a_ref_true,
                    a_ref_true + sizeof(a_ref_true));
            cv_bool b_valid = cv_false;
            cv_array o_accum;
            cv_array_init_vector(&o_accum,
                p_this->a_accum,
                p_this->i_accum_len);
            if (cv_array_compare(&o_accum, &g_ref_null)) {
                cv_json_set_type(p_value, cv_json_type_null);
                b_valid = cv_true;
            } else if (cv_array_compare(&o_accum, &g_ref_false)) {
                cv_json_set_type(p_value, cv_json_type_false);
                b_valid = cv_true;
            } else if (cv_array_compare(&o_accum, &g_ref_true)) {
                cv_json_set_type(p_value, cv_json_type_true);
                b_valid = cv_true;
            }
            if (b_valid) {
                parser_push(p_this, p_value);
            } else {
                cv_json_destroy(p_value);
                p_value = 0;
                p_this->e_state = state_idle;
            }
            cv_array_cleanup(&o_accum);
        }
        p_this->b_word_started = 0;
    }
}

/*
 *
 */

static void parser_flush(parser * p_this) {
    if (p_this->i_accum_len) {
        /* check for label */
        /* if parent is object and label is required */
        cv_bool b_is_object = cv_false;
        if (p_this->i_stack_len) {
            unsigned const e_type = cv_json_get_type(
                p_this->a_stack[p_this->i_stack_len - 1]);
            if (cv_json_type_object == e_type) {
                b_is_object = cv_true;
            }
        }
        if (b_is_object && (0 == p_this->i_label_len)) {
            cv_runtime_memcpy( p_this->a_label, p_this->a_accum,
                p_this->i_accum_len);
            p_this->i_label_len = p_this->i_accum_len;
            p_this->e_state = state_idle;
            p_this->b_string_started = 0;
            p_this->b_word_started = 0;
            p_this->e_number_type = 0;
        } else {
            parser_flush_number(p_this);
            parser_flush_string(p_this);
            parser_flush_word(p_this);
        }
        p_this->i_accum_len = 0;
    }
}

/*
 *
 */

static cv_bool parser_step(parser * p_this,
    unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    if (state_idle == p_this->e_state) {
        if (' ' == c_token) {
        } else if ('\t' == c_token) {
        } else if ('\r' == c_token) {
        } else if ('\n' == c_token) {
        } else if (',' == c_token) {
        } else if (':' == c_token) {
        } else if ('\"' == c_token) {
            p_this->b_string_started = 1;
            p_this->e_state = state_string_normal;
        } else if ('-' == c_token) {
            /* process sign */
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_sign;
            p_this->e_number_type = 1;
        } else if ('+' == c_token) {
            /* process sign */
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_sign;
            p_this->e_number_type = 1;
        } else if ('0' == c_token) {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_zero;
            p_this->e_number_type = 1;
        } else if (('1' <= c_token) && ('9' >= c_token)) {
            p_this->e_state = state_number_dec_digit;
            p_this->e_number_type = 1;
            b_repeat = cv_true;
        } else if ('.' == c_token) {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_frac_digit;
            p_this->e_number_type = 1;
        } else if ('[' == c_token) {
            if (p_this->i_stack_len < parser_stack_max) {
                /* create an array node */
                cv_json * p_value = cv_json_create();
                if (p_value) {
                    cv_json_set_type(p_value, cv_json_type_array);

                    /* add to stack of nodes */
                    p_this->a_stack[p_this->i_stack_len] = p_value;
                    p_this->i_stack_len ++;
                }
            }
            p_this->e_state = state_idle;
        } else if ('{' == c_token) {
            if (p_this->i_stack_len < parser_stack_max) {
                /* create an object node */
                cv_json * p_value = cv_json_create();
                if (p_value) {
                    cv_json_set_type(p_value, cv_json_type_object);
                    /* add to stack of nodes */
                    p_this->a_stack[p_this->i_stack_len] = p_value;
                    p_this->i_stack_len ++;
                }
            }
            p_this->e_state = state_idle;
        } else if (']' == c_token) {
            /* complete this array */
            if (0 == p_this->i_stack_len) {
                /* Error? */
                p_this->e_state = state_end;
            } else if (1 == p_this->i_stack_len) {
                /* do a final */
                p_this->p_final = p_this->a_stack[0u];
                p_this->a_stack[0u] = 0;
                p_this->i_stack_len = 0;
                p_this->e_state = state_idle;
            } else {
                /* push this to parent */
                p_this->e_state = state_idle;
            }
        } else if ('}' == c_token) {
            /* complete this object */
            if (0 == p_this->i_stack_len) {
                /* Error? */
                p_this->e_state = state_end;
            } else if (1 == p_this->i_stack_len) {
                /* do a final */
                p_this->p_final = p_this->a_stack[0u];
                p_this->a_stack[0u] = 0;
                p_this->i_stack_len = 0;
                p_this->e_state = state_idle;
            } else {
                /* push this to parent */
                p_this->e_state = state_idle;
            }
        } else if ((('a' <= c_token) && ('z' >= c_token))
            || (('A' <= c_token) && ('Z' >= c_token))
            || ('_' == c_token)) {
            p_this->e_state = state_word;
            b_repeat = cv_true;
        } else {
            /* could be null, true, false or error */
        }
    } else if (state_string_normal == p_this->e_state) {
        if ('\"' == c_token) {
            parser_flush(p_this);
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
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_zero;
        } else if (('1' <= c_token) && ('9' >= c_token)) {
            p_this->e_state = state_number_dec_digit;
            b_repeat = cv_true;
        } else {
            /* error ? */
            p_this->e_state = state_idle;
            b_repeat = cv_true;
            parser_flush(p_this);
        }
    } else if (state_number_zero == p_this->e_state) {
        if (('x' == c_token) ||
            ('X' == c_token)) {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_hex_digit;
        } else if (('0' <= c_token) && ('9' >= c_token)) {
            p_this->e_state = state_number_dec_digit;
            b_repeat = cv_true;
        } else if ('.' == c_token) {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_frac_digit;
        } else {
            /* error ? */
            p_this->e_state = state_idle;
            b_repeat = cv_true;
            parser_flush(p_this);
        }
    } else if (state_number_dec_digit == p_this->e_state) {
        if (('0' <= c_token) && ('9' >= c_token)) {
            /* process the digit */
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_dec_digit;
        } else if ('.' == c_token) {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_frac_digit;
        } else if (('e' == c_token) ||
            ('E' == c_token)) {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_exp_prefix;
        } else {
            /* flush this number */
            /* error ? */
            p_this->e_state = state_idle;
            b_repeat = cv_true;
            parser_flush(p_this);
        }
    } else if (state_number_frac_digit == p_this->e_state) {
        if (('0' <= c_token) && ('9' >= c_token)) {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_frac_digit;
        } else if (('e' == c_token) ||
            ('E' == c_token)) {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_exp_prefix;
        } else {
            /* error ? */
            p_this->e_state = state_idle;
            b_repeat = cv_true;
            parser_flush(p_this);
        }
    } else if (state_number_exp_prefix == p_this->e_state) {
        if ('-' == c_token) {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_exp_digit;
        } else if ('+' == c_token) {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_exp_digit;
        } else if (('0' <= c_token) && ('9' >= c_token)) {
            p_this->e_state = state_number_exp_digit;
            b_repeat = cv_true;
        } else {
            /* error ? */
            p_this->e_state = state_idle;
            b_repeat = cv_true;
            parser_flush(p_this);
        }
    } else if (state_number_exp_digit == p_this->e_state) {
        if (('0' <= c_token) && ('9' >= c_token)) {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_exp_digit;
        } else {
            /* error ? */
            p_this->e_state = state_idle;
            b_repeat = cv_true;
            parser_flush(p_this);
        }
    } else if (state_number_hex_digit == p_this->e_state) {
        if (('0' <= c_token) && ('9' >= c_token)) {
            /* process digit */
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_hex_digit;
        } else if (('a' <= c_token) && ('f' >= c_token)) {
            /* process digit */
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_hex_digit;
        } else if (('A' <= c_token) && ('F' >= c_token)) {
            /* process digit */
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_number_hex_digit;
        } else {
            parser_flush(p_this);
            /* error ? */
            p_this->e_state = state_idle;
            b_repeat = cv_true;
        }
    } else if (state_word == p_this->e_state) {
        if ((('a' <= c_token) && ('z' >= c_token))
            || (('A' <= c_token) && ('Z' >= c_token))
            || (('0' <= c_token) && ('9' >= c_token))
            || ('_' == c_token)) {
            p_this->b_word_started = 1;
            p_this->e_state = state_word;
            parser_accumulate(p_this, c_token);
        } else {
            p_this->e_state = state_idle;
            b_repeat = cv_true;
            parser_flush(p_this);
        }
    } else {
        /* error ? */
    }
    return b_repeat;
}

/*
 *
 */

static void parser_walk(parser * p_this,
    unsigned char c_token) {
    while (parser_step(p_this, c_token)) {
    }
}

/*
 *
 */

static void parser_run(parser * p_this,
    cv_array_it * p_document) {
    unsigned char c_token = 0;
    while (cv_array_it_read_next_char(p_document, &c_token)) {
        parser_walk(p_this, c_token);
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
    p_result = o_parser.p_final;
    o_parser.p_final = 0;
    parser_cleanup(&o_parser);
    return p_result;
}

