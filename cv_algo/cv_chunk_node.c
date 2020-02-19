/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_chunk_node.h>
#include <cv_debug/cv_debug_class.h>

cv_debug_decl_(g_chunk_node_class);

/*
 *
 */

void cv_chunk_node_init(cv_chunk_node * p_this) {
    cv_debug_construct_(g_chunk_node_class, p_this);
    cv_list_node_init(&p_this->o_node);
    p_this->i_data_len = 0;
}

/*
 *
 */

void cv_chunk_node_cleanup(cv_chunk_node * p_this) {
    cv_list_join(&p_this->o_node, &p_this->o_node);
    cv_list_node_cleanup(&p_this->o_node);
    cv_debug_destruct_(g_chunk_node_class, p_this);
}

/*
 *
 */

cv_bool cv_chunk_node_is_full(cv_chunk_node const * p_this) {
    return (p_this->i_data_len >= cv_chunk_data_len);
}

/*
 *
 */

cv_bool cv_chunk_node_write_char(cv_chunk_node * p_this,
    unsigned char i_value) {
    cv_bool b_result = cv_false;
    if (p_this->i_data_len < cv_chunk_data_len) {
        unsigned char * const p_data =
            p_this->a_data + p_this->i_data_len;
        *p_data = i_value;
        p_this->i_data_len ++;
        b_result = cv_true;
    }
    return b_result;
}

/* end-of-file: cv_chunk_node.c */
