/* See LICENSE for license details */

#include <cv_algo/cv_ascii_tool.h>
#include <cv_algo/cv_ascii_data.h>
#include <cv_algo/cv_ascii_code.h>
#include <cv_misc/cv_cast.h>
#include <cv_memory.h>

cv_bool cv_ascii_compare( cv_ascii_code const * p_left,
    cv_ascii_code const * p_right) {
    cv_bool b_result = cv_false;
    if (0 == cv_memory_compare( p_left->p_min, cv_ascii_code_len(p_left),
            p_right->p_min, cv_ascii_code_len(p_right))) {
        b_result = cv_true;
    }
    return b_result;
}

void cv_ascii_zero( cv_ascii_data const * p_this) {
    cv_memory_zero(p_this->p_min, cv_ascii_data_len(p_this));
}

void cv_ascii_fill( cv_ascii_data const * p_this, char c_value) {
    unsigned char const uc_value = cv_cast_(unsigned char)(c_value);
    cv_memory_fill(p_this->p_min, cv_ascii_data_len(p_this), uc_value);
}

void cv_ascii_copy( cv_ascii_data const * p_left,
    cv_ascii_code const * p_right) {
    cv_memory_copy(p_left->p_min, cv_ascii_data_len(p_left), p_right->p_min,
        cv_ascii_code_len(p_right));
}

/* end-of-file: cv_ascii_tool.c */
