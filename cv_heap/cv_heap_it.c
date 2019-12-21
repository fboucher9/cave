/* See LICENSE for license details */

#include <cv_heap/cv_heap_it.h>

#include <cv_heap/cv_heap_node_ptr.h>

#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class);

void cv_heap_it_init(
    cv_heap_it * p_this,
    cv_list_root const * p_list)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_list_it_init( &p_this->o_list_it, p_list);
}

void cv_heap_it_cleanup(
    cv_heap_it * p_this)
{
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_list_it_cleanup( &p_this->o_list_it);
    cv_debug_destruct_(g_class, p_this);
}

cv_bool cv_heap_it_next(
    cv_heap_it * p_this,
    cv_heap_node_ptr * r_ptr)
{
    cv_bool b_result = cv_false;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    b_result = cv_list_it_next( &p_this->o_list_it, &r_ptr->o_list_ptr);
    return b_result;
}

