/* See LICENSE for license details */

#include <cv_heap/cv_heap_section.h>

#include <cv_runtime.h>

#include <cv_debug.h>

#include <cv_misc/cv_sizeof.h>

#include <cv_algo/cv_list_it.h>

#include <cv_algo/cv_array.h>

/* Predefine */
typedef struct cv_heap_section_node cv_heap_section_node;

/* Predefine */
typedef union cv_heap_section_ptr cv_heap_section_ptr;

/* Predefine */
typedef struct cv_heap_section_node_desc cv_heap_section_node_desc;

union cv_heap_section_ptr
{
    void const * pc_void;
    void * p_void;
    char const * pc_char;
    char * p_char;
    cv_heap_section_node const * pc_heap_section_node;
    cv_heap_section_node * p_heap_section_node;
    cv_list_ptr o_list_ptr;
};

struct cv_heap_section_node_desc
{
    long i_grow_len;
    long l_padding[1u];
};

#define cv_heap_section_node_desc_initializer_ \
{ 0, { 0 } }

struct cv_heap_section_node
{
    cv_list_node o_node;
    /* -- */
    cv_heap_section_node_desc o_desc;
    /* -- */
    cv_array o_payload;
    /* -- */
    cv_array o_allocation;
};

#if 0
#define cv_heap_section_node_initializer_ \
{ \
    cv_node_initializer_, \
    cv_heap_section_node_desc_initializer_, \
    cv_array_initializer_, \
    cv_null_, \
    { cv_null_ } \
}
#endif

static void cv_heap_section_node_init(
    cv_heap_section_node * p_this,
    cv_heap_section_node_desc const * p_desc)
{
    cv_debug_assert_(p_this && p_desc, cv_debug_code_null_ptr);
    cv_debug_init_(p_this, cv_sizeof_(*p_this));
    cv_list_node_init(&p_this->o_node);
    p_this->o_desc = *p_desc;
}

static void cv_heap_section_node_cleanup(
    cv_heap_section_node * p_this)
{
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    cv_list_node_cleanup(&p_this->o_node);
    cv_array_cleanup(&p_this->o_payload);
    cv_array_cleanup(&p_this->o_allocation);
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}

static cv_heap_section_node * cv_heap_section_node_create(
    cv_heap_section_node_desc const * p_desc)
{
    cv_heap_section_ptr o_ptr = cv_ptr_null_;
    cv_debug_assert_(!!p_desc, cv_debug_code_null_ptr);
    {
        long const i_malloc_len = p_desc->i_grow_len;
        o_ptr.p_void = cv_runtime_malloc(i_malloc_len);
        if (o_ptr.p_void) {
            cv_heap_section_node_init(o_ptr.p_heap_section_node, p_desc);

            cv_array_init_vector(
                &o_ptr.p_heap_section_node->o_allocation,
                o_ptr.p_void, i_malloc_len);

            cv_array_init_range(
                &o_ptr.p_heap_section_node->o_payload,
                o_ptr.p_heap_section_node + 1,
                o_ptr.pc_char + i_malloc_len);
        } else {
            cv_debug_msg_(cv_debug_code_out_of_memory);
        }
    }
    return o_ptr.p_heap_section_node;
}

static void cv_heap_section_node_destroy(
    cv_heap_section_node * p_this)
{
    cv_debug_assert_(!!p_this, cv_debug_code_null_ptr);
    {
        void * const p_allocation = p_this->o_allocation.o_min.p_void;
        cv_heap_section_node_cleanup(p_this);
        if (p_allocation) {
            cv_runtime_free(p_allocation);
        }
    }
}

void cv_heap_section_init(
    cv_heap_section * p_this,
    cv_heap_section_desc const * p_desc)
{
    cv_debug_assert_( p_this && p_desc, cv_debug_code_null_ptr);
    p_this->o_desc = *p_desc;
    cv_list_root_init(&p_this->o_list);
    cv_array_it_init_vector(&p_this->o_array_it, cv_null_, 0);
}

void cv_heap_section_cleanup(
    cv_heap_section * p_this)
{
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    {
        /* Destroy all nodes */
        cv_list_it o_list_it = cv_list_it_initializer_;
        cv_list_it_init(&o_list_it, &p_this->o_list);
        {
            cv_heap_section_ptr o_ptr = cv_ptr_null_;
            while (cv_list_it_first(&o_list_it, &o_ptr.o_list_ptr)) {
                cv_heap_section_node_destroy(o_ptr.p_heap_section_node);
            }
        }
        cv_list_it_cleanup(&o_list_it);
        cv_list_root_cleanup(&p_this->o_list);
        cv_array_it_cleanup(&p_this->o_array_it);
    }
}

static cv_bool cv_heap_section_grow(
    cv_heap_section * p_this)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    {
        cv_heap_section_ptr o_ptr = cv_ptr_null_;
        cv_heap_section_node_desc o_desc =
            cv_heap_section_node_desc_initializer_;
        o_desc.i_grow_len = p_this->o_desc.i_grow_len;
        o_ptr.p_heap_section_node =
            cv_heap_section_node_create(&o_desc);
        if (o_ptr.p_heap_section_node) {
            cv_list_join(&o_ptr.p_heap_section_node->o_node,
                &p_this->o_list.o_node);
            /* Setup array iterator to new buffer */
            cv_array_it_cleanup(&p_this->o_array_it);
            cv_array_it_init(&p_this->o_array_it,
                &o_ptr.p_heap_section_node->o_payload);
            b_result = cv_true;
        }
    }
    return b_result;
}

void * cv_heap_section_alloc(
    cv_heap_section * p_this,
    long i_len)
{
    cv_array_ptr o_data_ptr = cv_ptr_null_;
    cv_debug_assert_( !!p_this, cv_debug_code_null_ptr);
    cv_debug_assert_( i_len > 0, cv_debug_code_invalid_length);
    {
        /* Align len */
        long const i_aligned_len = cv_sizeof_align(i_len, 8);

        /* Check for grow */
        if (cv_array_it_get_next_array(&p_this->o_array_it,
                i_aligned_len,
                &o_data_ptr)) {
        } else {
            if (cv_heap_section_grow(p_this)) {
                if (cv_array_it_get_next_array(&p_this->o_array_it,
                        i_aligned_len,
                        &o_data_ptr)) {
                } else {
                    cv_debug_msg_(cv_debug_code_out_of_memory);
                }
            } else {
                cv_debug_msg_(cv_debug_code_out_of_memory);
            }
        }
    }
    return o_data_ptr.p_void;
}

/* end-of-file: cv_heap_section.c */
