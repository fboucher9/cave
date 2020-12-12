/* See LICENSE for license details */

#ifndef cv_random_h_
#define cv_random_h_

/*
 *
 */

#include <cv_random/cv_random_pred.h>

/*
 *
 */

struct cv_random {
    unsigned long i_machine[3u];
    unsigned long l_padding[1u];
};

void cv_random_init( struct cv_random * p_this, unsigned long i_seed );
void cv_random_cleanup( struct cv_random * p_this );
unsigned long cv_random_pick( struct cv_random * p_this,
    unsigned long i_modulo);

#endif /* #ifndef cv_random_h_ */

/* end-of-file: cv_random.h */
