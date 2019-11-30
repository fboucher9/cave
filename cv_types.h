/* See LICENSE for license details */

#ifndef cv_types_h_
#define cv_types_h_

/*
 *  Module: cv_types.h
 *
 *  Description: Define types that require compiler-specific extensions, any
 *  type that is possibly defined with a long long int.  The long long type is
 *  not standard so it must not be used directly.  This file does all the
 *  compiler-specific magic to silence the warnings.
 *
 *  Comments: The _t suffix typically used with this kind of definition is
 *  ommited because the _t suffix is reserved for use by POSIX standard.
 */

#include <cv_types_uptr.h>

#include <cv_types_sptr.h>

#include <cv_types_ull.h>

#include <cv_types_sll.h>

#endif /* #ifndef cv_types_h_ */
