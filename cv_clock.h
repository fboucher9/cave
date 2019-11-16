/* See LICENSE for license details */

#ifndef cv_clock_h_
#define cv_clock_h_

#include <cv_clock_pred.h>

#include <cv_clock_epoch.h>

#include <cv_types.h>

struct cv_clock
{
    cv_ull i_freq;
    /* -- */
    cv_ull i_count;
    /* -- */
    cv_clock_epoch e_clock_epoch;
    int ui_padding[3u];
};

char cv_clock_read(
    cv_clock_epoch e_clock_epoch,
    cv_clock * p_value);

char cv_clock_sleep(
    cv_clock const * p_value);

char cv_clock_convert_freq(
    cv_clock * p_value,
    cv_ull i_freq);

char cv_clock_convert_epoch(
    cv_clock * p_value,
    cv_clock_epoch e_clock_epoch);

#endif /* #ifndef cv_clock_h_ */
