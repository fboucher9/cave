/* See LICENSE for license details */

#include <cv_algo/cv_ascii_heap.h>
#include <cv_algo/cv_ascii_code.h>
#include <cv_heap/cv_heap.h>
#include <cv_memory.h>
#include <cv_algo/cv_unique.h>

void cv_ascii_heap_init(cv_ascii_heap * p_this) {
    cv_ascii_data_init(&p_this->o_base);
}

void cv_ascii_heap_cleanup(cv_ascii_heap * p_this) {
    cv_ascii_heap_resize(p_this, 0);
    cv_ascii_data_cleanup(&p_this->o_base);
}

cv_bool cv_ascii_heap_resize(cv_ascii_heap * p_this,
    cv_uptr i_len) {
    cv_bool b_result = cv_false;
    if (p_this->o_base.p_min) {
        cv_heap_free(p_this->o_base.p_min);
        p_this->o_base.p_min = 0;
        p_this->o_base.p_max = 0;
    }
    if (i_len) {
        static unsigned char const a_ascii_heap_class[] = {
            'a', 's', 'c', 'i', 'i', '_', 'h', 'e', 'a', 'p'
        };
        static cv_unique g_ascii_heap_unique =
            cv_unique_initializer_(a_ascii_heap_class);
        void * p_placement = 0;
        cv_unique_next(&g_ascii_heap_unique);
        p_placement = cv_heap_alloc(i_len, &g_ascii_heap_unique);
        if (p_placement) {
            p_this->o_base.p_min = cv_ascii_data_cast(p_placement);
            p_this->o_base.p_max = p_this->o_base.p_min + i_len;
            b_result = cv_true;
        }
    } else {
        b_result = cv_true;
    }
    return b_result;
}

cv_bool cv_ascii_heap_dup(cv_ascii_heap * p_this,
    cv_ascii_code const * p_ref) {
    cv_bool b_result = cv_false;
    if (p_ref) {
        cv_uptr const i_ref_len = cv_ascii_code_len(p_ref);
        if (cv_ascii_heap_resize(p_this, i_ref_len)) {
            if (i_ref_len) {
                cv_memory_copy(p_this->o_base.p_min, i_ref_len,
                    p_ref->p_min, i_ref_len);
            }
            b_result = cv_true;
        }
    } else {
        cv_ascii_heap_resize(p_this, 0);
        b_result = cv_true;
    }
    return b_result;
}

cv_uptr cv_ascii_heap_len(cv_ascii_heap const * p_this) {
    return cv_ascii_data_len(&p_this->o_base);
}

/* end-of-file: cv_ascii_heap.c */
