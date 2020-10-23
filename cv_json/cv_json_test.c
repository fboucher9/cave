/* See LICENSE for license details */

/*
 *
 */

#include <cv_json/cv_json_test.h>
#include <cv_json/cv_json.h>
#include <cv_json/cv_json_type.h>
#include <cv_json/cv_json_it.h>
#include <cv_json/cv_json_ptr.h>
#include <cv_algo/cv_array.h>
#include <cv_test_print.h>
#include <cv_misc/cv_cast.h>
#include <cv_json/cv_json_dec.h>
#include <cv_algo/cv_array_it.h>
#include <cv_options/cv_options.h>
#include <cv_options/cv_options_it.h>
#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

/*
 *
 */

static void dump_json_node(cv_json const * p_this, cv_bool b_field,
    cv_bool b_top) {
    unsigned const e_type = cv_json_get_type(p_this);
    if (b_field) {
        cv_array o_label;
        cv_array_init(&o_label);
        cv_json_get_label(p_this, &o_label);
        cv_print_char('\"');
        cv_print_array(&o_label);
        cv_print_char('\"');
        cv_print_char(':');
        cv_array_cleanup(&o_label);
    }

    if (cv_json_type_null == e_type) {
        cv_print_0("null", 80);
    } else if (cv_json_type_false == e_type) {
        cv_print_0("false", 80);
    } else if (cv_json_type_true == e_type) {
        cv_print_0("true", 80);
    } else if (cv_json_type_number == e_type) {
        double const f_number = cv_json_get_number(p_this);
#if defined cv_have_libc_
        fprintf(stdout, "%g", f_number);
        fflush(stdout);
#else /* #if defined cv_have_libc_ */
        long const i_number = cv_cast_(long)(f_number);
        cv_print_dec(i_number);
#endif /* #if defined cv_have_libc_ */
    } else if (cv_json_type_string == e_type) {
        cv_array o_string;
        cv_array_init(&o_string);
        cv_json_get_string(p_this, &o_string);
        cv_print_char('\"');
        cv_print_array(&o_string);
        cv_print_char('\"');
        cv_array_cleanup(&o_string);
    } else if (cv_json_type_array == e_type) {
        /* Iteration of children */
        cv_bool b_first = cv_true;
        cv_json_it o_it;
        cv_json_ptr o_json_ptr = {0};
        cv_json_it_init(&o_it, p_this);
        cv_print_char('[');
        while (cv_json_it_next(&o_it, &o_json_ptr)) {
            cv_json * p_child = o_json_ptr.p_value;
            if (b_first) {
                b_first = cv_false;
            } else {
                cv_print_char(',');
            }
            dump_json_node(p_child, cv_false, cv_false);
        }
        cv_json_it_cleanup(&o_it);
        cv_print_char(']');
    } else if (cv_json_type_object == e_type) {
        /* Iteration of children */
        cv_bool b_first = cv_true;
        cv_json_it o_it;
        cv_json_ptr o_json_ptr = {0};
        cv_json_it_init(&o_it, p_this);
        cv_print_char('{');
        while (cv_json_it_next(&o_it, &o_json_ptr)) {
            cv_json * p_child = o_json_ptr.p_value;
            if (b_first) {
                b_first = cv_false;
            } else {
                cv_print_char(',');
            }
            dump_json_node(p_child, cv_true, cv_false);
        }
        cv_json_it_cleanup(&o_it);
        cv_print_char('}');
    } else {
        cv_print_char('?');
    }
    if (b_top) {
        cv_print_nl();
    }
}

static void cv_json_test_1_null(void) {
    cv_json * p_this = cv_json_create();
    if (p_this) {
        cv_json_set_type(p_this, cv_json_type_null);
        dump_json_node(p_this, cv_false, cv_true);
        cv_json_destroy(p_this);
    }
}

static void cv_json_test_1_false(void) {
    cv_json * p_this = cv_json_create();
    if (p_this) {
        cv_json_set_type(p_this, cv_json_type_false);
        dump_json_node(p_this, cv_false, cv_true);
        cv_json_destroy(p_this);
    }
}

static void cv_json_test_1_true(void) {
    cv_json * p_this = cv_json_create();
    if (p_this) {
        cv_json_set_type(p_this, cv_json_type_true);
        dump_json_node(p_this, cv_false, cv_true);
        cv_json_destroy(p_this);
    }
}

static void cv_json_test_1_number(void) {
    cv_json * p_this = cv_json_create();
    if (p_this) {
        cv_json_set_type(p_this, cv_json_type_number);
        cv_json_set_number(p_this, 1234.0);
        dump_json_node(p_this, cv_false, cv_true);
        cv_json_destroy(p_this);
    }
}

static void cv_json_test_1_string(void) {
    cv_json * p_this = cv_json_create();
    if (p_this) {
        static unsigned char const a_string[] = {
            'h', 'e', 'l', 'l', 'o' };
        static cv_array const o_string = cv_array_initializer_(
            a_string, a_string + sizeof(a_string));
        cv_json_set_type(p_this, cv_json_type_string);
        cv_json_set_string(p_this, &o_string);
        dump_json_node(p_this, cv_false, cv_true);
        cv_json_destroy(p_this);
    }
}

static void cv_json_test_1_array(void) {
    cv_json * p_this = cv_json_create();
    if (p_this) {
        cv_json_set_type(p_this, cv_json_type_array);
        {
            cv_json * p_child = cv_json_create();
            if (p_child) {
                cv_json_set_type(p_child, cv_json_type_number);
                cv_json_set_number(p_child, 4);
                cv_json_join(p_child, p_this);
            }
        }
        {
            cv_json * p_child = cv_json_create();
            if (p_child) {
                cv_json_set_type(p_child, cv_json_type_number);
                cv_json_set_number(p_child, 8);
                cv_json_join(p_child, p_this);
            }
        }
        dump_json_node(p_this, cv_false, cv_true);
        cv_json_destroy(p_this);
    }
}

static cv_json * cv_json_test_build_object(void) {
    cv_json * p_this = cv_json_create();
    if (p_this) {
        cv_json_set_type(p_this, cv_json_type_object);
        {
            cv_json * p_child = cv_json_create();
            if (p_child) {
                static unsigned char const a_label[] = {
                    'a' };
                static cv_array const o_label = cv_array_initializer_(
                    a_label, a_label + sizeof(a_label));
                cv_json_set_label(p_child, &o_label);
                cv_json_set_type(p_child, cv_json_type_number);
                cv_json_set_number(p_child, 4);
                cv_json_join(p_child, p_this);
            }
        }
        {
            cv_json * p_child = cv_json_create();
            if (p_child) {
                static unsigned char const a_label[] = {
                    'b' };
                static cv_array const o_label = cv_array_initializer_(
                    a_label, a_label + sizeof(a_label));
                cv_json_set_label(p_child, &o_label);
                cv_json_set_type(p_child, cv_json_type_number);
                cv_json_set_number(p_child, 8);
                cv_json_join(p_child, p_this);
            }
        }
    }
    return p_this;
}

/*
 *
 */

static void cv_json_test_1_object(void) {
    cv_json * p_this = cv_json_test_build_object();
    if (p_this) {
        dump_json_node(p_this, cv_false, cv_true);
        cv_json_destroy(p_this);
    }
}

/*
 *
 */

static void cv_json_test_1_empty(void) {
    cv_json * p_this = cv_json_create();
    if (p_this) {
        cv_json_set_type(p_this, cv_json_type_string);
        {
            cv_array o_string;
            cv_array_init(&o_string);
            cv_json_set_string(p_this, &o_string);
            cv_array_cleanup(&o_string);
        }
        dump_json_node(p_this, cv_false, cv_true);
        cv_json_destroy(p_this);
    }
}

/*
 *
 */

static void cv_json_test_1_move(void) {
    cv_json * p_object1 = cv_json_create();
    if (p_object1) {
        cv_json * p_object2 = cv_json_test_build_object();
        if (p_object2) {
            cv_json_set_type(p_object1, cv_json_type_null);
            cv_json_move(p_object1, p_object2);
            dump_json_node(p_object1, cv_false, cv_true);
            cv_json_destroy(p_object2);
        }
        cv_json_destroy(p_object1);
    }
}

/*
 *
 */

static void cv_json_test_1(void) {
    cv_json_test_1_null();
    cv_json_test_1_false();
    cv_json_test_1_true();
    cv_json_test_1_number();
    cv_json_test_1_string();
    cv_json_test_1_array();
    cv_json_test_1_object();
    cv_json_test_1_empty();
    cv_json_test_1_move();
}

/*
 *
 */

static void cv_json_test_2_generic(
    unsigned char const * p_text,
    cv_uptr i_text_len) {
    cv_json * p_json_node = cv_json_create();
    if (p_json_node) {
        cv_array o_text;
        cv_array_init_vector(&o_text, p_text, i_text_len);
        cv_json_dec_array(&o_text, p_json_node);
        dump_json_node(p_json_node, cv_false, cv_true);
        cv_array_cleanup(&o_text);
        cv_json_destroy(p_json_node);
    }
}

/*
 *
 */

static void cv_json_test_2_null(void) {
    static unsigned char const a_text[] = {
        'n', 'u', 'l', 'l'
    };
    cv_json_test_2_generic(a_text, sizeof(a_text));
}

/*
 *
 */

static void cv_json_test_2_false(void) {
    static unsigned char const a_text[] = {
        'f', 'a', 'l', 's', 'e'
    };
    cv_json_test_2_generic(a_text, sizeof(a_text));
}

/*
 *
 */

static void cv_json_test_2_true(void) {
    static unsigned char const a_text[] = {
        't', 'r', 'u', 'e'
    };
    cv_json_test_2_generic(a_text, sizeof(a_text));
}

/*
 *
 */

static void cv_json_test_2_number(void) {
    static unsigned char const a_text[] = {
        '1', '2', '3', '4'
    };
    cv_json_test_2_generic(a_text, sizeof(a_text));
}

/*
 *
 */

static void cv_json_test_2_string(void) {
    static unsigned char const a_text[] = {
        '\"', 'h', 'e', 'l', 'l', 'o', '\"'
    };
    cv_json_test_2_generic(a_text, sizeof(a_text));
}

/*
 *
 */

static void cv_json_test_2_escapes(void) {
    static unsigned char const a_text[] = {
        '\"', '\\', 'r', '\\', 't', '\\', 'n', '\\', 'b', '\\', 'u', 'a', 'b',
        'c', 'd', '\"'
    };
    cv_json_test_2_generic(a_text, sizeof(a_text));
}

/*
 *
 */

static void cv_json_test_2_array(void) {
    static unsigned char const a_text[] = {
        '[', '4', ',', '8', ']'
    };
    cv_json_test_2_generic(a_text, sizeof(a_text));
}

/*
 *
 */

static void cv_json_test_2_object(void) {
    static unsigned char const a_text[] = {
        '{', '\"', 'a', '\"', ':', '4', ',', '\"', 'b', '\"', ':', '8', '}'
    };
    cv_json_test_2_generic(a_text, sizeof(a_text));
}

/*
 *
 */

static void cv_json_test_2(void) {
    /* test for cv_json_dec */
    cv_json_test_2_null();
    cv_json_test_2_false();
    cv_json_test_2_true();
    cv_json_test_2_number();
    cv_json_test_2_string();
    cv_json_test_2_escapes();
    cv_json_test_2_array();
    cv_json_test_2_object();
}

/*
 *
 */

void cv_json_test(cv_options_it * p_options) {
    cv_array o_option_node;
    cv_array_init(&o_option_node);
    if (cv_options_it_next(p_options, &o_option_node)) {
        /* */
        cv_print_0("option: ", 80);
        cv_print_array(&o_option_node);
        cv_print_nl();
        cv_json_test_2_generic(o_option_node.o_min.pc_uchar,
            cv_array_len(&o_option_node));
    } else {
        cv_json_test_1();
        cv_json_test_2();
    }
    cv_array_cleanup(&o_option_node);
}

/* end-of-file: cv_json_test.h */
