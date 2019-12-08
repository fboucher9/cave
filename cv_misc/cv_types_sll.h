/* See LICENSE for license details */

#ifndef cv_types_sll_h_
#define cv_types_sll_h_

/*
 *  Type: cv_sll
 *
 *  Description: Define a signed integer that has at least 64 bits.  The
 *  implementation may have more bits, but not less.
 *
 *  Comments: Even if the long type may be 64 bits on certain architectures we
 *  must still use the long long type.  Having different types for long and the
 *  cv_sll type enables extra warnings at compile-time.
 *
 *  The cv_typeof_sll_ may be defined from the makefiles for architectures that
 *  do not support the default detection method below.
 */

#if ! defined cv_typeof_sll_
#if ! defined __GNUC__ && defined _MSC_VER
#define cv_typeof_sll_ signed __int64
#else /* #if ... */
#define cv_typeof_sll_ signed long long
#endif /* #if ... */
#endif /* #if ! defined cv_typeof_sll_ */

#include <cv_misc/cv_warning_ll_ignore.h>
typedef cv_typeof_sll_ cv_sll;
#include <cv_misc/cv_warning_ll_restore.h>

/* Verify sizeof cv_sll */
typedef char cv_verify_sizeof_sll [
(sizeof(cv_sll) >= 8) ? 1 : -1 ];

#endif /* #ifndef cv_typeof_sll_h_ */

/* end-of-file: cv_types_sll.h */
