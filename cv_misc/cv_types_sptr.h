/* See LICENSE for license details */

#ifndef cv_types_sptr_h_
#define cv_types_sptr_h_

/*
 *  Type: cv_sptr
 *
 *  Description: Define a signed integer with same size as a pointer.  This
 *  type is compatible with ptrdiff_t type.
 *
 *  Comments: For architectures that do not supply the __PTRDIFF_TYPE__ macro
 *  and requires a type different than long, then define the cv_typeof_sptr_
 *  macro from the makefiles.
 */

#if ! defined cv_typeof_sptr_
#if defined __PTRDIFF_TYPE__
#define cv_typeof_sptr_ __PTRDIFF_TYPE__
#elif ! defined __GNUC__ && defined _MSC_VER && defined _WIN64
#define cv_typeof_sptr_ signed __int64
#elif ! defined __GNUC__ && defined _MSC_VER && ! defined _WIN64
#define cv_typeof_sptr_ signed __int32
#elif defined cv_have_stddef_h_
#include <stddef.h>
#define cv_typeof_sptr_ ptrdiff_t
#else /* #if ... */
#define cv_typeof_sptr_ signed long
#endif /* #if ... */
#endif /* #if ! defined cv_typeof_sptr_ */

#include <cv_misc/cv_warning_ll_ignore.h>
typedef cv_typeof_sptr_ cv_sptr;
#include <cv_misc/cv_warning_ll_restore.h>

/* Verify sizeof the cv_sptr type */
typedef char cv_verify_sizeof_sptr [
(sizeof(cv_sptr) == sizeof(void *)) ? 1 : -1];

#endif /* #ifndef cv_types_sptr_h_ */

/* end-of-file: cv_types_sptr.h */
