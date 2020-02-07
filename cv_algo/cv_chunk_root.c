/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_chunk_root.h>
#include <cv_algo/cv_chunk_ptr.h>
#include <cv_algo/cv_chunk_node.h>
#include <cv_debug/cv_debug_class.h>
#include <cv_algo/cv_list_it.h>
#include <cv_heap/cv_heap.h>

cv_debug_decl_(g_chunk_root);

/*
 *
 */

void cv_chunk_root_init(cv_chunk_root * p_this) {
    cv_debug_construct_(g_chunk_root, p_this);
    cv_list_root_init(&p_this->o_root);
    p_this->i_total_len = 0;
    p_this->i_node_len = 0;
}

/*
 *
 */

void cv_chunk_root_cleanup(cv_chunk_root * p_this) {
    /* empty the list */
    cv_chunk_root_empty(p_this);
    cv_debug_destruct_(g_chunk_root, p_this);
}

/*
 *
 */

void cv_chunk_root_empty(cv_chunk_root * p_this) {
    cv_chunk_ptr o_chunk_ptr = cv_chunk_ptr_initializer_;
    cv_list_it o_list_it = cv_list_it_initializer_;
    cv_list_it_init(&o_list_it, &p_this->o_root);
    while (cv_list_it_first(&o_list_it, &o_chunk_ptr.o_list_ptr)) {
        cv_chunk_node_cleanup(o_chunk_ptr.p_chunk);
        cv_heap_free(o_chunk_ptr.p_void);
    }
}

/*
 *
 */

static cv_bool cv_chunk_root_append(cv_chunk_root * p_this) {
    cv_bool b_result = cv_false;
    (void)p_this;
    return b_result;
}

/*
 *
 */

cv_bool cv_chunk_root_write(cv_chunk_root * p_this,
    cv_array_it * p_array_it) {
    cv_bool b_result = cv_true;
    /* append a new chunk */
    if (b_result) {
        if (p_this->o_root.o_node.o_next.pc_node ==
            &p_this->o_root.o_node) {
            b_result = cv_chunk_root_append(p_this);
        }
    }
    if (b_result) {
        (void)p_array_it;
        b_result = cv_false;
    }
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
    (void)p_this;
    (void)p_array_it;
}

/* end-of-file: cv_chunk_root.c */
