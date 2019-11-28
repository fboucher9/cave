/* See LICENSE for license details */

#ifndef cv_memory_h_
#define cv_memory_h_

void cv_memory_zero(
    void * p_buf,
    long i_buf_len);

long cv_memory_copy(
    void * p_dst,
    long i_dst_len,
    void const * p_src,
    long i_src_len);

long cv_memory_find_0(
    void const * p_src,
    long i_src_len);

int cv_memory_compare(
    void const * p_left,
    long i_left_len,
    void const * p_right,
    long i_right_len);

#endif /* #ifndef cv_memory_h_ */
