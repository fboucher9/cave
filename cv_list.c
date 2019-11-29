/* See LICENSE for license details */

/*

Module: cv_list.c

Description: Implementation of cv_list object.  Offers services to init and
cleanup the cv_list object.  Other methods are handled by cv_node and
cv_node_it modules.

*/

#include <cv_list.h>

#include <cv_debug.h>

#include <cv_sizeof.h>

/*

Function: cv_list_init()

Description: Initialize the given cv_list object.  The first and last pointers
are set to address of cv_list object creating an empty list.

Parameters: p_this - Pointer to cv_list object.

Returns: boolean value

Comments: The memory allocated for instance may be uninitialized.

*/
void cv_list_init(
    cv_list * p_this)
{
    cv_debug_assert_(
        !!p_this,
        "null ptr");
    {
        cv_debug_init_(p_this, cv_sizeof_(*p_this));
        cv_node_init(
            &p_this->o_node);
    }
}

/*

Function: cv_list_cleanup()

Description: Cleanup the given cv_list object.  It is responsability of
application to first detach all items from list.  The object is returned to
uninitialized state.

Parameters: p_this - Pointer to cv_list object.

Returns: none.

Comments: none.

*/
void cv_list_cleanup(
    cv_list * p_this)
{
    cv_debug_assert_(
        !!p_this,
        "null ptr");
    {
        /* Assert if not already empty */
        if (p_this->o_node.o_next.p_node !=
            &p_this->o_node)
        {
            cv_debug_msg_("list cleanup not empty");
        }

        cv_node_cleanup(
            &p_this->o_node);

        cv_debug_cleanup_(p_this, cv_sizeof_(*p_this));
    }
}

/* end-of-file: cv_list.c */
