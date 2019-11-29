/* See LICENSE for license details */

#ifndef cv_stack_ptr_h_
#define cv_stack_ptr_h_

#include <cv_stack_pred.h>

#include <cv_ptr.h>

/*
 *  Union: cv_stack_ptr
 *
 *  Description: Compatible pointers for cv_stack objects.
 *
 */

union cv_stack_ptr
{
    void const * pc_void;
    void * p_void;
    cv_stack const * pc_stack;
    cv_stack * p_stack;
    cv_ptr o_ptr;
};

/* Validate assumptions of union */
typedef char cv_verify_sizeof_stack_ptr [
    (sizeof(cv_stack_ptr) == sizeof(void const *)) &&
    (sizeof(cv_stack_ptr) == sizeof(void *)) &&
    (sizeof(cv_stack_ptr) == sizeof(cv_stack const *)) &&
    (sizeof(cv_stack_ptr) == sizeof(cv_stack *)) &&
    (sizeof(cv_stack_ptr) == sizeof(cv_ptr)) ? 1 : -1 ];

#endif /* #ifndef cv_stack_ptr_h_ */

/* end-of-file: cv_stack_ptr.h */
