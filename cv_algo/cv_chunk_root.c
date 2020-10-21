/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_chunk_root.h>
#include <cv_algo/cv_chunk_ptr.h>
#include <cv_algo/cv_chunk_node.h>
#include <cv_algo/cv_chunk_it.h>
#include <cv_debug/cv_debug_class.h>
#include <cv_algo/cv_list_it.h>
#include <cv_heap/cv_heap.h>
#include <cv_algo/cv_array_it.h>

cv_debug_decl_(g_chunk_root, "cv_chunk_root", sizeof(cv_chunk_root));

/*
 *
 */

void cv_chunk_root_init(cv_chunk_root * p_this) {
    cv_debug_construct_(g_chunk_root, p_this);
    cv_list_root_init(&p_this->o_root);
    p_this->i_total_len = 0;
}

/*
 *
 */

void cv_chunk_root_cleanup(cv_chunk_root * p_this) {
    /* empty the list */
    cv_chunk_root_empty(p_this);
    cv_list_root_cleanup(&p_this->o_root);
    cv_debug_destruct_(g_chunk_root, p_this);
}

/*
 *
 */

void cv_chunk_root_empty(cv_chunk_root * p_this) {
    cv_chunk_ptr o_chunk_ptr;
    cv_list_it o_list_it;
    cv_list_it_init(&o_list_it, &p_this->o_root);
    while (cv_list_it_first(&o_list_it, &o_chunk_ptr.o_list_ptr)) {
        cv_chunk_node_cleanup(o_chunk_ptr.p_chunk);
        cv_heap_free(o_chunk_ptr.p_void);
    }
    cv_list_it_cleanup(&o_list_it);
    p_this->i_total_len = 0;
}

/*
 *
 */

static cv_bool cv_chunk_root_append(cv_chunk_root * p_this) {
    static cv_uptr g_chunk_node_unique = 0;
    cv_bool b_result = cv_false;
    cv_chunk_ptr o_chunk_ptr = {0};
    o_chunk_ptr.p_void = cv_heap_alloc(sizeof(cv_chunk_node), "chunk_node",
        ++ g_chunk_node_unique);
    if (o_chunk_ptr.p_void) {
        cv_chunk_node_init(o_chunk_ptr.p_chunk);
        cv_list_join(
            &o_chunk_ptr.p_chunk->o_node,
            &p_this->o_root.o_node);
        b_result = cv_true;
    } else {
        b_result = cv_false;
    }
    return b_result;
}

/*
 *
 */

static cv_bool cv_chunk_root_is_empty(cv_chunk_root const * p_this) {
    return (p_this->o_root.o_node.o_prev.pc_node == &p_this->o_root.o_node);
}

/*
 *
 */

static cv_bool cv_chunk_root_last(cv_chunk_root const * p_this,
    cv_chunk_ptr * r_chunk_ptr) {
    cv_bool b_result = cv_false;
    cv_chunk_ptr o_chunk_ptr = {0};
    o_chunk_ptr.o_list_ptr.pc_node =
        p_this->o_root.o_node.o_prev.pc_node;
    if (o_chunk_ptr.o_list_ptr.pc_node != &p_this->o_root.o_node) {
        *r_chunk_ptr = o_chunk_ptr;
        b_result = cv_true;
    }
    return b_result;
}

/*
 *
 */

static cv_bool cv_chunk_root_is_full(cv_chunk_root const * p_this) {
    cv_bool b_result = cv_true;
    cv_chunk_ptr o_chunk_ptr = {0};
    if (cv_chunk_root_last(p_this, &o_chunk_ptr)) {
        b_result = cv_chunk_node_is_full(o_chunk_ptr.pc_chunk);
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_chunk_root_write_char( cv_chunk_root * p_this,
    unsigned char i_value) {
    cv_bool b_result = cv_true;
    if (cv_chunk_root_is_empty(p_this) ||
        cv_chunk_root_is_full(p_this)) {
        /* append a new chunk */
        b_result = cv_chunk_root_append(p_this);
    }
    if (b_result) {
        cv_chunk_ptr o_chunk_ptr = {0};
        if (cv_chunk_root_last(p_this, &o_chunk_ptr)) {
            if (cv_chunk_node_write_char(o_chunk_ptr.p_chunk,
                    i_value)) {
                p_this->i_total_len ++;
            } else {
                b_result = cv_false;
            }
        } else {
            b_result = cv_false;
        }
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_chunk_root_write_array(cv_chunk_root * p_this,
    cv_array const * p_array) {
    cv_bool b_result = cv_true;
    cv_array_it o_array_it;
    unsigned char i_value = 0;
    cv_array_it_init(&o_array_it, p_array);
    while (b_result && cv_array_it_read_next_char(&o_array_it, &i_value)) {
        b_result = cv_chunk_root_write_char(p_this, i_value);
    }
    cv_array_it_cleanup(&o_array_it);
    return b_result;
}

/*
 *
 */

cv_uptr cv_chunk_root_len(cv_chunk_root const * p_this) {
    return p_this->i_total_len;
}

/*
 *
 */

void cv_chunk_root_read(cv_chunk_root const * p_this,
    cv_array_it * p_array_it) {
    cv_chunk_it o_chunk_it;
    (void)p_array_it;
    cv_chunk_it_init(&o_chunk_it, p_this);
    {
        cv_bool b_continue = cv_true;
        cv_chunk_ptr o_chunk_ptr;
        while (b_continue && cv_chunk_it_next(&o_chunk_it, &o_chunk_ptr)) {
            cv_chunk_node const * pc_chunk = o_chunk_ptr.pc_chunk;
            cv_uptr i_data_index = 0;
            while (b_continue && (i_data_index < pc_chunk->i_data_len)) {
                unsigned char const i_value = pc_chunk->a_data[i_data_index];
                if (cv_array_it_write_next_char(p_array_it, i_value)) {
                    i_data_index ++;
                } else {
                    b_continue = cv_false;
                }
            }
        }
    }
    cv_chunk_it_cleanup(&o_chunk_it);
}

/* end-of-file: cv_chunk_root.c */
