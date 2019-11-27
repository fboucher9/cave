/* See LICENSE for license details */

#ifndef cv_list_h_
#define cv_list_h_

/*

Module: cv_list.h

Description: Root of linked list.  Contains pointers to first and last
elements.

*/

#include <cv_list_pred.h>

#include <cv_node.h>

#include <cv_bool.h>

/*

Structure: cv_list

Description: Members of cv_list object.  Implementation uses a node since a
node has two pointers.  Also the node functions may be used on the root.

*/
struct cv_list
{
    cv_node o_node;
};

/*

Macro: cv_list_initializer_

Description: Initializer list for cv_list structure.  This sets all members
to null pointer values.

*/
#define cv_list_initializer_ { cv_node_initializer_ }

/* see cv_list.c for more details. */
cv_bool cv_list_init(
    cv_list * p_this);

/* see cv_list.c for more details. */
void cv_list_cleanup(
    cv_list * p_this);

#endif /* #ifndef cv_list_h_ */

/* end-of-file: cv_list.h */
