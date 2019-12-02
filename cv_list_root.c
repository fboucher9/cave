/* See LICENSE for license details */

/*

Module: cv_list_root.c

Description: Implementation of cv_list_root object.  Offers services to init and
cleanup the cv_list_root object.  Other methods are handled by cv_node and
cv_node_it modules.

*/

#include <cv_list_root.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

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
    cv_debug_assert_( !!p_this, "null ptr");
    cv_debug_init_(p_this, cv_sizeof_(*p_this));
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
    cv_debug_assert_( !!p_this, "null ptr");
    /* Assert if not already empty */
    if (p_this->o_node.o_next.p_node != &p_this->o_node) {
        cv_debug_msg_("list cleanup not empty");
    }
    cv_list_node_cleanup( &p_this->o_node);
    cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
}

/* end-of-file: cv_list_root.c */