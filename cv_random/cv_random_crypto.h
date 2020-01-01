/* See LICENSE for license details */

#ifndef cv_random_crypto_h_
#define cv_random_crypto_h_

/*
 *
 */

#include <cv_random/cv_random_pred.h>
#include <cv_file/cv_file_disk.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_random_crypto {
#if defined cv_linux_
    cv_file_disk o_file_disk;
#else /* #if defined cv_linux_ */
    void * p_void;
#endif /* #if defined cv_linux_ */
};

#if defined cv_linux_
#define cv_random_crypto_initializer_ { cv_file_disk_initializer_ }
#else /* #if defined cv_linux_ */
#define cv_random_crypto_initializer_ { 0 }
#endif /* #if defined cv_linux_ */

cv_bool cv_random_crypto_init(struct cv_random_crypto * p_this);
void cv_random_crypto_cleanup(struct cv_random_crypto * p_this);
unsigned long cv_random_crypto_pick( struct cv_random_crypto * p_this,
    unsigned long i_modulo);

#endif /* #ifndef cv_random_crypto_h_ */

/* end-of-file: cv_random_crypto.h */
