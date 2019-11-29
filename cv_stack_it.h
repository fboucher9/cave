/* See LICENSE for license details */

#ifndef cv_stack_it_h_
#define cv_stack_it_h_

/*
 *  Module: cv_stack_it.h
 *
 *  Description: Iterator for cv_stack object.
 */

#include <cv_stack_pred.h>

#include <cv_stack_ptr.h>

struct cv_stack_it
{
    cv_stack_ptr o_cur;
};

#define cv_stack_it_initializer { cv_ptr_null_ }

void cv_stack_it_init(
    cv_stack_it * p_this,
    cv_stack const * p_root);

void cv_stack_it_cleanup(
    cv_stack_it * p_this);

#endif /* #ifndef cv_stack_it_h_ */

/* end-of-file: cv_stack_it.h */
