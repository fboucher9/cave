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
 *
 */

void cv_stack_init(
    cv_stack * p_this)
{
    cv_debug_assert_(
        !!p_this,
        "null ptr");
    cv_debug_init_(
        p_this,
        cv_sizeof_(*p_this));
    p_this->o_next.p_void = cv_null_;
}

/*
 *
 */

void cv_stack_cleanup(
    cv_stack * p_this)
{
    cv_debug_assert_(
        !!p_this,
        "null ptr");
    if (p_this->o_next.p_void)
    {
        cv_debug_msg_("stack not empty");
    }
    cv_debug_cleanup_(
        p_this,
        cv_sizeof_(*p_this));
}

/*
 *
 */

void cv_stack_push(
    cv_stack * p_this,
    cv_stack * p_object)
{
    cv_debug_assert_(
        p_this && p_object,
        "null ptr");
    p_object->o_next.p_stack = p_this->o_next.p_stack;
    p_this->o_next.p_stack = p_object;
}

/*
 *
 */

cv_stack * cv_stack_pop(
    cv_stack * p_this)
{
    cv_stack * p_result = cv_null_;
    cv_debug_assert_(
        !!p_this,
        "null ptr");
    p_result = p_this->o_next.p_stack;
    if (p_result)
    {
        p_this->o_next = p_result->o_next;
    }
    return p_result;
}

/* end-of-file: cv_stack.c */
