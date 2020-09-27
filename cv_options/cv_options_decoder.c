/* See LICENSE for license details */

/*
 *
 */

#include <cv_options/cv_options_decoder.h>
#include <cv_options/cv_options.h>
#include <cv_algo/cv_array_it.h>
#include <cv_debug/cv_debug.h>
#include <cv_algo/cv_array_heap.h>

cv_debug_decl_(g_options_decoder, "cv_options_decoder");

/*
 *
 */

void cv_options_decoder_init( cv_options_decoder * p_this ) {
    cv_debug_construct_(g_options_decoder, p_this);
    cv_chunk_root_init(&p_this->o_chunk_root);
}

/*
 *
 */

void cv_options_decoder_cleanup( cv_options_decoder * p_this ) {
    cv_chunk_root_cleanup(&p_this->o_chunk_root);
    cv_debug_destruct_(g_options_decoder, p_this);
}

/*
 *
 */

static cv_bool cv_options_decoder_flush( cv_options_decoder * p_this,
    cv_options * p_options) {
    cv_bool b_result = cv_true;
    cv_uptr const i_word_len = cv_chunk_root_len(&p_this->o_chunk_root);
    if (i_word_len) {
        /* Allocate memory for a word */
        cv_array_heap o_buffer = {0};
        /* Use cv_array_heap */
        if (cv_array_heap_init(&o_buffer, i_word_len, 0)) {
            /* fill in the array using chunk list */
            /* ... */
            b_result = cv_options_add(p_options, &o_buffer.o_array);
            cv_array_heap_cleanup(&o_buffer);
        } else {
            b_result = cv_false;
        }
    } else {
        b_result = cv_true;
    }
    cv_chunk_root_empty(&p_this->o_chunk_root);
    return b_result;
}

/*
 *
 */

cv_bool cv_options_decoder_write_char( cv_options_decoder * p_this,
    unsigned char c_input, cv_options * p_options) {
    cv_bool b_result = cv_true;
    if (p_this->b_white_space) {
        if (' ' == c_input) {
        } else {
            /* begin a new word */
            b_result = cv_chunk_root_write_char(&p_this->o_chunk_root, c_input);
            if (b_result) {
                p_this->b_white_space = cv_false;
            }
        }
    } else {
        if (' ' == c_input) {
            b_result = cv_options_decoder_flush(p_this, p_options);
            p_this->b_white_space = cv_true;
        } else {
            b_result = cv_chunk_root_write_char(
                &p_this->o_chunk_root, c_input);
        }
    }
    return b_result;
}

/*
 *
 */

cv_bool cv_options_decoder_write_array( cv_options_decoder * p_this,
    cv_array const * p_input, cv_options * p_options) {
    cv_bool b_result = cv_true;
    unsigned char c_input = 0;
    cv_array_it o_array_it = {0};
    cv_array_it_init(&o_array_it, p_input);
    while (b_result && cv_array_it_read_next_char(&o_array_it, &c_input)) {
        b_result = cv_options_decoder_write_char(p_this, c_input, p_options);
    }
    cv_array_it_cleanup(&o_array_it);
    return b_result;
}

