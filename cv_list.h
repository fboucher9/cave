/* See LICENSE for license details */

#ifndef cv_list_h_
#define cv_list_h_

/*

*/

#include <cv_node_pred.h>

#include <cv_node.h>

struct cv_list
{
    cv_node o_node;
};

#define cv_list_initializer_ { cv_node_initializer_ }

char cv_list_init(
    cv_list * p_this);

void cv_list_cleanup(
    cv_list * p_this);

#endif /* #ifndef cv_list_h_ */

/* end-of-file: cv_list.h */
