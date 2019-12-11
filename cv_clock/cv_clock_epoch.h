/* See LICENSE for license details */

#ifndef cv_clock_epoch_h_
#define cv_clock_epoch_h_

/*
 *
 */

typedef enum cv_clock_epoch {
    cv_clock_epoch_invalid = 0,
    /* */
    cv_clock_epoch_duration,
    /* */
    cv_clock_epoch_mono,
    /* */
    cv_clock_epoch_unix,
    /* */
    cv_clock_epoch_ntp
} cv_clock_epoch;

#endif /* #ifndef cv_clock_epoch_h_ */
