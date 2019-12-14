/* See LICENSE for license details */

#ifndef cv_stringify_h_
#define cv_stringify_h_

/*
 *  Module: cv_stringify.h
 *
 *  Description: Macro to convert argument to a literal string.  The double
 *  macro trick is used to expand the argument before conversion.
 */

#define cv_stringify_(x) xx_stringify_(x)
#define xx_stringify_(x) #x

#endif /* #ifndef cv_stringify_h_ */

/* end-of-file: cv_stringify.h */
