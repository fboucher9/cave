/* See LICENSE for license details */

#include <cv_heap_section.h>

#include <cv_runtime.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

#include <cv_node_it.h>

#include <cv_array.h>

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
    cv_node_ptr o_node_ptr;
};

struct cv_heap_section_node_desc
{
    cv_heap_section_list * p_parent;
    void * pv_padding[1u];
    /* -- */
    long i_grow_len;
    long l_padding[1u];
};

#define cv_heap_section_node_desc_initializer_ \
{ \
    cv_null_, \
    { cv_null_ }, \
    0, \
    { 0 } \
}

struct cv_heap_section_node
{
    cv_node o_node;
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

static cv_bool cv_heap_section_node_init(
    cv_heap_section_node * p_this,
    cv_heap_section_node_desc const * p_desc)
{
    cv_bool b_result = cv_false;
    if (p_this && p_desc)
    {
        cv_node_init(&p_this->o_node);
        p_this->o_desc = *p_desc;
        cv_array_init(&p_this->o_allocation);
        cv_array_init(&p_this->o_payload);
        cv_node_join(&p_this->o_node,
            &p_desc->p_parent->o_list.o_node);
        b_result = cv_true;
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

static void cv_heap_section_node_cleanup(
    cv_heap_section_node * p_this)
{
    if (p_this)
    {
        cv_node_cleanup(&p_this->o_node);
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
}

static cv_heap_section_node * cv_heap_section_node_create(
    cv_heap_section_node_desc const * p_desc)
{
    cv_heap_section_ptr o_ptr = cv_ptr_null_;
    if (p_desc)
    {
        long const i_malloc_len = p_desc->i_grow_len;
        o_ptr.p_void = cv_runtime_malloc(i_malloc_len);
        if (o_ptr.p_void)
        {
            if (cv_heap_section_node_init(o_ptr.p_heap_section_node,
                    p_desc))
            {
                cv_array_setup(
                    &o_ptr.p_heap_section_node->o_allocation,
                    o_ptr.p_void,
                    o_ptr.pc_char + i_malloc_len);

                cv_array_setup(
                    &o_ptr.p_heap_section_node->o_payload,
                    o_ptr.p_heap_section_node + 1,
                    o_ptr.pc_char + i_malloc_len);
            }
            else
            {
                cv_runtime_free(o_ptr.p_void);
                o_ptr.p_void = cv_null_;
            }
        }
        else
        {
            cv_debug_msg_("out of memory");
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return o_ptr.p_heap_section_node;
}

static void cv_heap_section_node_destroy(
    cv_heap_section_node * p_this)
{
    if (p_this)
    {
        cv_heap_section_node_cleanup(p_this);
        cv_runtime_free(p_this->o_allocation.o_min.p_void);
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
}

cv_bool cv_heap_section_list_init(
    cv_heap_section_list * p_this,
    cv_heap_section_desc const * p_desc)
{
    cv_bool b_result = cv_false;
    if (p_this && p_desc)
    {
        p_this->o_desc = *p_desc;
        cv_list_init(&p_this->o_list);
        {
            cv_array o_null_array = cv_array_initializer_;
            cv_array_it_init(&p_this->o_array_it, &o_null_array);
        }
        b_result = cv_true;
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

void cv_heap_section_list_cleanup(
    cv_heap_section_list * p_this)
{
    if (p_this)
    {
        /* Destroy all nodes */
        cv_node_it o_node_it = cv_node_it_initializer_;
        if (cv_node_it_init(&o_node_it, &p_this->o_list))
        {
            cv_heap_section_ptr o_ptr = cv_ptr_null_;
            while (cv_node_it_first(&o_node_it, &o_ptr.o_node_ptr))
            {
                cv_heap_section_node_destroy(o_ptr.p_heap_section_node);
            }
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
}

static cv_bool cv_heap_section_list_grow(
    cv_heap_section_list * p_this)
{
    cv_bool b_result = cv_false;
    if (p_this)
    {
        cv_heap_section_ptr o_ptr = cv_ptr_null_;

        cv_heap_section_node_desc o_desc =
            cv_heap_section_node_desc_initializer_;

        o_desc.p_parent = p_this;
        o_desc.i_grow_len = p_this->o_desc.i_grow_len;

        o_ptr.p_heap_section_node =
            cv_heap_section_node_create(&o_desc);
        if (o_ptr.p_heap_section_node)
        {
            /* Setup array iterator to new buffer */
            if (cv_array_it_init(&p_this->o_array_it,
                &o_ptr.p_heap_section_node->o_payload))
            {
                b_result = cv_true;
            }
            else
            {
                cv_heap_section_node_destroy(
                    o_ptr.p_heap_section_node);
            }
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return b_result;
}

void * cv_heap_section_list_alloc(
    cv_heap_section_list * p_this,
    long i_len)
{
    cv_array_ptr o_data_ptr = cv_ptr_null_;
    if (p_this)
    {
        if (i_len)
        {
            /* Align len */
            long const i_aligned_len = cv_sizeof_align(i_len, 8);

            /* Check for grow */
            if (cv_array_it_get_next_array(&p_this->o_array_it,
                    i_aligned_len,
                    &o_data_ptr))
            {
            }
            else
            {
                if (cv_heap_section_list_grow(p_this))
                {
                    if (cv_array_it_get_next_array(&p_this->o_array_it,
                            i_aligned_len,
                            &o_data_ptr))
                    {
                    }
                    else
                    {
                        cv_debug_msg_("too big");
                    }
                }
                else
                {
                    cv_debug_msg_("grow fail");
                }
            }
        }
        else
        {
            cv_debug_msg_("zero len");
        }
    }
    else
    {
        cv_debug_msg_("null ptr");
    }
    return o_data_ptr.p_void;
}

/* end-of-file: cv_heap_section.c */
