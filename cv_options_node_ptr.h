/* See LICENSE for license details */

#ifndef cv_options_node_ptr_h_
#define cv_options_node_ptr_h_

#include <cv_options_pred.h>

#include <cv_node_ptr.h>

union cv_options_node_ptr
{
    cv_node_ptr o_node_ptr;
    cv_options_node * p_options_node;
    cv_options_node const * pc_options_node;
};

#define cv_options_node_ptr_null_ { cv_node_ptr_null_ }

typedef char cv_verify_sizeof_options_node_ptr [
    sizeof(cv_options_node_ptr) == sizeof(cv_node_ptr)
    && sizeof(cv_options_node_ptr) == sizeof(cv_options_node *)
    && sizeof(cv_options_node_ptr) == sizeof(cv_options_node const *)
    ? 1 : -1 ];

#endif /* #ifndef cv_options_node_ptr_h_ */
