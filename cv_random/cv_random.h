/* See LICENSE for license details */

#ifndef cv_random_h_
#define cv_random_h_

/*
 *
 */

#include <cv_random/cv_random_pred.h>
#include <cv_misc/cv_types.h>

/*
 *
 */

struct cv_random {
    cv_ull i_machine;
};

void cv_random_init( struct cv_random * p_this, unsigned long i_seed );
void cv_random_cleanup( struct cv_random * p_this );
unsigned long cv_random_pick( struct cv_random * p_this,
    unsigned long i_modulo);

#endif /* #ifndef cv_random_h_ */

/* end-of-file: cv_random.h */
