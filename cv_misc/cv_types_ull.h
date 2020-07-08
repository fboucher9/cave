/* See LICENSE for license details */

#ifndef cv_types_ull_h_
#define cv_types_ull_h_

/*
 *  Type: cv_ull
 *
 *  Description: Define an unsigned integer that has at least 64 bits.  The
 *  implementation may have more bits, but not less.
 *
 *  Comments: Even if the long type may be 64 bits on certain architectures
 *  we must still use the long long type.  Having different types for long
 *  and the cv_ull type enables extra warnings at compile-time.
 *
 *  The cv_typeof_ull_ may be defined from the makefiles for architectures
 *  that do not support the default detection method below.
 */

#if ! defined cv_typeof_ull_
#if defined __UINT64_TYPE__
#define cv_typeof_ull_ __UINT64_TYPE__
#elif ! defined __GNUC__ && defined _MSC_VER
#define cv_typeof_ull_ unsigned __int64
#elif defined cv_have_stdint_h_
#include <stdint.h>
#define cv_typeof_ull_ uint64_t
#else /* #if ... */
#define cv_typeof_ull_ unsigned long long
#endif /* #if ... */
#endif /* #if ! defined cv_typeof_ull_ */

#include <cv_misc/cv_warning_ll_ignore.h>
typedef cv_typeof_ull_ cv_ull;
#include <cv_misc/cv_warning_ll_restore.h>

/* Verify sizeof cv_ull */
typedef char cv_verify_sizeof_ull [
(sizeof(cv_ull) >= 8) ? 1 : -1 ];

#endif /* #ifndef cv_types_ull_h_ */

/* end-of-file: cv_types_ull.h */
