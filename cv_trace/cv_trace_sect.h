/* See LICENSE for license details */

#ifndef cv_trace_sect_h_
#define cv_trace_sect_h_

/*
 *
 */

#include <cv_trace/cv_trace_pred.h>
#include <cv_algo/cv_array.h>
#include <cv_misc/cv_types.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_trace_sect {
    cv_array o_name;
    /* -- */
    cv_array o_region;
    /* -- */
    cv_array o_iterator;
    /* -- */
    cv_bool b_echo;
    char c_padding[7u];
};

void cv_trace_sect_init( cv_trace_sect * p_this,
    cv_array const * p_name, cv_array const * p_region, cv_bool b_echo);
void cv_trace_sect_cleanup( cv_trace_sect * p_this);
void cv_trace_sect_begin( cv_trace_sect * p_this);
void cv_trace_sect_print( cv_array const * p_array);
void cv_trace_sect_end(void);

#endif /* #ifndef cv_trace_sect_h_ */

/* end-of-file: cv_trace_sect.h */
