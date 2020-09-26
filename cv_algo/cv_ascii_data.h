/* See LICENSE for license details */

#ifndef cv_ascii_data_h_
#define cv_ascii_data_h_

#include <cv_algo/cv_ascii_pred.h>
#include <cv_misc/cv_types.h>
#include <cv_misc/cv_bool.h>

struct cv_ascii_data {
    char * p_min;
    char * p_max;
};

char * cv_ascii_data_cast(void * p_void);
void cv_ascii_data_init(cv_ascii_data * p_this);
void cv_ascii_data_cleanup(cv_ascii_data * p_this);
cv_uptr cv_ascii_data_len(cv_ascii_data const * p_this);

#endif /* #ifndef cv_ascii_data_h_ */

/* end-of-file: cv_ascii_data.h */
