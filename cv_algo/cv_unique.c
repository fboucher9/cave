/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_unique.h>

/*
 *
 */

void cv_unique_init( cv_unique * p_this ) {
    cv_array_init(&p_this->o_class);
    p_this->i_instance = 0;
}

/*
 *
 */

void cv_unique_cleanup( cv_unique * p_this) {
    cv_array_cleanup(&p_this->o_class);
}

/*
 *
 */

void cv_unique_set( cv_unique * p_this, cv_array const * p_class,
    cv_ull i_instance) {
    if (p_class) {
        p_this->o_class = *p_class;
    } else {
        p_this->o_class.o_min.pc_void = 0;
        p_this->o_class.o_max.pc_void = 0;
    }
    p_this->i_instance = i_instance;
}

/*
 *
 */

void cv_unique_copy( cv_unique * p_this, cv_unique const * p_ref) {
    if (p_ref) {
        cv_unique_set(p_this, &(p_ref->o_class), p_ref->i_instance);
    } else {
        cv_unique_set(p_this, 0, 0);
    }
}

/*
 *
 */

void cv_unique_next( cv_unique * p_this) {
    p_this->i_instance ++;
}

/* end-of-file: cv_unique.c */
