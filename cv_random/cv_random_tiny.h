/* See LICENSE for license details */

#ifndef cv_random_tiny_h_
#define cv_random_tiny_h_

/*
 *
 */

#include <cv_random/cv_random_pred.h>
#include <cv_misc/cv_types.h>

struct cv_random_tiny {
    unsigned long status[4];
    unsigned long mat1;
    unsigned long mat2;
    unsigned long tmat;
    unsigned long l_pad[1];
};

void cv_random_tiny_init (cv_random_tiny * s, unsigned long seed);

void cv_random_tiny_cleanup(cv_random_tiny * s);

unsigned long cv_random_tiny_pick (cv_random_tiny * s, unsigned long modulo);

#endif /* #ifndef cv_random_tiny_h_ */

/* end-of-file: cv_random_tiny.h */
