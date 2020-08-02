/* See LICENSE for license details */

#ifndef cv_json_ptr_h_
#define cv_json_ptr_h_

/*
 *
 */

#include <cv_json/cv_json_pred.h>
#include <cv_algo/cv_list_ptr.h>

/*
 *
 */

union cv_json_ptr {
    void const * pc_void;
    void * p_void;
    cv_json const * pc_value;
    cv_json * p_value;
    cv_list_ptr o_list_ptr;
};

#endif /* #ifndef cv_json_ptr_h_ */

/* end-of-file: cv_json_ptr.h */
