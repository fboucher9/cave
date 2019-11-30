/* See LICENSE for license details */

#ifndef cv_list_root_h_
#define cv_list_root_h_

/*

Module: cv_list_root.h

Description: Root of linked list.  Contains pointers to first and last
elements.

*/

#include <cv_list_pred.h>

#include <cv_list_node.h>

#include <cv_bool.h>

/*

Structure: cv_list_root

Description: Members of cv_list_root object.  Implementation uses a node since a
node has two pointers.  Also the node functions may be used on the root.

*/
struct cv_list_root
{
    cv_list_node o_node;
};

/*

Macro: cv_list_root_initializer_

Description: Initializer list for cv_list_root structure.  This sets all members
to null pointer values.

*/
#define cv_list_root_initializer_ { cv_list_node_initializer_ }

/* see cv_list_root.c for more details. */
void cv_list_root_init(
    cv_list_root * p_this);

/* see cv_list_root.c for more details. */
void cv_list_root_cleanup(
    cv_list_root * p_this);

#endif /* #ifndef cv_list_root_h_ */

/* end-of-file: cv_list_root.h */
