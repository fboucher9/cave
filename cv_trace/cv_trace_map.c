/* See LICENSE for license details */

/*
 *
 */

#include <cv_trace/cv_trace_map.h>
#include <cv_heap/cv_heap.h>
#include <cv_debug/cv_debug.h>
#include <cv_runtime.h>

cv_debug_decl_(cv_trace_map_class, "cv_trace_map");

/*
 *
 */

cv_bool cv_trace_map_init( cv_trace_map * p_this,
    cv_array const * p_name, cv_uptr i_length) {
    cv_bool b_result = cv_false;
    (void)p_name;
    cv_debug_construct_(cv_trace_map_class, p_this);
    cv_array_init(&p_this->o_total_region);
    cv_array_init(&p_this->o_avail_region);
    p_this->o_total_region.o_min.p_void = cv_runtime_malloc(i_length);
    if (p_this->o_total_region.o_min.p_void) {
        p_this->o_total_region.o_max.pc_uchar =
            p_this->o_total_region.o_min.pc_uchar + i_length;
        p_this->o_avail_region = p_this->o_total_region;
        b_result = cv_true;
    }
    if (!b_result) {
        cv_array_cleanup(&p_this->o_avail_region);
        cv_array_cleanup(&p_this->o_total_region);
    }
    return b_result;
}

/*
 *
 */

void cv_trace_map_cleanup( cv_trace_map * p_this ) {
    cv_array_cleanup(&p_this->o_avail_region);
    cv_array_cleanup(&p_this->o_total_region);
    cv_debug_destruct_(cv_trace_map_class, p_this);
}

/*
 *
 */

void * cv_trace_map_alloc( cv_trace_map * p_this, cv_uptr i_length) {
    void * p_buffer = 0;
    if ((p_this->o_avail_region.o_min.pc_uchar + i_length) <=
        p_this->o_avail_region.o_max.pc_uchar) {
        p_buffer = p_this->o_avail_region.o_min.p_void;
        p_this->o_avail_region.o_min.pc_uchar += i_length;
    } else {
    }
    return p_buffer;
}

/* end-of-file: cv_trace_map.c */
