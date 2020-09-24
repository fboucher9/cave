/* See LICENSE for license details */

#ifndef cv_memory_h_
#define cv_memory_h_

#include <cv_misc/cv_types.h>

void cv_memory_zero( void * p_buf, cv_uptr i_buf_len);

void cv_memory_fill( void * p_buf, cv_uptr i_buf_len,
    unsigned char c_value);

cv_uptr cv_memory_copy( void * p_dst, cv_uptr i_dst_len,
    void const * p_src, cv_uptr i_src_len);

cv_uptr cv_memory_find_0( void const * p_src, cv_uptr i_src_len);

int cv_memory_compare( void const * p_left, cv_uptr i_left_len,
    void const * p_right, cv_uptr i_right_len);

cv_uptr cv_memory_len( void const * p_min, void const * p_max);

#endif /* #ifndef cv_memory_h_ */
