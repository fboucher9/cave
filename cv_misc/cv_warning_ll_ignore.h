/* See LICENSE for license details */

/*
 *  Module: cv_warning_ll_ignore.h
 *
 *  Description: This is a macro include, it may be included several times so
 *  no include guard.
 */

/* Temporarily disable warnings for use of long long type */
/* The gcc pragma is also recognized by clang */
#if defined __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wlong-long"
#endif /* #if defined __GNUC__ */

/* end-of-file: cv_warning_ll_ignore.h */
