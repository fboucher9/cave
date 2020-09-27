/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_stack_it.h>
#include <cv_algo/cv_stack.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class, "cv_stack_it");

/*
 *
 */

void cv_stack_it_init(
    cv_stack_it * p_this,
    cv_stack const * p_root) {
    cv_debug_assert_(p_this && p_root, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    p_this->o_cur.pc_stack = p_root->o_next.pc_stack;
}

/*
 *
 */

void cv_stack_it_cleanup(
    cv_stack_it * p_this) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

cv_bool cv_stack_it_next(
    cv_stack_it * p_this,
    cv_stack_ptr * r_cur) {
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this && r_cur, cv_debug_code_null_ptr);
    if (p_this->o_cur.pc_stack) {
        *r_cur = p_this->o_cur;
        p_this->o_cur = p_this->o_cur.pc_stack->o_next;
        b_result = cv_true;
    }
    return b_result;
}

/* end-of-file: cv_stack_it.c */
