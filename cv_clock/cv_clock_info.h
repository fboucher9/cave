/* See LICENSE for license details */

#ifndef cv_clock_info_h_
#define cv_clock_info_h_

/*
 *
 */

#include <cv_clock/cv_clock_pred.h>

/*
 *
 */

struct cv_clock_info {
    struct cv_clock_date_info {
        short i_year; /* 2019 */
        short i_month; /* 1-12 */
        short i_day_of_month; /* 1-31 */
        short s_padding1[1u];
    } o_date;
    /* -- */
    struct cv_clock_time_info {
        short i_hour; /* 0-23 */
        short i_minute; /* 0-59 */
        short i_second; /* 0-59 */
        short s_padding2[1u];
        /* -- */
        unsigned long i_fraction;
        unsigned long l_padding[1u];
    } o_time;
};

#define cv_clock_info_initializer_ \
{ { 0, 0, 0, {0} }, { 0, 0, 0, {0}, 0, {0} } }

#endif /* #ifndef cv_clock_info_h_ */

/* end-of-file: cv_clock_pred.h */
