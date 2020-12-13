/* See LICENSE for license details */

/*
 *
 */

#include <cv_random/cv_random.h>
#include <cv_debug/cv_debug.h>
#include <cv_misc/cv_cast.h>

cv_debug_decl_(cv_random_class, "cv_random", sizeof(struct cv_random));

/*
 *
 */

void cv_random_init( struct cv_random * p_this, unsigned long i_seed ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(cv_random_class, p_this);
    p_this->i_machine = i_seed;
}

/*
 *
 */

void cv_random_cleanup( struct cv_random * p_this ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_destruct_(cv_random_class, p_this);
}

/*
 *
 */

unsigned long cv_random_pick( struct cv_random * p_this,
    unsigned long i_modulo) {
    unsigned long i_value = 0;
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);

    {
        cv_ull const oldstate = p_this->i_machine;

        /* LCG */
        p_this->i_machine =
            oldstate *
            ((cv_cast_(cv_ull)(0x5851f42dul) << 32u) +
                (cv_cast_(cv_ull)(0x4c957f2dul))) +
            ((cv_cast_(cv_ull)(0x14057b7eul) << 32u) +
                (cv_cast_(cv_ull)(0xf767814ful))) ;

        /* PCG-XSH-RR */
        {
            unsigned long const xorshifted = cv_cast_(unsigned long)(
                ((oldstate >> 18u) ^ oldstate) >> 27u);

            unsigned int const rot = cv_cast_(unsigned int)(
                oldstate >> 59u);

            i_value = cv_cast_(unsigned long)(
                (xorshifted >> rot) | (xorshifted << ((-rot) & 31)));
        }

        if ( i_modulo) {
            i_value = ( i_value % i_modulo);
        }
    }

    return i_value;
}

/* end-of-file: cv_random.c */
