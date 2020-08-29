/* See LICENSE for license details */

/*
 *
 */

#include <cv_json/cv_json_dec.h>
#include <cv_json/cv_json.h>

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
    state_end
};

/*
 *
 */

typedef struct parser {
    unsigned e_state;
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

static void parser_step(parser * p_this,
    unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    do {
        if (state_idle == p_this->e_state) {
            if (' ' == c_token) {
            } else if ('\t' == c_token) {
            } else if ('\r' == c_token) {
            } else if ('\n' == c_token) {
            } else if (',' == c_token) {
            } else if (':' == c_token) {
            } else if ('\"' == c_token) {
                p_this->e_state = state_string_normal;
            } else {
            }
        } else if (state_string_normal == p_this->e_state) {
            if ('\"' == c_token) {
                p_this->e_state = state_string_after;
            } else if ('\\' == c_token) {
                p_this->e_state = state_string_escape;
            } else {
                /* store token into chunk list... */
            }
        } else if (state_string_escape == p_this->e_state) {
            if ('u' == c_token) {
                p_this->e_state = state_string_unicode1;
            } else if ('t' == c_token) {
            } else if ('b' == c_token) {
            } else if ('r' == c_token) {
            } else if ('n' == c_token) {
            } else {
            }
        } else if (state_string_after == p_this->e_state) {
            if (' ' == c_token) {
            } else if ('\t' == c_token) {
            } else if ('\r' == c_token) {
            } else if ('\n' == c_token) {
            } else if (':' == c_token) {
            } else {
                /* create a value and store into top of stack */
                /* if stack is empty then this is only value */
                p_this->e_state = state_idle;
                b_repeat = cv_true;
            }
        } else {
        }
    } while (b_repeat);
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
}

/*
 *
 */

cv_json * cv_json_dec( cv_array_it * p_document ) {
    cv_json * p_result = 0;
    parser o_parser = {0};
    parser_init(&o_parser);
    parser_run(&o_parser, p_document);
    parser_cleanup(&o_parser);
    return p_result;
}

