/* See LICENSE for license details */

#ifndef cv_bool_h_
#define cv_bool_h_

#if defined __cplusplus

#define cv_false_ (false)

#define cv_true_ (true)

typedef bool cv_bool;

#else /* #if defined __cplusplus */

#define cv_false_ (0)

#define cv_true_ (1)

typedef unsigned char cv_bool;

#endif /* #if defined __cplusplus */

#endif /* #ifndef cv_bool_h_ */

/* end-of-file: cv_bool.h */
