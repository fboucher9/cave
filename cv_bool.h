/* See LICENSE for license details */

#ifndef cv_bool_h_
#define cv_bool_h_

enum cv_bool_values
{
    cv_false = 0,

    cv_true = 1

};

#if defined __cplusplus

typedef bool cv_bool;

#else /* #if defined __cplusplus */

typedef unsigned char cv_bool;

#endif /* #if defined __cplusplus */

#endif /* #ifndef cv_bool_h_ */

/* end-of-file: cv_bool.h */
