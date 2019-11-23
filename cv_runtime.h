/* See LICENSE for license details */

#ifndef cv_runtime_h_
#define cv_runtime_h_

void * cv_runtime_malloc(
    long const i_malloc_len);

void cv_runtime_free(
    void * p_buffer);

#if defined __GNUC__
__attribute__((format(printf, 1, 2)))
#endif /* #if defined __GNUC__ */
void cv_runtime_printf(
    char const * p_format0,
    ...);

#endif /* #ifndef cv_runtime_h_ */

/* end-of-file: cv_runtime.h */
