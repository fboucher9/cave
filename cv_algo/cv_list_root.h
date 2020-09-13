/* See LICENSE for license details */

#ifndef cv_list_root_h_
#define cv_list_root_h_

/*

Module: cv_list_root.h

Description: Root of linked list.  Contains pointers to first and last
elements.

*/

#include <cv_algo/cv_list_pred.h>

#include <cv_algo/cv_list_node.h>

#include <cv_misc/cv_bool.h>

/*

Structure: cv_list_root

Description: Members of cv_list_root object.  Implementation uses a node since a
node has two pointers.  Also the node functions may be used on the root.

*/
struct cv_list_root
{
    cv_list_node o_node;
};

/* see cv_list_root.c for more details. */
void cv_list_root_init(
    cv_list_root * p_this);

/* see cv_list_root.c for more details. */
void cv_list_root_cleanup(
    cv_list_root * p_this);

void cv_list_root_append(
    cv_list_root * p_this,
    cv_list_node * p_node);

void cv_list_root_prepend(
    cv_list_root * p_this,
    cv_list_node * p_node);

#endif /* #ifndef cv_list_root_h_ */

/* end-of-file: cv_list_root.h */
