/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_unique.h>

/*
 *
 */

void cv_unique_init( cv_unique * p_this ) {
    p_this->p_class = 0;
    p_this->i_instance = 0;
}

/*
 *
 */

void cv_unique_cleanup( cv_unique * p_this) {
    (void)p_this;
}

/*
 *
 */

void cv_unique_set( cv_unique * p_this, char const * p_class,
    cv_uptr i_instance) {
    p_this->p_class = p_class;
    p_this->i_instance = i_instance;
}

/*
 *
 */

void cv_unique_copy( cv_unique * p_this, cv_unique const * p_ref) {
    if (p_ref) {
        cv_unique_set(p_this, p_ref->p_class, p_ref->i_instance);
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
