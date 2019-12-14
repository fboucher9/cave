/* See LICENSE for license details */

#ifndef cv_function_h_
#define cv_function_h_

/*
 *  Module: cv_function.h
 *
 *  Description: Macro used to get current function name.  This macro may only
 *  be used from the body of a function, or else compilation may fail.  The
 *  macro may expands to code, not another macro so avoid doing any macro
 *  concatenation or stringify with the result of the macro.
 */

#include <cv_misc/cv_stringify.h>

#if defined __STDC_VERSION__ && (__STDC_VERSION__ >= 199901)
#define cv_function_ __func__
#elif defined __cplusplus && (__cplusplus >= 201103)
#define cv_function_ __func__
#else /* #if defined ... */
#define cv_function_ __FILE__ ":" cv_stringify_(__LINE__)
#endif /* #if defined ... */

#endif /* #ifndef cv_function_h_ */

/* end-of-file: cv_function.h */
