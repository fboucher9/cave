/* See LICENSE for license details */

#include <cv_random/cv_random_tiny.h>

static void cv_random_tiny_next_state (cv_random_tiny * p_this) {
    unsigned long x;
    unsigned long y;
    y = p_this->status[3];
    x = (p_this->status[0] & 0x7ffffffful)
        ^ p_this->status[1]
        ^ p_this->status[2];
    x ^= ((x << 1) & 0xfffffffful);
    y ^= (y >> 1) ^ x;
    p_this->status[0] = p_this->status[1];
    p_this->status[1] = p_this->status[2];
    p_this->status[2] = (x ^ (y << 10)) & 0xfffffffful;
    p_this->status[3] = y;
    if (y & 1) {
         p_this->status[1] ^= p_this->mat1;
         p_this->status[2] ^= p_this->mat2;
     }
}

static unsigned long cv_random_tiny_temper (cv_random_tiny * p_this) {
    unsigned long t0;
    unsigned long t1;
    t0 = p_this->status[3];
    t1 = p_this->status[0] + (p_this->status[2] >> 8);
    t0 ^= t1;
    t0 ^= (unsigned long)(-((signed long)(t1 & 1))) & p_this->tmat;
    return t0;
}

void cv_random_tiny_init (cv_random_tiny * p_this, unsigned long seed) {
    unsigned long i;
    p_this->status[0] = seed;
    p_this->status[1] = p_this->mat1 = 0x8f7011eeul;
    p_this->status[2] = p_this->mat2 = 0xfc78ff1ful;
    p_this->status[3] = p_this->tmat = 0x3793fdfful;
    for (i = 1; i < 8; i++) {
        p_this->status[i & 3] ^= 0xfffffffful & (i + (1812433253ul)
            * (p_this->status[(i - 1) & 3]
               ^ (p_this->status[(i - 1) & 3] >> 30)));
    }
    for (i = 0; i < 8; i++) {
        cv_random_tiny_next_state(p_this);
    }
}

void cv_random_tiny_cleanup(cv_random_tiny * p_this) {
    (void)p_this;
}

unsigned long cv_random_tiny_pick (cv_random_tiny * p_this,
    unsigned long modulo) {
    unsigned long i_value = 0;
    cv_random_tiny_next_state(p_this);
    i_value = cv_random_tiny_temper(p_this);
    if (modulo) {
        i_value = (i_value % modulo);
    }
    return i_value;
}

/* end-of-file: cv_random_tiny.c */
