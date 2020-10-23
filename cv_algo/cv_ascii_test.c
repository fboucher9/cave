/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_ascii_test.h>
#include <cv_algo/cv_ascii_code.h>
#include <cv_algo/cv_ascii_code_it.h>
#include <cv_algo/cv_ascii_data.h>
#include <cv_algo/cv_ascii_data_it.h>
#include <cv_algo/cv_ascii_heap.h>
#include <cv_algo/cv_ascii_0.h>
#include <cv_algo/cv_ascii_tool.h>
#include <cv_test_print.h>

/*
 *
 */

static void cv_ascii_test_1_code(void) {
    {
        unsigned char a_placement[10u];
        char const * pc_char = cv_ascii_code_cast(a_placement);
        (void)pc_char;
    }
    {
        cv_ascii_code o_this;
        cv_ascii_code_init(&o_this);
        cv_ascii_code_set_text(&o_this, "alfred", 80);
        {
            cv_uptr const i_len = cv_ascii_code_len(&o_this);
            (void)i_len;
        }
        {
            cv_ascii_code_it o_iterator;
            cv_ascii_code_it_init(&o_iterator);
            cv_ascii_code_it_alias(&o_iterator, &o_this);
            {
                char const * pc_char = 0;
                while (cv_ascii_code_it_next(&o_iterator, &pc_char)) {
                    unsigned int const c_token = *pc_char & 0xff;
                    cv_print_char(c_token & 0xff);
                }
                cv_print_nl();
            }
            cv_ascii_code_it_alias(&o_iterator, &o_this);
            {
                char const * pc_char = 0;
                while (cv_ascii_code_it_prev(&o_iterator, &pc_char)) {
                    unsigned int const c_token = *pc_char & 0xff;
                    cv_print_char(c_token & 0xff);
                }
                cv_print_nl();
            }
            cv_ascii_code_it_cleanup(&o_iterator);
        }
        cv_ascii_code_set_text(&o_this, 0, 0);
        cv_ascii_code_cleanup(&o_this);
    }
}

/*
 *
 */

static void cv_ascii_test_1_data(void) {
    unsigned char a_placement[] = {
        'a', 'l', 'f', 'r', 'e', 'd'
    };
    char * p_char = cv_ascii_data_cast(a_placement);
    cv_ascii_data o_this;
    cv_ascii_data_init(&o_this);
    o_this.p_min = p_char;
    o_this.p_max = p_char + sizeof(a_placement);
    {
        cv_uptr const i_len = cv_ascii_data_len(&o_this);
        (void)i_len;
    }
    {
        cv_ascii_data_it o_iterator;
        cv_ascii_data_it_init(&o_iterator);
        cv_ascii_data_it_alias(&o_iterator, &o_this);
        {
            char * p_cur = 0;
            while (cv_ascii_data_it_next(&o_iterator, &p_cur)) {
                unsigned int const c_token = *p_cur & 0xff;
                cv_print_char(c_token & 0xff);
            }
            cv_print_nl();
        }
        cv_ascii_data_it_alias(&o_iterator, &o_this);
        {
            char * p_cur = 0;
            while (cv_ascii_data_it_prev(&o_iterator, &p_cur)) {
                unsigned int const c_token = *p_cur & 0xff;
                cv_print_char(c_token & 0xff);
            }
            cv_print_nl();
        }
        cv_ascii_data_it_cleanup(&o_iterator);
    }
    cv_ascii_data_cleanup(&o_this);
}

/*
 *
 */

static void cv_ascii_test_1_heap(void) {
    cv_ascii_code o_code;
    cv_ascii_code_init(&o_code);
    cv_ascii_code_set_text(&o_code, "alfred", 80);
    {
        cv_ascii_heap o_this;
        cv_ascii_heap_init(&o_this);
        if (cv_ascii_heap_dup(&o_this, &o_code)) {
        } else {
            cv_print_0("wtf", 80);
            cv_print_nl();
        }
        {
            cv_uptr const i_len = cv_ascii_heap_len(&o_this);
            (void)i_len;
        }
        if (cv_ascii_heap_dup(&o_this, 0)) {
        } else {
            cv_print_0("wtf", 80);
            cv_print_nl();
        }
        cv_ascii_heap_cleanup(&o_this);
    }
    cv_ascii_code_cleanup(&o_code);
}

/*
 *
 */

static void cv_ascii_test_1(void) {
    /* test of code */
    /* test of code_it */
    cv_ascii_test_1_code();
    /* test of data */
    /* test of data_it */
    cv_ascii_test_1_data();
    /* test of heap */
    cv_ascii_test_1_heap();
    /* test of 0 */
    /* test of tool */
}

/*
 *
 */

void cv_ascii_test(void) {
    cv_ascii_test_1();
}

/* end-of-file: cv_ascii_test.c */
