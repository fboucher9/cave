/* See LICENSE for license details */

/*
 *  Module: cv_stack.c
 *
 *  Description: Stack services.
 */


#include <cv_stack.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

#include <cv_null.h>


/*
 *  Function: cv_stack_init()
 */

void cv_stack_init(
    cv_stack * p_this)
{
    cv_debug_assert_( !!p_this, "null ptr");
    cv_debug_init_( p_this, cv_sizeof_(*p_this));
    p_this->o_next.p_void = cv_null_;
}

/*
 *  Function: cv_stack_cleanup()
 */

void cv_stack_cleanup(
    cv_stack * p_this)
{
    cv_debug_assert_( !!p_this, "null ptr");
    if (p_this->o_next.p_void) {
        cv_debug_msg_("stack not empty");
    }
    cv_debug_cleanup_( p_this, cv_sizeof_(*p_this));
}

/*
 *  Function: cv_stack_push()
 */

void cv_stack_push(
    cv_stack * p_this,
    cv_stack * p_object)
{
    cv_debug_assert_( p_this && p_object, "null ptr");
    p_object->o_next.p_stack = p_this->o_next.p_stack;
    p_this->o_next.p_stack = p_object;
}

/*
 *  Function: cv_stack_pop()
 */

cv_bool cv_stack_pop(
    cv_stack * p_this,
    cv_stack_ptr * r_value)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_( p_this && r_value, "null ptr");
    {
        cv_stack_ptr o_next = p_this->o_next;
        if (o_next.p_stack) {
            p_this->o_next = o_next.p_stack->o_next;
            o_next.p_stack->o_next.p_stack = cv_null_;
            *r_value = o_next;
            b_result = cv_true;
        }
    }
    return b_result;
}

/* end-of-file: cv_stack.c */
