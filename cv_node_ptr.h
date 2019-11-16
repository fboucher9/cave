/* See LICENSE for license details */

#ifndef cv_node_ptr_h_
#define cv_node_ptr_h_

#include <cv_node_pred.h>

union cv_node_ptr
{
    void * p_void;
    void const * pc_void;
    cv_node * p_node;
    cv_node const * pc_node;
};

typedef char cv_verify_sizeof_node_ptr [
    sizeof(cv_node_ptr) == sizeof(void *)
    && sizeof(cv_node_ptr) == sizeof(void const *)
    && sizeof(cv_node_ptr) == sizeof(cv_node *)
    && sizeof(cv_node_ptr) == sizeof(cv_node const *)
    ? 1 : -1 ];

#endif /* #ifndef cv_node_ptr_h_ */
