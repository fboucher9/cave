/* See LICENSE for license details */

#ifndef cv_thread_ptr_h_
#define cv_thread_ptr_h_

/*
 *  Module: cv_thread_ptr.h
 *
 *  Declare the cv_thread_ptr type.
 */

#include <cv_thread/cv_thread_pred.h>

#include <cv_algo/cv_ptr.h>

/*
 *  Structure: cv_thread_ptr
 *
 *  Declare a union of compatible pointers for cv_thread module.
 *  Use cv_ptr_null_ to initialize the cv_thread_ptr instance.
 */

union cv_thread_ptr
{
    void const * pc_void;
    void * p_void;
    cv_thread const * pc_thread;
    cv_thread * p_thread;
    cv_ptr o_ptr;
};

/* Compile-time verification of assumptions */
typedef char cv_verify_sizeof_thread_ptr [
    ((sizeof(cv_thread_ptr) == sizeof(void const *))
        && (sizeof(cv_thread_ptr) == sizeof(void *))
        && (sizeof(cv_thread_ptr) == sizeof(cv_thread const *))
        && (sizeof(cv_thread_ptr) == sizeof(cv_thread *))
        && (sizeof(cv_thread_ptr) == sizeof(cv_ptr)))
    ? 1 : -1 ];

union cv_thread_desc_ptr {
    void const * pc_void;
    void * p_void;
    cv_thread_desc const * pc_thread_desc;
    cv_thread_desc * p_thread_desc;
    cv_ptr o_ptr;
};

#endif /* #ifndef cv_thread_ptr_h_ */

/* end-of-file: cv_thread_ptr.h */
