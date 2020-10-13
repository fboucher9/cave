/* See LICENSE for license details */

/*
 *  cv_json_dec.c
 *
 *  json decoder.  Provide input document and extract a single json value.
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
 *  Enumaration: parser_state
 *
 *  States for json decoder.
 */

enum parser_state {

    /* Waiting to find a value */
    state_idle = 0,

    /* Waiting for normal characters to insert into quoted string */
    state_string_normal,

    /* Waiting for second character of escape */
    state_string_escape,

    /* Waiting for hexadecimal digits of unicode character */
    state_string_unicode,

    /* Waiting for decimal digits of mantissa */
    state_number_dec_digit,

    /* Waiting for decimal digits of fraction */
    state_number_frac_digit,

    /* Waiting for decimal digits of exponent */
    state_number_exp_digit,

    /* Waiting for identifier characters to insert into word */
    state_word,

    /* Flush of accumulated data */
    state_flush,

    /* Json value is complete, decoder may stop */
    state_end
};

/*
 *  Enumaration: parser_const
 *
 *  Miscellaneous constants reserved for use by json decoder implementation.
 */

enum parser_const {

    /* Maximum number of values in stack */
    parser_stack_max = 64,

    /* Numeric base for decimal */
    parser_base_decimal = 10,

    /* Numeric base for hexadecimal */
    parser_base_hexadecimal = 16,

    /* Maximum number of hexadecimal digits for unicode character */
    parser_unicode_max = 4,

    /* Minimum character of decimal digit */
    parser_token_0 = '0',

    /* Maximum character of decimal digit */
    parser_token_9 = '9',

    /* Minimum character of hexadecimal digit or alphabet */
    parser_token_a = 'a',

    /* Minimum character of hexadecimal digit or alphabet */
    parser_token_A = 'A',

    /* Exponent prefix */
    parser_token_e = 'e',

    /* Exponent prefix */
    parser_token_E = 'E',

    /* Maximum character of hexadecimal digit */
    parser_token_f = 'f',

    /* Maximum character of hexadecimal digit */
    parser_token_F = 'F',

    /* Prefix of unicode character */
    parser_token_u = 'u',

    /* Prefix of unicode character */
    parser_token_U = 'U',

    /* Maximum character of alphabet */
    parser_token_z = 'z',

    /* Maximum character of alphabet */
    parser_token_Z = 'Z',

    /* Period used for number */
    parser_token_period = '.',

    /* Minus used for number */
    parser_token_minus = '-',

    /* Plus used for number */
    parser_token_plus = '+',

    /* Underscore used for words */
    parser_token_underscore = '_',

    /* Dollar sign used for words */
    parser_token_dollar = '$',

    /* Mark begin and end of quoted string */
    parser_token_string = '\"',

    /* Escape character within quoted strings */
    parser_token_backslash = '\\',

    /* Escape code for tab */
    parser_escape_tab = 't',

    /* Escape code for bell */
    parser_escape_bell = 'b',

    /* Escape code for carriage return */
    parser_escape_cr = 'r',

    /* Escape code for line feed */
    parser_escape_lf = 'n',

    /* Raw literal for tab */
    parser_literal_tab = '\t',

    /* Raw literal for bell */
    parser_literal_bell = '\b',

    /* Raw literal for carriage return */
    parser_literal_cr = '\r',

    /* Raw literal for line feed */
    parser_literal_lf = '\n',

    /* Mark begin of array */
    parser_token_array_begin = '[',

    /* Mark end of array */
    parser_token_array_end = ']',

    /* Mark begin of object */
    parser_token_object_begin = '{',

    /* Mark end of object */
    parser_token_object_end = '}'
};

/*
 *
 */

static cv_bool parser_is_dec(unsigned int c_token) {
    return ((parser_token_0 <= c_token) &&
        (parser_token_9 >= c_token));
}

/*
 *
 */

static cv_bool parser_is_hex(unsigned int c_token) {
    return parser_is_dec(c_token)
        || ((parser_token_a <= c_token) && (parser_token_f >= c_token))
        || ((parser_token_A <= c_token) && (parser_token_F >= c_token));
}

/*
 *
 */

static cv_bool parser_is_identifier(unsigned int c_token) {
    return parser_is_dec(c_token)
        || ((parser_token_a <= c_token) && (parser_token_z >= c_token))
        || ((parser_token_A <= c_token) && (parser_token_Z >= c_token))
        || (parser_token_underscore == c_token)
        || (parser_token_dollar == c_token);
}

/*
 *
 */

static unsigned parser_hex_digit(unsigned int c_token) {
    unsigned i_digit = 0;
    if (parser_is_dec(c_token)) {
        i_digit = c_token - parser_token_0;
    } else if ((parser_token_a <= c_token) && (parser_token_f >= c_token)) {
        i_digit = c_token - parser_token_a + parser_base_decimal;
    } else if ((parser_token_A <= c_token) && (parser_token_F >= c_token)) {
        i_digit = c_token - parser_token_A + parser_base_decimal;
    } else {
        cv_debug_break_("invalid hexadecimal digit");
    }
    return i_digit;
}

/*
 *
 */

typedef struct number_accum {
    union number_value {
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
} number_accum;

/*
 *
 */

static void number_accum_reset(
    number_accum * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    p_this->b_negative = cv_false;
    p_this->i_digit_count = 0;
    p_this->ll_digits = 0;
    p_this->u.f_value = 0.0;
}

/*
 *
 */

static void number_accum_add(
    number_accum * p_this,
    unsigned int i_base, unsigned int i_digit) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(((parser_base_decimal == i_base)
            || (parser_base_hexadecimal == i_base))
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

static void number_accum_add_decimal(
    number_accum * p_this, unsigned char c_token) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(parser_is_dec(c_token),
        cv_debug_code_invalid_parameter);
    {
        unsigned const i_token = c_token;
        number_accum_add(p_this, parser_base_decimal,
            i_token - parser_token_0);
    }
}

/*
 *
 */

static cv_bool number_accum_step_decimal(
    number_accum * p_this, unsigned char c_token) {
    cv_bool b_result = cv_true;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (parser_token_minus == c_token) {
        p_this->b_negative = cv_true;
    } else if (parser_token_plus == c_token) {
        p_this->b_negative = cv_false;
    } else if (parser_is_dec(c_token)) {
        number_accum_add_decimal(p_this, c_token);
    } else {
        b_result = cv_false;
    }
    return b_result;
}

/*
 *
 */

static void number_accum_add_hexadecimal(
    number_accum * p_this, unsigned char c_token) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(parser_is_hex(c_token),
        cv_debug_code_invalid_parameter);
    {
        unsigned const i_digit = parser_hex_digit(c_token);
        number_accum_add(p_this, parser_base_hexadecimal, i_digit);
    }
}

/*
 *  Structure: parser
 *
 *  Json decoder state machine.
 */

typedef struct parser {

    /*
     *  Current state of state machine, see parser_state enumeration for more
     *  details.
     */
    unsigned long e_state;

    /* Current depth in json value stack */
    unsigned long i_stack_len;

    /* -- */

    /* Indicate that decoder has started parsing a number */
    cv_bool b_number_started;

    /* Indicate that decoder has started parsing a word */
    cv_bool b_word_started;

    /* Indicate that decoder has started parsing a quoted string */
    cv_bool b_string_started;

    /* Indicate that o_accum_cache field is initialized */
    cv_bool b_accum_cache_initialized;

    /* Indicate that o_label_cache field is initialized */
    cv_bool b_label_cache_initialized;

    /* Align to 64-bit */
    char c_padding[3u];

    /* -- */

    /* Reference to application's final json value */
    cv_json * p_value;

    /* Align to 64-bit */
    void * p_padding[1u];

    /* -- */

    cv_chunk_root o_chunk_root;

    /* -- */

    cv_array_heap o_accum_cache;

    /* -- */

    cv_array_heap o_label_cache;

    /* -- */

    number_accum o_dec_section;

    /* -- */

    number_accum o_frac_section;

    /* -- */

    number_accum o_exp_section;

    /* -- */

    number_accum o_unicode_section;

    /* -- */

    cv_json * a_stack[parser_stack_max];

} parser;

cv_debug_decl_(g_parser_class, "cv_json_dec", sizeof(parser));

/*
 *  parser_reset_number_state()
 *
 *  Reset all number components.
 *
 *  p_this - Pointer to json decoder object.
 */

static void parser_reset_number_state(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    number_accum_reset(&p_this->o_dec_section);
    number_accum_reset(&p_this->o_frac_section);
    number_accum_reset(&p_this->o_exp_section);
}

/*
 *  parser_label_cache_free()
 *
 *  Cleanup the cached label.
 *
 *  p_this - Pointer to json decoder object.
 */

static void parser_label_cache_free(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->b_label_cache_initialized) {
        cv_array_heap_cleanup(&p_this->o_label_cache);
        p_this->b_label_cache_initialized = cv_false;
    }
}

/*
 *  parser_accum_cache_free()
 *
 *  Cleanup the cached accumulator.
 *
 *  p_this - Pointer to json decoder object.
 */

static void parser_accum_cache_free(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    if (p_this->b_accum_cache_initialized) {
        cv_array_heap_cleanup(&p_this->o_accum_cache);
        p_this->b_accum_cache_initialized = cv_false;
    }
}

/*
 *  parser_accumulate()
 *
 *  Store given token into accumulator.  The accumulator is implemented as a
 *  chunk list, the chunk list is not a linear buffer so it must be converted
 *  to a linear buffer before use.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  c_token - Single character from document.
 */

static void parser_accumulate(parser * p_this, unsigned char c_token) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_chunk_root_write_char(&p_this->o_chunk_root, c_token);
}

/*
 *  parser_save_label()
 *
 *  Keep a copy of the accumulated string to use as a label.  The saved label
 *  is kept until the next value is decoded or until the current object is
 *  completed.
 *
 *  p_this - Pointer to json decoder object.
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
 *  parser_is_object()
 *
 *  Detect if parent is an object.  When parent is an object, values must
 *  be prefixed with labels.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  Returns cv_true is parent is an object.
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
 *  parser_apply_label()
 *
 *  Apply the cached label to the given json value.  The move operation
 *  is used to reduce number of memory allocation and number of memory copy
 *  operations.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  p_value - Pointer to cv_json object.
 */

static void parser_apply_label(parser * p_this, cv_json * p_value) {
    cv_debug_assert_(p_this && p_value, cv_debug_code_null_ptr);
    if (p_this->b_label_cache_initialized) {
        cv_json_move_label(p_value, &p_this->o_label_cache);
        parser_label_cache_free(p_this);
    }
}

/*
 *  parser_apply_string()
 *
 *  Apply the accumulated string to the given json value.  The move operation
 *  is used to reduce number of memory allocation and number of memory copy
 *  operations.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  p_value - Pointer to cv_json object.
 */

static void parser_apply_string(parser * p_this, cv_json * p_value) {
    cv_debug_assert_(p_this && p_value, cv_debug_code_null_ptr);
    if (p_this->b_accum_cache_initialized) {
        cv_json_move_string(p_value, &p_this->o_accum_cache);
    }
}

/*
 *  parser_stack_join()
 *
 *  Join of json value with parent, or update final value if stack is empty.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  p_value - Pointer to cv_json object.
 */

static void parser_stack_join(parser * p_this, cv_json * p_value) {
    cv_debug_assert_(p_this && p_value, cv_debug_code_null_ptr);
    if (0 == p_this->i_stack_len) {
        if (p_value != p_this->p_value) {
            cv_json_move(p_this->p_value, p_value);
            cv_json_destroy(p_value);
        }
    } else {
        cv_json_join(p_value,
            p_this->a_stack[p_this->i_stack_len - 1]);
    }
}

/*
 *  parser_stack_push()
 *
 *  Insert a json value into stack.  Size of stack is limited, this operation
 *  may fail, in that case value must be destroyed.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  p_value - Pointer to cv_json object.
 *
 *  Returns cv_true on success, cv_false on error.
 */

static cv_bool parser_stack_push(parser * p_this, cv_json * p_value) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && p_value, cv_debug_code_null_ptr);
    if (p_this->i_stack_len < parser_stack_max) {
        p_this->a_stack[p_this->i_stack_len] = p_value;
        p_this->i_stack_len ++;
        b_result = cv_true;
    }
    return b_result;
}

/*
 *  parser_stack_alloc()
 *
 *  Alloc a json value.  First value used is the one provided by application.
 *  Subsequence allocation create a new json value.  For arrays and objects the
 *  value is pushed onto the stack.  For other types of values, it is attached
 *  to it's parent.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  e_type - Type of json value.  One of cv_json_type_xx enumerations.
 *
 *  Returns a pointer to cv_json object, or null on error.
 */

static cv_json * parser_stack_alloc(parser * p_this, unsigned e_type) {
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
            if (parser_stack_push(p_this, p_value)) {
            } else {
                if (p_value != p_this->p_value) {
                    cv_json_destroy(p_value);
                    p_value = 0;
                }
            }
        } else {
            parser_stack_join(p_this, p_value);
        }
    }
    return p_value;
}

/*
 *  parser_stack_pop()
 *
 *  Remove a json value from the stack and join with it's parent.  If last item
 *  of stack is removed then it marks the end of the json value.  If a label is
 *  in cache without any value then insert a null.
 *
 *  p_this - Pointer to json decoder object.
 */

static void parser_stack_pop(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    /* Flush of label */
    if (p_this->b_label_cache_initialized) {
        parser_stack_alloc(p_this, cv_json_type_null);
    }
    if (0 < p_this->i_stack_len) {
        parser_stack_join( p_this, p_this->a_stack[--p_this->i_stack_len]);
    }
}

/*
 *  parser_accum_cache_alloc()
 *
 *  Create a linear buffer using the accumulated data in the chunk list.  The
 *  chunk list may be empty, that may occur for empty strings, in that case
 *  create an empty linear buffer.
 *
 *  p_this - Pointer to json decoder object.
 */

static void parser_accum_cache_alloc(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    parser_accum_cache_free(p_this);
    if (!p_this->b_accum_cache_initialized) {
        cv_uptr const i_accum_len = cv_chunk_root_len(&p_this->o_chunk_root);
        if (cv_array_heap_init(&p_this->o_accum_cache, i_accum_len)) {
            cv_array_it o_array_it;
            cv_array_it_init(&o_array_it, &p_this->o_accum_cache.o_array);
            cv_chunk_root_read(&p_this->o_chunk_root, &o_array_it);
            cv_array_it_cleanup(&o_array_it);
            p_this->b_accum_cache_initialized = cv_true;
        }
    }
}

/*
 *  parser_detect_word_type()
 *
 *  Determine json value type by comparing the given string with a list of
 *  reserved words.
 *
 *  p_array - Pointer to cv_array object to be compared with list of reserved
 *  words.
 *
 *  Returns cv_json_type if string matches, else 0 if no match is found.
 */

static unsigned parser_detect_word_type(cv_array const * p_array) {
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
    unsigned e_word_type = cv_json_type_string;
    cv_debug_assert_(p_array, cv_debug_code_null_ptr);
    if (cv_array_compare( p_array, &g_ref_null)) {
        e_word_type = cv_json_type_null;
    } else if (cv_array_compare( p_array, &g_ref_false)) {
        e_word_type = cv_json_type_false;
    } else if (cv_array_compare(p_array, &g_ref_true)) {
        e_word_type = cv_json_type_true;
    }
    return e_word_type;
}

/*
 *  parser_convert_number()
 *
 *  Convert accumulated number data to a single floating point number.  The
 *  accumulated data contains three components, decimal, fraction and exponent.
 *  This function combined all three components.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  Returns floating point number.
 */

static double parser_convert_number(parser * p_this) {
    double i_value = 0.0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    i_value = p_this->o_dec_section.u.f_value;
    /* Divide by ten for each fraction */
    {
        double i_fraction = p_this->o_frac_section.u.f_value;
        unsigned long i_digit_iterator =
            p_this->o_frac_section.i_digit_count;
        while (i_digit_iterator --) {
            i_fraction = i_fraction / parser_base_decimal;
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
                i_value = i_value / parser_base_decimal;
            }
        } else {
            while (i_exp_iterator --) {
                i_value = i_value * parser_base_decimal;
            }
        }
    }
    return i_value;
}

/*
 *  parser_flush_string()
 *
 *  Helper function for parser_flush().  Create a json value for a string.  The
 *  accumulated data is free of quotes and escapes, unicode characters have
 *  been converted or stripped.  Only thing left to do is to stored into a json
 *  value.
 *
 *  p_this - Pointer to json decoder object.
 */

static void parser_flush_string(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(p_this->b_string_started, cv_debug_code_error);
    {
        /* flush the accumulated string */
        /* create a string node */
        cv_json * p_value = parser_stack_alloc(p_this, cv_json_type_string);
        if (p_value) {
            parser_apply_string(p_this, p_value);
        }
    }
}

/*
 *  parser_flush_number()
 *
 *  Helper function for parser_flush(), flush of accumulated data for numbers.
 *  If a number was accumulated by state machine then convert the accumulated
 *  data to a floating point number and store into a json value.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  The accumulated data is stored into three components, decimal, fraction and
 *  exponent.  All three components must be recombined in order to form a
 *  floating point number.
 */

static void parser_flush_number(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(p_this->b_number_started, cv_debug_code_error);
    {
        cv_json * const p_value = parser_stack_alloc(p_this,
            cv_json_type_number);
        if (p_value) {
            double i_value = parser_convert_number(p_this);
            cv_json_set_number(p_value, i_value);
        }
    }
}

/*
 *  parser_flush_word()
 *
 *  Helper function for parser_flush().  Create a json value using identifier.
 *  If the idenfifier corresponds to one of the reserved words, then create a
 *  matching json value.  If the identifier is not a reserved word, then create
 *  a string.
 *
 *  p_this - Pointer to json decoder object.
 */

static void parser_flush_word(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(p_this->b_word_started, cv_debug_code_error);
    {
        unsigned const e_word_type = parser_detect_word_type(
            &p_this->o_accum_cache.o_array);
        cv_json * const p_value = parser_stack_alloc(p_this, e_word_type);
        if (p_value) {
            if (cv_json_type_string == e_word_type) {
                parser_apply_string(p_this, p_value);
            }
        }
    }
}

/*
 *  parser_flush()
 *
 *  Processing of accumulated data.  The state machine has stored data into the
 *  accumulator, now it's time to transfer the data to a json value.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  The first step is to create a linear buffer from accumulated data.  Then
 *  the linear buffer must be processed as a label, string, number or word,
 *  depending of the flags set during accumulation.
 */

static void parser_flush(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    parser_accum_cache_alloc(p_this);
    if (p_this->b_accum_cache_initialized) {
        /* check for label */
        /* if parent is object and label is required */
        cv_bool const b_is_object = parser_is_object(p_this);
        if (b_is_object && !p_this->b_label_cache_initialized) {
            parser_save_label(p_this);
        } else {
            if (p_this->b_number_started) {
                parser_flush_number(p_this);
            }
            if (p_this->b_string_started) {
                parser_flush_string(p_this);
            }
            if (p_this->b_word_started) {
                parser_flush_word(p_this);
            }
        }
        p_this->b_string_started = cv_false;
        p_this->b_word_started = cv_false;
        p_this->b_number_started = cv_false;
        parser_reset_number_state(p_this);
        parser_accum_cache_free(p_this);
    }
    cv_chunk_root_empty(&p_this->o_chunk_root);
}

/*
 *  parser_step_idle()
 *
 *  Helper function for parser_step(), advance json decoder for idle state.
 *  This state represents the space between each value.  The type of value is
 *  detected using the token and the state is updated accordingly.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  c_token - Single character from document.
 *
 *  Returns same as parser_step().
 */

static cv_bool parser_step_idle(parser * p_this,
    unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(state_idle == p_this->e_state, cv_debug_code_error);
    if (parser_token_string == c_token) {
        p_this->b_string_started = cv_true;
        p_this->e_state = state_string_normal;
    } else if (parser_is_dec(c_token) || (parser_token_period == c_token) ||
        (parser_token_minus == c_token) || (parser_token_plus == c_token)) {
        p_this->e_state = state_number_dec_digit;
        b_repeat = cv_true;
    } else if (parser_token_array_begin == c_token) {
        parser_stack_alloc(p_this, cv_json_type_array);
    } else if (parser_token_array_end == c_token) {
        parser_stack_pop(p_this);
        p_this->e_state = (0 == p_this->i_stack_len) ? state_end : state_idle;
    } else if (parser_token_object_begin == c_token) {
        parser_stack_alloc(p_this, cv_json_type_object);
    } else if (parser_token_object_end == c_token) {
        parser_stack_pop(p_this);
        p_this->e_state = (0 == p_this->i_stack_len) ? state_end : state_idle;
    } else if (parser_is_identifier(c_token)) {
        p_this->e_state = state_word;
        b_repeat = cv_true;
    }
    return b_repeat;
}

/*
 *  parser_step_string()
 *
 *  Helper function for parser_step(), advance json decoder for string states.
 *  Handle escapes and unicode characters.  The string may only be ended by a
 *  double quote or the end of the document.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  c_token - Single character from document.
 *
 *  Returns same as parser_step().
 */

static cv_bool parser_step_string(parser * p_this, unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_((state_string_normal <= p_this->e_state) &&
        (state_string_unicode >= p_this->e_state), cv_debug_code_error);
    if (state_string_normal == p_this->e_state) {
        if (parser_token_string == c_token) {
            p_this->e_state = state_flush;
        } else if (parser_token_backslash == c_token) {
            p_this->e_state = state_string_escape;
        } else {
            /* store token into chunk list... */
            parser_accumulate(p_this, c_token);
        }
    } else if (state_string_escape == p_this->e_state) {
        if ((parser_token_u == c_token) || (parser_token_U == c_token)) {
            number_accum_reset(&p_this->o_unicode_section);
            p_this->e_state = state_string_unicode;
        } else if (parser_escape_tab == c_token) {
            parser_accumulate(p_this, parser_literal_tab);
            p_this->e_state = state_string_normal;
        } else if (parser_escape_bell == c_token) {
            parser_accumulate(p_this, parser_literal_bell);
            p_this->e_state = state_string_normal;
        } else if (parser_escape_cr == c_token) {
            parser_accumulate(p_this, parser_literal_cr);
            p_this->e_state = state_string_normal;
        } else if (parser_escape_lf == c_token) {
            parser_accumulate(p_this, parser_literal_lf);
            p_this->e_state = state_string_normal;
        } else {
            parser_accumulate(p_this, c_token);
            p_this->e_state = state_string_normal;
        }
    } else if (state_string_unicode == p_this->e_state) {
        /* store this character into unicode accumulator */
        cv_bool b_flush_hex = cv_false;
        if (parser_is_hex(c_token)) {
            number_accum_add_hexadecimal(
                &p_this->o_unicode_section, c_token);
            if (p_this->o_unicode_section.i_digit_count >=
                parser_unicode_max) {
                b_flush_hex = cv_true;
            }
        } else {
            b_flush_hex = cv_true;
            b_repeat = cv_true;
        }
        if (b_flush_hex) {
            /* store this character into unicode accumulator */
            /* todo: support for utf-16 characters */
            if (p_this->o_unicode_section.ll_digits <=
                cv_unsigned_char_max_) {
                unsigned char const c_hex_digit =
                    p_this->o_unicode_section.ll_digits &
                    cv_unsigned_char_max_;
                parser_accumulate(p_this, c_hex_digit);
            }
            number_accum_reset(&p_this->o_unicode_section);
            p_this->e_state = state_string_normal;
        }
    }
    return b_repeat;
}

/*
 *  parser_step_number()
 *
 *  Helper function for parser_step(), advance json decoder for number states.
 *  The number is composed of three parts, decimal, fraction and exponent.  The
 *  digits are processed and also a copy is stored into the accumulator since
 *  the number may be used as a label.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  c_token - Single character from document.
 *
 *  Returns same as parser_step().
 *
 *  Each component is handled by the number_accum object.  Characters are fed
 *  to the number_accum object which accumulates the digits to form a
 *  floating point number and a integer.  Sign is also stored.
 */

static cv_bool parser_step_number(parser * p_this, unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_((state_number_dec_digit <= p_this->e_state) &&
        (state_number_exp_digit >= p_this->e_state), cv_debug_code_error);
    if (state_number_dec_digit == p_this->e_state) {
        if (number_accum_step_decimal(
                &p_this->o_dec_section, c_token)) {
        } else if (parser_token_period == c_token) {
            p_this->e_state = state_number_frac_digit;
        } else if ((parser_token_e == c_token) ||
            (parser_token_E == c_token)) {
            p_this->e_state = state_number_exp_digit;
        } else {
            p_this->e_state = state_flush;
            b_repeat = cv_true;
        }
    } else if (state_number_frac_digit == p_this->e_state) {
        if (number_accum_step_decimal(
                &p_this->o_frac_section, c_token)) {
        } else if ((parser_token_e == c_token) ||
            (parser_token_E == c_token)) {
            p_this->e_state = state_number_exp_digit;
        } else {
            p_this->e_state = state_flush;
            b_repeat = cv_true;
        }
    } else if (state_number_exp_digit == p_this->e_state) {
        if (number_accum_step_decimal(
                &p_this->o_exp_section, c_token)) {
        } else {
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
 *  parser_step_word()
 *
 *  Helper function for parser_step(), advance json decoder for word states.
 *  The word is either a reserved word or a javascript identifier.  Store all
 *  characters of word into accumulator, the magic is done at the flush.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  c_token - Single character from document.
 *
 *  Returns same as parser_step().
 */

static cv_bool parser_step_word(parser * p_this, unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(state_word == p_this->e_state, cv_debug_code_error);
    if (parser_is_identifier(c_token)) {
        p_this->b_word_started = cv_true;
        parser_accumulate(p_this, c_token);
    } else {
        p_this->e_state = state_flush;
        b_repeat = cv_true;
    }
    return b_repeat;
}

/*
 *  parser_step()
 *
 *  Use given character to advance the json decoder state machine.  The
 *  character may be consumed or repeated.  When repeated, the caller must call
 *  this function again with the same character.
 *
 *  This function is the main switch for the state machine.  This function
 *  dispatches to sub functions according to current state.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  c_token - Single character from document.
 *
 *  Returns cv_true if character must be repeated.  cv_false if character is
 *  consumed.
 */

static cv_bool parser_step(parser * p_this, unsigned char c_token) {
    cv_bool b_repeat = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_assert_(state_end >= p_this->e_state, cv_debug_code_error);
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
        p_this->e_state = (0 == p_this->i_stack_len) ? state_end : state_idle;
        b_repeat = cv_true;
    }
    return b_repeat;
}

/*
 *  parser_walk()
 *
 *  Process a single character from document.  The character to fed to
 *  parser_step() function one or more times until the character is consumed.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  c_token - Single character from document.
 */

static void parser_walk(parser * p_this, unsigned char c_token) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    while ((state_end != p_this->e_state) &&
        parser_step(p_this, c_token)) {
    }
}

/*
 *  parser_run()
 *
 *  Process all data from given document until reach end of json value or
 *  until reach end of document.  The document is split into characters and
 *  each character is fed to parser_walk() function.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  p_document - Pointer to cv_array_it object.  See cv_json_dec_array_it
 *  for more details.
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
 *  parser_init()
 *
 *  Initialize the json decoder state machine.
 *
 *  p_this - Pointer to json decoder object.
 *
 *  p_value - Pointer to cv_json object.  A reference to this object is stored
 *  into state machine.  It must not be destroyed by application during
 *  lifetime of json decoder.
 */

static void parser_init(parser * p_this, cv_json * p_value) {
    cv_debug_assert_(p_this && p_value, cv_debug_code_null_ptr);
    cv_debug_construct_(g_parser_class, p_this);
    p_this->e_state = state_idle;
    p_this->i_stack_len = 0;
    p_this->b_word_started = cv_false;
    p_this->b_string_started = cv_false;
    p_this->b_number_started = cv_false;
    p_this->b_accum_cache_initialized = cv_false;
    p_this->b_label_cache_initialized = cv_false;
    p_this->p_value = p_value;
    cv_chunk_root_init(&p_this->o_chunk_root);
    number_accum_reset(&p_this->o_unicode_section);
    parser_reset_number_state(p_this);
}

/*
 *  parser_cleanup()
 *
 *  Flush remaining data from caches and to cleanup of all members.  The flush
 *  does not discard the data, it tries to complete the json value.  If some
 *  seperators are missing from end of document the value is not completely
 *  lost.
 *
 *  p_this - Pointer to json decoder object.
 */

static void parser_cleanup(parser * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    /* Flush of caches */
    parser_flush(p_this);
    /* Free the stack */
    while (p_this->i_stack_len) {
        parser_stack_pop(p_this);
    }
    p_this->p_value = 0;
    parser_label_cache_free(p_this);
    parser_accum_cache_free(p_this);
    cv_chunk_root_cleanup(&p_this->o_chunk_root);
    cv_debug_destruct_(g_parser_class, p_this);
}

/*
 *  cv_json_dec_array_it()
 *
 *  Decode a json document and store the value into the given cv_json object.
 *  Iterator will advance until state machine has discovered the end of the
 *  json value.
 *
 *  p_document - Pointer to cv_array_it object.  This parameter is used as
 *  input for the json decoder.  The iterator must refer to a complete json
 *  value.
 *
 *  p_value - Pointer to cv_json object.  This parameter is used as output for
 *  the json decoder.  The final value is stored into this cv_json object.
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
 *  cv_json_dec_array()
 *
 *  Decode a json document and store the value into the given cv_json object.
 *  Only one json value is decoded from given document.
 *
 *  p_document - Pointer to cv_array object.  This parameter is used as input
 *  for the json decoder.  The array must refer to a complete json value.
 *
 *  p_value - Pointer to cv_json object.  This parameter is used as output for
 *  the json decoder.  The final value is stored into this cv_json object.
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

