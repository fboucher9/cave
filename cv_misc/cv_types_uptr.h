/* See LICENSE for license details */

#ifndef cv_types_uptr_h_
#define cv_types_uptr_h_

/*
 *  Type: cv_uptr
 *
 *  Description: Define an unsigned integer with the same size as a pointer.
 *  This type is compatible with sizeof() operator.
 *
 *  Comments: For architectures that do not supply the __SIZE_TYPE__ macro and
 *  requires a type different than long, then define the cv_typeof_uptr_ macro
 *  from the makefiles.
 */

#if ! defined cv_typeof_uptr_
#if defined __SIZE_TYPE__
#define cv_typeof_uptr_ __SIZE_TYPE__
#elif ! defined __GNUC__ && defined _MSC_VER && defined _WIN64
#define cv_typeof_uptr_ unsigned __int64
#elif ! defined __GNUC__ && defined _MSC_VER && ! defined _WIN64
#define cv_typeof_uptr_ unsigned __int32
#elif defined cv_have_stddef_h_
#include <stddef.h>
#define cv_typeof_uptr_ size_t
#else /* #if defined __SIZE_TYPE__ */
#define cv_typeof_uptr_ unsigned long
#endif /* #if defined __SIZE_TYPE__ */
#endif /* #if ! defined cv_typeof_uptr_ */

#include <cv_misc/cv_warning_ll_ignore.h>
typedef cv_typeof_uptr_ cv_uptr;
#include <cv_misc/cv_warning_ll_restore.h>

/* Verify sizeof the cv_uptr type */
typedef char cv_verify_sizeof_uptr [
(sizeof(cv_uptr) == sizeof(void *)) ? 1 : -1];

#endif /* #ifndef cv_types_uptr_h_ */

/* end-of-file: cv_types_uptr.h */
