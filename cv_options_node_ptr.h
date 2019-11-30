/* See LICENSE for license details */

#ifndef cv_options_node_ptr_h_
#define cv_options_node_ptr_h_

#include <cv_options_pred.h>

#include <cv_list_ptr.h>

union cv_options_node_ptr
{
    void const * pc_void;
    void * p_void;
    cv_options_node * p_options_node;
    cv_options_node const * pc_options_node;
    cv_list_ptr o_list_ptr;
};

typedef char cv_verify_sizeof_options_node_ptr [
    sizeof(cv_options_node_ptr) == sizeof(cv_list_ptr)
    && sizeof(cv_options_node_ptr) == sizeof(cv_options_node *)
    && sizeof(cv_options_node_ptr) == sizeof(cv_options_node const *)
    ? 1 : -1 ];

#endif /* #ifndef cv_options_node_ptr_h_ */
