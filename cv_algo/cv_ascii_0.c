/* See LICENSE for license details */

#include <cv_algo/cv_ascii_0.h>
#include <cv_algo/cv_ascii_code.h>
#include <cv_memory.h>

void cv_ascii_0_init(cv_ascii_0 * p_this) {
    cv_ascii_heap_init(&p_this->o_heap);
}

void cv_ascii_0_cleanup(cv_ascii_0 * p_this) {
    cv_ascii_heap_cleanup(&p_this->o_heap);
}

cv_bool cv_ascii_0_dup(cv_ascii_0 * p_this,
    cv_ascii_code const * p_ref) {
    cv_bool b_result = cv_false;
    if (p_ref) {
        cv_uptr const i_ref_len = cv_ascii_code_len(p_ref);
        if (cv_ascii_heap_resize(&p_this->o_heap, i_ref_len + 1)) {
            cv_memory_copy(p_this->o_heap.o_base.p_min,
                i_ref_len, p_ref->p_min, i_ref_len);
            p_this->o_heap.o_base.p_min[i_ref_len] = 0;
            b_result = cv_true;
        }
    } else {
        b_result = cv_ascii_heap_resize(&p_this->o_heap, 0);
    }
    return b_result;
}

/* end-of-file: cv_ascii_0.c */
