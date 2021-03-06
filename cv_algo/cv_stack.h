/* See LICENSE for license details */

#ifndef cv_stack_h_
#define cv_stack_h_

/*
 *  Module: cv_stack.h
 *
 *  Stack is a list of objects which are inserted into the list using a push at
 *  head of list, and removed from the list using a pop from head of list.
 */

#include <cv_algo/cv_stack_pred.h>
#include <cv_algo/cv_stack_ptr.h>
#include <cv_misc/cv_bool.h>
#include <cv_misc/cv_types.h>

/*
 *  Structure: cv_stack
 *
 *  Representation of root element of stack or of each object within the stack.
 */

struct cv_stack {
    cv_stack_ptr o_next;
};

void cv_stack_init( cv_stack * p_this);
void cv_stack_cleanup( cv_stack * p_this);
void cv_stack_push( cv_stack * p_this, cv_stack * p_object);
cv_bool cv_stack_pop( cv_stack * p_this, cv_stack_ptr * r_value);

#endif /* #ifndef cv_stack_h_ */

/* end-of-file: cv_stack.h */
