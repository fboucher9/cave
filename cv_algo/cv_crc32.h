/* See LICENSE for license details */

#ifndef cv_crc32_h_
#define cv_crc32_h_

/*
 *
 */

#include <cv_algo/cv_crc32_pred.h>
#include <cv_algo/cv_array_pred.h>

/*
 *  Structure: cv_crc32
 *
 *  Descriptiion:  State for cv_crc32 parser.  Access to members is reserved
 *  to cv_crc32 implementation.
 *
 */

struct cv_crc32 {
    unsigned long a_private[2u];
}; /* struct cv_crc32 */

unsigned long cv_crc32_convert( struct cv_array const * p_buffer);
void cv_crc32_init(struct cv_crc32 * p_this);
void cv_crc32_cleanup(struct cv_crc32 * p_this);
void cv_crc32_write( struct cv_crc32 * p_this,
    struct cv_array const * p_buffer);
unsigned long cv_crc32_result( struct cv_crc32 const * p_this);

#endif /* #ifndef cv_crc32_h_ */

/* end-of-file: cv_crc32.h */
