/* See LICENSE for license details */

#ifndef cv_options_node_ptr_h_
#define cv_options_node_ptr_h_

#include <cv_options_pred.h>

#include <cv_node_pred.h>

union cv_options_node_ptr
{
    void * p_void;
    void const * pc_void;
    cv_node * p_node;
    cv_node const * pc_node;
    cv_options_node * p_options_node;
    cv_options_node const * pc_options_node;
};

typedef char cv_verify_sizeof_options_node_ptr [
    sizeof(cv_options_node_ptr) == sizeof(void *)
    && sizeof(cv_options_node_ptr) == sizeof(void const *)
    && sizeof(cv_options_node_ptr) == sizeof(cv_node *)
    && sizeof(cv_options_node_ptr) == sizeof(cv_node const *)
    && sizeof(cv_options_node_ptr) == sizeof(cv_options_node *)
    && sizeof(cv_options_node_ptr) == sizeof(cv_options_node const *)
    ? 1 : -1 ];

#endif /* #ifndef cv_options_node_ptr_h_ */
