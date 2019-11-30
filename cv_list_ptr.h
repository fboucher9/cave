/* See LICENSE for license details */

#ifndef cv_list_ptr_h_
#define cv_list_ptr_h_

#include <cv_list_pred.h>

#include <cv_ptr.h>

/*

Cast of cv_node pointers to or from void pointer.  Also cast to or from const
pointers.

*/

union cv_list_ptr
{
    void * p_void;
    void const * pc_void;
    cv_list_node * p_node;
    cv_list_node const * pc_node;
    cv_ptr o_ptr;
};

typedef char cv_verify_sizeof_list_ptr [
    sizeof(cv_list_ptr) == sizeof(void *)
    && sizeof(cv_list_ptr) == sizeof(void const *)
    && sizeof(cv_list_ptr) == sizeof(cv_list_node *)
    && sizeof(cv_list_ptr) == sizeof(cv_list_node const *)
    ? 1 : -1 ];

#endif /* #ifndef cv_list_ptr_h_ */
