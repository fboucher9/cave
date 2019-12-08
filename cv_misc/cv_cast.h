/* See LICENSE for license details */

#ifndef cv_cast_h_
#define cv_cast_h_

/*

Define a macro to cast an expression to given type.  Why use a macro?  Because
the macro allows us to use different methods depending on compiler.  The C++
implementation uses static_cast<> operator so the compiler will detect more
warnings.

Note: for cases that would require a C++ reinterpret_cast<> operator, then
do not use the cv_cast_ macro and use directly a C-style cast.

*/

#if ! defined cv_cast_
#if defined __cplusplus
#define cv_cast_(type, expr) \
    (static_cast<type>(expr))
#else /* #if defined __cplusplus */
#define cv_cast_(type, expr) \
    ((type)(expr))
#endif /* #if defined __cplusplus */
#endif /* #if ! defined cv_cast_ */

#endif /* #ifndef cv_cast_h_ */
