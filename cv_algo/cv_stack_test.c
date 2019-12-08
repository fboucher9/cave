/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_stack_test.h>
#include <cv_algo/cv_stack.h>
#include <cv_algo/cv_stack_it.h>
#include <cv_heap/cv_heap.h>
#include <cv_types.h>
#include <cv_sizeof.h>
#include <cv_test_print.h>

typedef struct cv_number_stack_node cv_number_stack_node;
typedef union cv_number_stack_ptr cv_number_stack_ptr;

/*
 *
 */

union cv_number_stack_ptr {
    void const * pc_void;
    void * p_void;
    cv_number_stack_node const * pc_number_stack_node;
    cv_number_stack_node * p_number_stack_node;
    cv_stack_ptr o_stack_ptr;
    cv_ptr o_ptr;
};

/* Compile-time verification of union type */
typedef char cv_verify_sizeof_number_stack_ptr [ (
    (sizeof(cv_number_stack_ptr) == sizeof(void const *)) &&
    (sizeof(cv_number_stack_ptr) == sizeof(void *)) &&
    (sizeof(cv_number_stack_ptr) == sizeof(cv_number_stack_node const *)) &&
    (sizeof(cv_number_stack_ptr) == sizeof(cv_number_stack_node *)) &&
    (sizeof(cv_number_stack_ptr) == sizeof(cv_stack_ptr)) &&
    (sizeof(cv_number_stack_ptr) == sizeof(cv_ptr)) ) ? 1 : -1];

/*
 *
 */

struct cv_number_stack_node {
    cv_stack o_stack;
    /* -- */
    long i_value;
    long l_padding[1u];
};

/*
 *
 */

void cv_stack_test(void) {
    /* Create a stack */
    cv_stack o_root = cv_stack_initializer_;
    cv_stack_init(&o_root);

    /* Create some numbers and push on stack */
    {
        static long const g_test_vector[] = {
            12345, 31, 14, 77, 5432, 8554 };
        static long const g_test_vector_count =
            cv_sizeof_(g_test_vector)/cv_sizeof_(g_test_vector[0u]);
        long i_index = 0;
        for (i_index = 0; i_index < g_test_vector_count; i_index++) {
            cv_number_stack_ptr o_node_ptr = cv_ptr_null_;
            o_node_ptr.p_void = cv_heap_alloc(
                cv_sizeof_(cv_number_stack_node));
            if (o_node_ptr.p_void) {
                cv_stack_init(&o_node_ptr.p_number_stack_node->o_stack);
                cv_stack_push(&o_root,
                    &o_node_ptr.p_number_stack_node->o_stack);
                o_node_ptr.p_number_stack_node->i_value =
                    g_test_vector[i_index];
            }
        }
    }

    /* Dump stack */
    {
        cv_stack_it o_stack_it = cv_stack_it_initializer_;
        cv_stack_it_init(&o_stack_it, &o_root);
        {
            cv_number_stack_ptr o_node_ptr = cv_ptr_null_;
            while (cv_stack_it_next(&o_stack_it, &o_node_ptr.o_stack_ptr)) {
                cv_number_stack_node const * const p_node =
                    o_node_ptr.pc_number_stack_node;
                {
                    static unsigned char const a_text[] = {
                        's', 't', 'a', 'c', 'k', ' ', '[' };
                    cv_print_vector(a_text, cv_sizeof_(a_text));
                }
                cv_print_dec(p_node->i_value);
                cv_print_char(']');
                cv_print_nl();
            }
        }
        cv_stack_it_cleanup(&o_stack_it);
    }

    /* Cleanup stack */
    {
        cv_number_stack_ptr o_node_ptr = cv_ptr_null_;
        while (cv_stack_pop(&o_root, &o_node_ptr.o_stack_ptr)) {
            cv_stack_cleanup(&o_node_ptr.p_number_stack_node->o_stack);
            cv_heap_free(o_node_ptr.p_void);
        }
    }

    cv_stack_cleanup(&o_root);
}

/* end-of-file: cv_stack_test.c */
