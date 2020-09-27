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
        if (0 != cv_array_len(&o_label)) {
            cv_print_char('\"');
            cv_print_array(&o_label);
            cv_print_char('\"');
            cv_print_char(':');
        }
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
        long const i_number = cv_cast_(long)(f_number);
        cv_print_dec(i_number);
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

static void cv_json_test_1_object(void) {
    cv_json * p_this = cv_json_create();
    if (p_this) {
        cv_json_set_type(p_this, cv_json_type_object);
        {
            cv_json * p_child = cv_json_create();
            if (p_child) {
                static unsigned char const a_label[] = {
                    'l', 'a', 'b', 'e', 'l', '1' };
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
                    'l', 'a', 'b', 'e', 'l', '2' };
                static cv_array const o_label = cv_array_initializer_(
                    a_label, a_label + sizeof(a_label));
                cv_json_set_label(p_child, &o_label);
                cv_json_set_type(p_child, cv_json_type_number);
                cv_json_set_number(p_child, 8);
                cv_json_join(p_child, p_this);
            }
        }
        dump_json_node(p_this, cv_false, cv_true);
        cv_json_destroy(p_this);
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
}

/*
 *
 */

void cv_json_test(void) {
    cv_json_test_1();
}

/* end-of-file: cv_json_test.h */
