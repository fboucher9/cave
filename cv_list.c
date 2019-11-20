/* See LICENSE for license details */

/*

Module: cv_list.c

Description: Implementation of cv_list object.  Offers services to init and
cleanup the cv_list object.  Other methods are handled by cv_node and
cv_node_it modules.

*/

#include <cv_list.h>

#include <cv_debug.h>

/*

Function: cv_list_init()

Description: Initialize the given cv_list object.  The first and last pointers
are set to address of cv_list object creating an empty list.

Parameters: p_this - Pointer to cv_list object.

Returns: boolean value

Comments: The memory allocated for instance may be uninitialized.

*/
char cv_list_init(
    cv_list * p_this)
{
    char b_result = 0;
    if (p_this)
    {
        if (cv_node_init(
            &p_this->o_node))
        {
            b_result = 1;
        }
    }
    else
    {
        cv_debug_msg_("list init null ptr");
    }
    return b_result;
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
    if (p_this)
    {
        /* Assert if not already empty */
        if (p_this->o_node.o_next.p_node !=
            &p_this->o_node)
        {
            cv_debug_msg_("list cleanup not empty");
        }

        cv_node_cleanup(
            &p_this->o_node);
    }
    else
    {
        cv_debug_msg_("list cleanup null ptr");
    }
}

/* end-of-file: cv_list.c */
