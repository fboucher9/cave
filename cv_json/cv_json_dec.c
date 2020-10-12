/* See LICENSE for license details */

/*
 *
 */

#include <cv_json/cv_json_dec.h>
#include <cv_json/cv_json.h>
#include <cv_json/cv_json_type.h>
#include <cv_algo/cv_array_it.h>
#include <cv_algo/cv_array_0.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_algo/cv_array_heap.h>
#include <cv_algo/cv_chunk_root.h>
#include <cv_misc/cv_limits.h>
#include <cv_debug/cv_debug.h>

/*
 *
 */

enum parser_state {
    state_idle = 0,
    state_string_normal,
    state_string_escape,
    state_string_unicode,
    state_number_dec_digit,
    state_number_frac_digit,
    state_number_exp_digit,
    state_word,
    state_flush,
    state_end
};

/*
 *
 */

enum parser_const {
    parser_stack_max = 64
};

/*
 *
 */

typedef struct parser_number_section {
    union parser_number_accum {
        double f_value;
        cv_ull ll_padding[(sizeof(double) + sizeof(cv_ull) - 1) /
            sizeof(cv_ull)];
    } u;
    /* -- */
    cv_ull ll_digits;
    /* -- */
    unsigned long i_digit_count;
    unsigned long l_padding[1u];
    /* -- */
    cv_bool b_negative;
    char c_padding[7u];
} parser_number_section;

/*
 *
 */

static void parser_number_section_reset(
    parser_number_section * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    p_this->b_negative = cv_false;
    p_this->i_digit_count = 0;
    p_this->ll_digits = 0;
    p_this->u.f_value = 0.0;
}

/*
 *
 */

static void parser_number_section_add(
    parser_number_section * p_this,
    unsigned int i_base, unsigned int i_digit) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(((10u == i_base) || (16u == i_base))
        && (i_digit < i_base), cv_debug_code_invalid_parameter);
    p_this->u.f_value =
        (p_this->u.f_value * i_base) + (i_digit % i_base);
    p_this->ll_digits =
        (p_this->ll_digits * i_base) + (i_digit % i_base);
    p_this->i_digit_count ++;
}

/*
 *
 */

static void parser_number_section_add_decimal(
    parser_number_section * p_this, unsigned char c_token) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(('0' <= c_token) && ('9' >= c_token),
        cv_debug_code_invalid_parameter);
    {
        unsigned const i_token = c_token;
        parser_number_section_add(p_this, 10, i_token - '0');
    }
}

/*
 *
 */

static cv_bool parser_number_section_step_decimal(
    parser_number_section * p_this, unsigned char c_token) {
    cv_bool b_result = cv_true;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if ('-' == c_token) {
        p_this->b_negative = cv_true;
    } else if ('+' == c_token) {
        p_this->b_negative = cv_false;
    } else if (('0' <= c_token) && ('9' >= c_token)) {
        parser_number_section_add_decimal(p_this, c_token);
    } else {
        b_result = cv_false;
    }
    return b_result;
}

/*
 *
 */

static cv_bool parser_is_hex(unsigned int c_token) {
    return (('0' <= c_token) && ('9' >= c_token))
        || (('a' <= c_token) && ('f' >= c_token))
        || (('A' <= c_token) && ('F' >= c_token));
}

/*
 *
 */

static unsigned parser_hex_digit(unsigned int c_token) {
    unsigned i_digit = 0;
    if (('0' <= c_token) && ('9' >= c_token)) {
        i_digit = c_token - '0';
    } else if (('a' <= c_token) && ('f' >= c_token)) {
        i_digit = c_token - 'a' + 10;
    } else if (('A' <= c_token) && ('F' >= c_token)) {
        i_digit = c_token - 'A' + 10;
    } else {
        cv_debug_break_("invalid hexadecimal digit");
    }
    return i_digit;
}

/*
 *
 */

static void parser_number_section_add_hexadecimal(
    parser_number_section * p_this, unsigned char c_token) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(parser_is_hex(c_token),
        cv_debug_code_invalid_parameter);
    {
        unsigned const i_digit = parser_hex_digit(c_token);
        parser_number_section_add(p_this, 16, i_digit);
    }
}

/*
 *
 */

typedef struct parser {
    parser_number_section o_dec_section;
    /* -- */
    parser_number_section o_frac_section;
    /* -- */
    parser_number_section o_exp_section;
    /* -- */
    parser_number_section o_unicode_section;
    /* -- */
    unsigned long e_state;
    unsigned long i_stack_len;
    /* -- */
    cv_bool b_number_started;
    cv_bool b_word_started;
    cv_bool b_string_started;
    cv_bool b_accum_cache_initialized;
    cv_bool b_label_cache_initialized;
    char c_padding[3u];
    /* -- */
    cv_json * p_value;
    /* -- */
    cv_json * a_stack[parser_stack_max];
    /* -- */
    cv_chunk_root o_chunk_root;
    /* -- */
    cv_array_heap o_accum_cache;
    /* -- */
    cv_array_heap o_label_cache;
} parser;

/*
 *
 */

static void parser_reset_number_state(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    p_this->b_number_started = cv_false;
    parser_number_section_reset(&p_this->o_dec_section);
    parser_number_section_reset(&p_this->o_frac_section);
    parser_number_section_reset(&p_this->o_exp_section);
}

/*
 *
 */

static void parser_label_cache_free(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->b_label_cache_initialized) {
        cv_array_heap_cleanup(&p_this->o_label_cache);
        p_this->b_label_cache_initialized = cv_false;
    }
}

/*
 *
 */

static void parser_accum_cache_free(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->b_accum_cache_initialized) {
        cv_array_heap_cleanup(&p_this->o_accum_cache);
        p_this->b_accum_cache_initialized = cv_false;
    }
}

/*
 *
 */

static void parser_accumulate(parser * p_this, unsigned char c_token) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_chunk_root_write_char(&p_this->o_chunk_root, c_token);
}

/*
 *
 */

static void parser_save_label(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (!p_this->b_label_cache_initialized) {
        if (cv_array_heap_init_move(&p_this->o_label_cache,
                &p_this->o_accum_cache)) {
            p_this->b_label_cache_initialized = cv_true;
        } /* else ? */
    }
}

/*
 *
 */

static void parser_apply_label(parser * p_this, cv_json * p_value) {
    cv_debug_assert_(p_this && p_value, cv_debug_code_null_ptr);
    if (p_this->b_label_cache_initialized) {
        cv_json_move_label(p_value, &p_this->o_label_cache);
        parser_label_cache_free(p_this);
    }
}

/*
 *
 */

static void parser_join(parser * p_this, cv_json * p_value) {
    cv_debug_assert_(p_this && p_value, cv_debug_code_null_ptr);
    if (0 == p_this->i_stack_len) {
        if (p_value == p_this->p_value) {
        } else {
            cv_json_move(p_this->p_value, p_value);
            cv_json_destroy(p_value);
        }
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

static void parser_push(parser * p_this, cv_json * p_value) {
    cv_debug_assert_(p_this && p_value, cv_debug_code_null_ptr);
    p_this->e_state = state_idle;
    if (p_this->i_stack_len < parser_stack_max) {
        p_this->a_stack[p_this->i_stack_len] = p_value;
        p_this->i_stack_len ++;
    } else {
        if (p_value != p_this->p_value) {
            cv_json_destroy(p_value);
        }
    }
}

/*
 *
 */

static void parser_pop(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (0 < p_this->i_stack_len) {
        parser_join( p_this, p_this->a_stack[--p_this->i_stack_len]);
    } else {
        p_this->e_state = state_end;
    }
}

/*
 *
 */

static cv_bool parser_is_object(parser * p_this) {
    cv_bool b_is_object = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (0 < p_this->i_stack_len) {
        unsigned const e_type = cv_json_get_type(
            p_this->a_stack[p_this->i_stack_len - 1]);
        if (cv_json_type_object == e_type) {
            b_is_object = cv_true;
        }
    }
    return b_is_object;
}

/*
 *
 */

static void parser_apply_string(parser * p_this, cv_json * p_value) {
    cv_debug_assert_(p_this && p_value, cv_debug_code_null_ptr);
    if (p_this->b_accum_cache_initialized) {
        cv_json_move_string(p_value, &p_this->o_accum_cache);
    }
}

/*
 *
 */

static cv_json * parser_alloc_node(parser * p_this, unsigned e_type) {
    cv_json * p_value = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (0 == p_this->i_stack_len) {
        p_value = p_this->p_value;
    } else {
        p_value = cv_json_create();
    }
    if (p_value) {
        cv_json_set_type(p_value, e_type);
        parser_apply_label(p_this, p_value);
        if ((cv_json_type_array == e_type) ||
            (cv_json_type_object == e_type)) {
            parser_push(p_this, p_value);
        } else {
            parser_join(p_this, p_value);
        }
    } else {
        p_this->e_state = state_idle;
    }
    return p_value;
}

/*
 *
 */

static void parser_flush_string(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    /* flush the accumulated string */
    /* create a string node */
    if (p_this->b_string_started) {
        cv_json * p_value = parser_alloc_node(p_this, cv_json_type_string);
        if (p_value) {
            parser_apply_string(p_this, p_value);
        }
    }
}

/*
 *
 */

static void parser_flush_number(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->b_number_started) {
        cv_json * p_value = parser_alloc_node(p_this, cv_json_type_number);
        if (p_value) {
            double i_value = 0.0;
            i_value = p_this->o_dec_section.u.f_value;
            /* Divide by ten for each fraction */
            {
                double i_fraction = p_this->o_frac_section.u.f_value;
                unsigned long i_digit_iterator =
                    p_this->o_frac_section.i_digit_count;
                while (i_digit_iterator --) {
                    i_fraction = i_fraction / 10.0;
                }
                i_value += i_fraction;
            }
            if (p_this->o_dec_section.b_negative) {
                i_value = -i_value;
            }
            /* Multiply by ten for each exponent */
            {
                signed long i_exp_iterator =
                    p_this->o_exp_section.ll_digits & cv_signed_long_max_;
                if (p_this->o_exp_section.b_negative) {
                    while (i_exp_iterator --) {
                        i_value = i_value / 10.0;
                    }
                } else {
                    while (i_exp_iterator --) {
                        i_value = i_value * 10.0;
                    }
                }
            }
            cv_json_set_number(p_value, i_value);
        }
    }
}

/*
 *
 */

static unsigned parser_detect_word_type(parser * p_this) {
    static unsigned char const a_ref_null[] = {
        'n', 'u', 'l', 'l' };
    static unsigned char const a_ref_false[] = {
        'f', 'a', 'l', 's', 'e' };
    static unsigned char const a_ref_true[] = {
        't', 'r', 'u', 'e' };
    static cv_array const g_ref_null = cv_array_initializer_(a_ref_null,
            a_ref_null + sizeof(a_ref_null));
    static cv_array const g_ref_false = cv_array_initializer_(a_ref_false,
            a_ref_false + sizeof(a_ref_false));
    static cv_array const g_ref_true = cv_array_initializer_(a_ref_true,
            a_ref_true + sizeof(a_ref_true));
    unsigned e_word_type = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (cv_array_compare(
            &p_this->o_accum_cache.o_array, &g_ref_null)) {
        e_word_type = cv_json_type_null;
    } else if (cv_array_compare(
            &p_this->o_accum_cache.o_array, &g_ref_false)) {
        e_word_type = cv_json_type_false;
    } else if (cv_array_compare(
            &p_this->o_accum_cache.o_array, &g_ref_true)) {
        e_word_type = cv_json_type_true;
    }
    return e_word_type;
}

/*
 *
 */

static void parser_flush_word(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->b_word_started) {
        unsigned const e_word_type = parser_detect_word_type(p_this);
        if (0 != e_word_type) {
            parser_alloc_node(p_this, e_word_type);
        } else {
            /* Insert a string */
            cv_json * p_value = parser_alloc_node(p_this,
                cv_json_type_string);
            if (p_value) {
                parser_apply_string(p_this, p_value);
            }
        }
    }
}

/*
 *
 */

static void parser_accum_cache_alloc(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    parser_accum_cache_free(p_this);
    if (!p_this->b_accum_cache_initialized) {
        cv_uptr const i_accum_len = cv_chunk_root_len(&p_this->o_chunk_root);
        if (cv_array_heap_init(&p_this->o_accum_cache, i_accum_len)) {
            if (i_accum_len) {
                cv_array_it o_array_it;
                cv_array_it_init(&o_array_it, &p_this->o_accum_cache.o_array);
                cv_chunk_root_read(&p_this->o_chunk_root, &o_array_it);
                cv_array_it_cleanup(&o_array_it);
            }
            p_this->b_accum_cache_initialized = cv_true;
        }
    }
}

/*
 *
 */

static void parser_flush(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    p_this->e_state = state_idle;
    parser_accum_cache_alloc(p_this);
    if (p_this->b_accum_cache_initialized) {
        /* check for label */
        /* if parent is object and label is required */
        cv_bool const b_is_object = parser_is_object(p_this);
        if (b_is_object && !p_this->b_label_cache_initialized) {
            parser_save_label(p_this);
        } else {
            parser_flush_number(p_this);
            parser_flush_string(p_this);
            parser_flush_word(p_this);
        }
        p_this->b_string_started = cv_false;
        p_this->b_word_started = cv_false;
        parser_reset_number_state(p_this);
        parser_accum_cache_free(p_this);
    }
    cv_chunk_root_empty(&p_this->o_chunk_root);
}

/*
 *
 */

static cv_bool parser_step_idle(parser * p_this,
    unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if ('\"' == c_token) {
        p_this->b_string_started = cv_true;
        p_this->e_state = state_string_normal;
    } else if ((('0' <= c_token) && ('9' >= c_token)) ||
        ('.' == c_token) || ('-' == c_token) || ('+' == c_token)) {
        p_this->e_state = state_number_dec_digit;
        b_repeat = cv_true;
    } else if (('[' == c_token) || ('{' == c_token)) {
        /* create an array node */
        parser_alloc_node(p_this,
            ('[' == c_token) ? cv_json_type_array : cv_json_type_object);
    } else if ((']' == c_token) || ('}' == c_token)) {
        /* Flush of label */
        if (p_this->b_label_cache_initialized) {
            parser_alloc_node(p_this, cv_json_type_null);
        }
        /* do a final */
        /* push this to parent */
        parser_pop(p_this);
    } else if ((('a' <= c_token) && ('z' >= c_token))
        || (('A' <= c_token) && ('Z' >= c_token))
        || ('_' == c_token) || ('$' == c_token)) {
        /* could be null, true, false or error */
        p_this->e_state = state_word;
        b_repeat = cv_true;
    } else {
    }
    return b_repeat;
}

/*
 *
 */

static cv_bool parser_step_string(parser * p_this, unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (state_string_normal == p_this->e_state) {
        if ('\"' == c_token) {
            p_this->e_state = state_flush;
        } else if ('\\' == c_token) {
            p_this->e_state = state_string_escape;
        } else {
            /* store token into chunk list... */
            parser_accumulate(p_this, c_token);
        }
    } else if (state_string_escape == p_this->e_state) {
        if (('u' == c_token) ||
            ('U' == c_token)) {
            parser_number_section_reset(&p_this->o_unicode_section);
            p_this->e_state = state_string_unicode;
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
    } else if (state_string_unicode == p_this->e_state) {
        /* store this character into unicode accumulator */
        cv_bool b_flush_hex = cv_false;
        if (parser_is_hex(c_token)) {
            parser_number_section_add_hexadecimal(
                &p_this->o_unicode_section, c_token);
            if (p_this->o_unicode_section.i_digit_count >= 4u) {
                b_flush_hex = cv_true;
            }
        } else {
            b_flush_hex = cv_true;
            b_repeat = cv_true;
        }
        if (b_flush_hex) {
            /* store this character into unicode accumulator */
            parser_accumulate(p_this,
                p_this->o_unicode_section.ll_digits & 0xffu);
            parser_number_section_reset(&p_this->o_unicode_section);
            p_this->e_state = state_string_normal;
        }
    }
    return b_repeat;
}

/*
 *
 */

static cv_bool parser_step_number(parser * p_this, unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (state_number_dec_digit == p_this->e_state) {
        if (parser_number_section_step_decimal(
                &p_this->o_dec_section, c_token)) {
        } else if ('.' == c_token) {
            p_this->e_state = state_number_frac_digit;
        } else if (('e' == c_token) || ('E' == c_token)) {
            p_this->e_state = state_number_exp_digit;
        } else {
            /* flush this number */
            /* error ? */
            p_this->e_state = state_flush;
            b_repeat = cv_true;
        }
    } else if (state_number_frac_digit == p_this->e_state) {
        if (parser_number_section_step_decimal(
                &p_this->o_frac_section, c_token)) {
        } else if (('e' == c_token) || ('E' == c_token)) {
            p_this->e_state = state_number_exp_digit;
        } else {
            /* error ? */
            p_this->e_state = state_flush;
            b_repeat = cv_true;
        }
    } else if (state_number_exp_digit == p_this->e_state) {
        if (parser_number_section_step_decimal(
                &p_this->o_exp_section, c_token)) {
        } else {
            /* error ? */
            p_this->e_state = state_flush;
            b_repeat = cv_true;
        }
    }
    if (!b_repeat) {
        parser_accumulate(p_this, c_token);
        p_this->b_number_started = cv_true;
    }
    return b_repeat;
}

/*
 *
 */

static cv_bool parser_step_word(parser * p_this, unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if ((('a' <= c_token) && ('z' >= c_token))
        || (('A' <= c_token) && ('Z' >= c_token))
        || (('0' <= c_token) && ('9' >= c_token))
        || ('_' == c_token) || ('$' == c_token)) {
        p_this->b_word_started = cv_true;
        parser_accumulate(p_this, c_token);
    } else {
        p_this->e_state = state_flush;
        b_repeat = cv_true;
    }
    return b_repeat;
}

/*
 *
 */

static cv_bool parser_step(parser * p_this, unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (state_idle == p_this->e_state) {
        b_repeat = parser_step_idle(p_this, c_token);
    } else if ((state_string_normal <= p_this->e_state) &&
        (state_string_unicode >= p_this->e_state)) {
        b_repeat = parser_step_string(p_this, c_token);
    } else if ((state_number_dec_digit <= p_this->e_state) &&
        (state_number_exp_digit >= p_this->e_state)) {
        b_repeat = parser_step_number(p_this, c_token);
    } else if (state_word == p_this->e_state) {
        b_repeat = parser_step_word(p_this, c_token);
    } else if (state_flush == p_this->e_state) {
        parser_flush(p_this);
        b_repeat = cv_true;
    } else if (state_end == p_this->e_state) {
    } else {
        /* error ? */
        cv_debug_break_("invalid state");
    }
    return b_repeat;
}

/*
 *
 */

static void parser_walk(parser * p_this, unsigned char c_token) {
    while (parser_step(p_this, c_token)) {
    }
}

/*
 *
 */

static void parser_run(parser * p_this, cv_array_it * p_document) {
    cv_debug_assert_(p_this && p_document, cv_debug_code_null_ptr);
    {
        unsigned char c_token = 0;
        while ((state_end != p_this->e_state) &&
            cv_array_it_read_next_char(p_document, &c_token)) {
            parser_walk(p_this, c_token);
        }
    }
}

/*
 *
 */

static void parser_init(parser * p_this, cv_json * p_value) {
    cv_debug_assert_(p_this && p_value, cv_debug_code_null_ptr);
    p_this->e_state = state_idle;
    p_this->i_stack_len = 0;
    p_this->b_word_started = cv_false;
    p_this->b_string_started = cv_false;
    p_this->b_accum_cache_initialized = cv_false;
    p_this->b_label_cache_initialized = cv_false;
    p_this->p_value = p_value;
    cv_chunk_root_init(&p_this->o_chunk_root);
    parser_number_section_reset(&p_this->o_unicode_section);
    parser_reset_number_state(p_this);
}

/*
 *
 */

static void parser_cleanup(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    /* Flush of caches */
    parser_flush(p_this);
    /* Free the stack */
    while (p_this->i_stack_len) {
        parser_pop(p_this);
    }
    p_this->p_value = 0;
    parser_label_cache_free(p_this);
    parser_accum_cache_free(p_this);
    cv_chunk_root_cleanup(&p_this->o_chunk_root);
}

/*
 *
 */

void cv_json_dec_array_it( cv_array_it * p_document, cv_json * p_value ) {
    cv_debug_assert_(p_document && p_value, cv_debug_code_null_ptr);
    {
        parser o_parser;
        parser_init(&o_parser, p_value);
        parser_run(&o_parser, p_document);
        parser_cleanup(&o_parser);
    }
}

/*
 *
 */

void cv_json_dec_array( cv_array const * p_document, cv_json * p_value ) {
    cv_debug_assert_(p_document && p_value, cv_debug_code_null_ptr);
    {
        cv_array_it o_array_it;
        cv_array_it_init(&o_array_it, p_document);
        cv_json_dec_array_it(&o_array_it, p_value);
        cv_array_it_cleanup(&o_array_it);
    }
}
