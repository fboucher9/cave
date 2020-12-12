/* See LICENSE for license details */

/*
 *
 */

#include <cv_random/cv_random.h>
#include <cv_debug/cv_debug.h>

cv_debug_decl_(cv_random_class, "cv_random", sizeof(struct cv_random));

/*
 *
 */

void cv_random_init( struct cv_random * p_this, unsigned long i_seed ) {
    cv_debug_assert_(p_this, cv_debug_code_null_ptr);
    cv_debug_construct_(cv_random_class, p_this);
    p_this->i_machine[0u] = i_seed;
    p_this->i_machine[1u] = i_seed;
    p_this->i_machine[2u] = i_seed;
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
    p_this->i_machine[0u] =
        ( ( p_this->i_machine[0u] * 1103515245ul) + 12345ul);
    p_this->i_machine[1u] =
        ( ( p_this->i_machine[1u] * 1103515245ul) + 12345ul);
    p_this->i_machine[2u] =
        ( ( p_this->i_machine[2u] * 1103515245ul) + 12345ul);
    i_value = ((p_this->i_machine[0u] >> 18u) & 0x000003FFul)
        | ((p_this->i_machine[1u] >> 8u) & 0x000FFC00ul)
        | ((p_this->i_machine[2u] << 2u) & 0xFFF00000ul);
    if ( i_modulo) {
        i_value = ( i_value % i_modulo);
    }
    return i_value;
}

/* end-of-file: cv_random.c */
