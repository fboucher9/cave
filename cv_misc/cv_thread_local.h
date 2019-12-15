/* See LICENSE for license details */

#ifndef cv_thread_local_h_
#define cv_thread_local_h_

/*
 *
 */

#if ! defined cv_thread_local_
#if defined __GNUC__
#define cv_thread_local_ __thread
#elif defined _MSC_VER
#define cv_thread_local_ __declspec(thread)
#else /* #if defined ... */
#define cv_thread_local_ __thread
#endif /* #if defined ... */
#endif /* #if ! defined cv_thread_local_ */

#endif /* #ifndef cv_thread_local_h_ */

/* end-of-file: cv_thread_local.h */
