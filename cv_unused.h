/* See LICENSE for license details */

#ifndef cv_unused_h_
#define cv_unused_h_

/*

Define macro to quiet warnings related to unused parameter or unused variables.
The macro casts the expression to void.

*/

#if ! defined cv_unused_
#define cv_unused_(expr) ((void)(expr))
#endif /* #if ! defined cv_unused_ */

#endif /* #ifndef cv_unused_h_ */
