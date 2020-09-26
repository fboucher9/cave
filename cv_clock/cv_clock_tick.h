/* See LICENSE for license details */

#ifndef cv_clock_tick_h_
#define cv_clock_tick_h_

/*
 *
 */

/*
 *  Use of tick to accelerate realtime clock reading.
 *
 *  Read first tick sample
 *  Read first clock sample
 *  Read second tick sample
 *  Read second clock sample
 *  Evaluate tick frequency
 *  Extrapolate clock for intermediate points
 *  Read third tick sample
 *  Read third clock sample
 *  Extrapolate clock for third point
 *  Error is difference between clock sample and extrapolation
 *
 *      If Error is positive
 *          -   Means that frequency is too low.
 *          -   Old frequency, then current frequency
 *          -   Check if error is corrected by current frequency
 *          -   Take error and convert back to a frequency
 *      Else
 *          -   Means that frequency is too high.
 *
 *  tick_elapsed = tick_measured - tick_old
 *  clock_estimated = clock_old + ((tick_elapsed * 1sec) / freq_old)
 *  on new sample:
 *      clock_elapsed = clock_measured - clock_old
 *      clock_error = clock_measured - clock_estimated
 *      freq_new = ((tick_elapsed * 1sec) / clock_elapsed)
 *      if clock_elapsed < 90msec
 *          period_nsec = 10msec
 *      else if clock_elapsed < 900msec
 *          period_nsec = 100msec
 *      else
 *          period_nsec = 1000msec
 *      freq_period = ((freq_new * 1sec) / period_nsec)
 *      freq_error = ((clock_error * freq_new) / period_nsec)
 *      freq_old = freq_new + freq_error * smooth_factor
 *      if clock_elapsed >= 900msec
 *          clock_old = clock_estimated
 *          tick_old = tick_measured
 */

#include <cv_clock/cv_clock_pred.h>
#include <cv_clock/cv_clock.h>
#include <cv_misc/cv_bool.h>

/*
 *
 */

struct cv_clock_tick {
    cv_clock o_clock;
};

void cv_clock_tick_init( cv_clock_tick * p_this);
void cv_clock_tick_cleanup( cv_clock_tick * p_this);
cv_bool cv_clock_tick_is_supported(void);
cv_bool cv_clock_tick_read( cv_clock_tick * r_value);

#endif /* #ifndef cv_clock_tick_h_ */

/* end-of-file: cv_clock_tick.h */
