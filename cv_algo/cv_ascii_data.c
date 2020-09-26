/* See LICENSE for license details */

#include <cv_algo/cv_ascii_data.h>
#include <cv_misc/cv_cast.h>
#include <cv_memory.h>

char * cv_ascii_data_cast(void * p_void) {
    return cv_cast_(char *)(p_void);
}

void cv_ascii_data_init(cv_ascii_data * p_this) {
    p_this->p_min = 0;
    p_this->p_max = 0;
}

void cv_ascii_data_cleanup(cv_ascii_data * p_this) {
    (void)p_this;
}

cv_uptr cv_ascii_data_len(cv_ascii_data const * p_this) {
    return cv_memory_len(p_this->p_min, p_this->p_max);
}

/* end-of-file: cv_ascii_data.c */
