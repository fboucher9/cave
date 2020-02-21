/* See LICENSE for license details */

#ifndef cv_chunk_h_
#define cv_chunk_h_

/*
 *  Module: cv_chunk.h
 *
 *  Description: List of arrays.  Storage for string of unknown length.  Since
 *  the maximum length is not known, the string is split into smaller chunks.
 *  Application may then combine the chunk into a single buffer.
 */

#include <cv_algo/cv_chunk_pred.h>
#include <cv_algo/cv_list_root.h>
#include <cv_misc/cv_bool.h>
#include <cv_misc/cv_types.h>
#include <cv_algo/cv_array_pred.h>

/*
 *
 */

struct cv_chunk_root {
    cv_list_root o_root;
    cv_uptr i_total_len;
};

void cv_chunk_root_init(cv_chunk_root * p_this);
void cv_chunk_root_cleanup(cv_chunk_root * p_this);
void cv_chunk_root_empty(cv_chunk_root * p_this);
cv_bool cv_chunk_root_write_char( cv_chunk_root * p_this,
    unsigned char i_value);
cv_bool cv_chunk_root_write_array(cv_chunk_root * p_this,
    cv_array const * p_array);
cv_uptr cv_chunk_root_len(cv_chunk_root const * p_this);
void cv_chunk_root_read(cv_chunk_root const * p_this,
    cv_array_it * p_array_it);

#endif /* #ifndef cv_chunk_h_ */

/* end-of-file: cv_chunk.h */
