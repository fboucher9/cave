/* See LICENSE for license details */

#ifndef cv_json_node_h_
#define cv_json_node_h_

/*
 *
 */

#include <cv_json/cv_json_pred.h>
#include <cv_algo/cv_list_node.h>
#include <cv_algo/cv_list_root.h>
#include <cv_algo/cv_array.h>

/*
 *
 */

struct cv_json {
    cv_list_node o_node;
    /* -- */
    cv_list_root o_root;
    /* -- */
    cv_array o_label;
    /* -- */
    cv_array o_string;
    /* -- */
    double i_number;
    /* -- */
    unsigned e_type;
    int i_padding[3u];
};

#endif /* #ifndef cv_json_node_h_ */

/* end-of-file: cv_json_node.h */
