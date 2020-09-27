/* See LICENSE for license details */

#ifndef cv_unique_h_
#define cv_unique_h_

/*
 *
 */

#include <cv_algo/cv_unique_pred.h>
#include <cv_misc/cv_types.h>
#include <cv_algo/cv_array.h>

/*
 *
 */

struct cv_unique {
    cv_array o_class;
    /* -- */
    cv_ull i_instance;
};

#define cv_unique_initializer_(a_text) \
{ cv_array_initializer_((a_text), (a_text) + sizeof(a_text)), 0 }

/*
 *
 */

void cv_unique_init( cv_unique * p_this );
void cv_unique_cleanup( cv_unique * p_this);
void cv_unique_set( cv_unique * p_this, cv_array const * p_class,
    cv_ull i_instance);
void cv_unique_copy( cv_unique * p_this, cv_unique const * p_ref);
void cv_unique_next( cv_unique * p_this);

#endif /* #ifndef cv_unique_h_ */

/* end-of-file: cv_unique.h */
