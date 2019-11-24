/* See LICENSE for license details */

#ifndef cv_runtime_h_
#define cv_runtime_h_

void * cv_runtime_malloc(
    long i_malloc_len);

void cv_runtime_free(
    void * p_buffer);

#if defined __GNUC__
__attribute__((format(printf, 1, 2)))
#endif /* #if defined __GNUC__ */
void cv_runtime_printf(
    char const * p_format0,
    ...);

#endif /* #ifndef cv_runtime_h_ */

void cv_runtime_memset(
    void * p_buf,
    unsigned char c_fill_value,
    long i_buf_len);

void cv_runtime_memcpy(
    void * p_dst,
    void const * p_src,
    long i_copy_len);

void const * cv_runtime_memchr(
    void const * p_src,
    unsigned char c_value,
    long i_src_len);

/* end-of-file: cv_runtime.h */
