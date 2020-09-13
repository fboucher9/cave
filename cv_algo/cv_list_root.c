/* See LICENSE for license details */

/*

Module: cv_list_root.c

Description: Implementation of cv_list_root object.  Offers services to init and
cleanup the cv_list_root object.  Other methods are handled by cv_node and
cv_node_it modules.

*/

#include <cv_algo/cv_list_root.h>

#include <cv_debug/cv_debug.h>

cv_debug_decl_(g_class);

/*

Function: cv_list_root_init()

Description: Initialize the given cv_list_root object.  The first and last pointers
are set to address of cv_list_root object creating an empty list.

Parameters: p_this - Pointer to cv_list_root object.

Returns: boolean value

Comments: The memory allocated for instance may be uninitialized.

*/
void cv_list_root_init(
    cv_list_root * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(g_class, p_this);
    cv_list_node_init( &p_this->o_node);
}

/*

Function: cv_list_root_cleanup()

Description: Cleanup the given cv_list_root object.  It is responsability of
application to first detach all items from list.  The object is returned to
uninitialized state.

Parameters: p_this - Pointer to cv_list_root object.

Returns: none.

Comments: none.

*/
void cv_list_root_cleanup(
    cv_list_root * p_this)
{
    cv_debug_assert_( p_this, cv_debug_code_null_ptr);
    /* Assert if not already empty */
    if (p_this->o_node.o_next.p_node != &p_this->o_node) {
        cv_debug_msg_(cv_debug_code_not_empty);
    }
    cv_list_node_cleanup( &p_this->o_node);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

void cv_list_root_append(
    cv_list_root * p_this,
    cv_list_node * p_node) {
    cv_list_join(p_node, &p_this->o_node);
}

/*
 *
 */

void cv_list_root_prepend(
    cv_list_root * p_this,
    cv_list_node * p_node) {
    cv_list_join(&p_this->o_node, p_node);
}

/* end-of-file: cv_list_root.c */
