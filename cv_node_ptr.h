/* See LICENSE for license details */

#ifndef cv_node_ptr_h_
#define cv_node_ptr_h_

#include <cv_node_pred.h>

#include <cv_null.h>

/*

Cast of cv_node pointers to or from void pointer.  Also cast to or from const
pointers.

*/

union cv_node_ptr
{
    void * p_void;
    void const * pc_void;
    cv_node * p_node;
    cv_node const * pc_node;
};

#define cv_node_ptr_null_ { cv_null_ }

typedef char cv_verify_sizeof_node_ptr [
    sizeof(cv_node_ptr) == sizeof(void *)
    && sizeof(cv_node_ptr) == sizeof(void const *)
    && sizeof(cv_node_ptr) == sizeof(cv_node *)
    && sizeof(cv_node_ptr) == sizeof(cv_node const *)
    ? 1 : -1 ];

#endif /* #ifndef cv_node_ptr_h_ */
