/* See LICENSE for license details */

#include <cv_algo/cv_ascii_code.h>
#include <cv_misc/cv_cast.h>
#include <cv_memory.h>

char const * cv_ascii_code_cast(void const * pc_void) {
    return cv_cast_(char const *)(pc_void);
}

void cv_ascii_code_init(cv_ascii_code * p_this) {
    p_this->p_min = 0;
    p_this->p_max = 0;
}

void cv_ascii_code_cleanup(cv_ascii_code * p_this) {
    (void)p_this;
}

void cv_ascii_code_set_text(cv_ascii_code * p_this, char const * p_text,
    cv_uptr i_max_len) {
    if (p_text) {
        p_this->p_min = p_text;
        p_this->p_max = p_text + cv_memory_find_0(p_text, i_max_len);
    } else {
        p_this->p_min = 0;
        p_this->p_max = 0;
    }
}

cv_uptr cv_ascii_code_len(cv_ascii_code const * p_this) {
    return cv_memory_len(p_this->p_min, p_this->p_max);
}

/* end-of-file: cv_ascii_code.c */
