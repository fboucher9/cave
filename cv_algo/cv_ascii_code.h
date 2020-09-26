/* See LICENSE for license details */

#ifndef cv_ascii_code_h_
#define cv_ascii_code_h_

#include <cv_algo/cv_ascii_pred.h>
#include <cv_misc/cv_types.h>
#include <cv_misc/cv_bool.h>

struct cv_ascii_code {
    char const * p_min;
    char const * p_max;
};

char const * cv_ascii_code_cast(void const * pc_void);
void cv_ascii_code_init(cv_ascii_code * p_this);
void cv_ascii_code_cleanup(cv_ascii_code * p_this);
void cv_ascii_code_set_text(cv_ascii_code * p_this, char const * p_text,
    cv_uptr i_max_len);
cv_uptr cv_ascii_code_len(cv_ascii_code const * p_this);

#endif /* #ifndef cv_ascii_code_h_ */

/* end-of-file: cv_ascii_code.h */
