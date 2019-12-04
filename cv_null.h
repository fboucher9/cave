/* See LICENSE for license details */

#ifndef cv_null_h_
#define cv_null_h_

/*

Define macro for null pointer.  This is required to cast zero to a pointer
type.  If the compiler is cplusplus then zero may be used directly.  If the
compiler is C, then zero must be casted to void* and then C compiler allows
cast from void* to all other pointer types.

*/

#if ! defined cv_null_
#if defined __cplusplus
#define cv_null_ (0)
#else /* #if defined __cplusplus */
#define cv_null_ ((void*)0)
#endif /* #if defined __cplusplus */
#endif /* #if ! defined cv_null_ */

#endif /* #ifndef cv_null_h_ */
