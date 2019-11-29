/* See LICENSE for license details */

#ifndef cv_stack_h_
#define cv_stack_h_

/*
 *  Module: cv_stack.h
 *
 *  Stack is a list of objects which are inserted into the list using a push,
 *  and removed from the list using a pop.  This is called a LIFO, or last in
 *  first out.
 */

#include <cv_stack_pred.h>

#include <cv_stack_ptr.h>

/*
 *  Structure: cv_stack
 *
 *  Representation of root element of stack or of each object within the stack.
 */

struct cv_stack
{
    cv_stack_ptr o_next;
};

#define cv_stack_initializer_ { cv_ptr_null_ }

void cv_stack_init(
    cv_stack * p_this);

void cv_stack_cleanup(
    cv_stack * p_this);

void cv_stack_push(
    cv_stack * p_this,
    cv_stack * p_object);

cv_stack * cv_stack_pop(
    cv_stack * p_this);

#endif /* #ifndef cv_stack_h_ */

/* end-of-file: cv_stack.h */
