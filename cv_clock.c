/* See LICENSE for license details */

#include <cv_clock.h>

#include <cv_unused.h>

#include <time.h>

#include <unistd.h>

char cv_clock_read(
    cv_clock_epoch e_clock_epoch,
    cv_clock * p_value)
{
    char b_result;

    cv_unused_(e_clock_epoch);
    cv_unused_(p_value);
    b_result = 0;

    return b_result;
}

char cv_clock_sleep(
    cv_clock const * p_value)
{
    char b_result;

    cv_unused_(p_value);
    b_result = 0;

    return b_result;
}

char cv_clock_convert_freq(
    cv_clock * p_value,
    cv_ull_t i_freq)
{
    char b_result;

    cv_unused_(p_value);
    cv_unused_(i_freq);
    b_result = 0;

    return b_result;
}

char cv_clock_convert_epoch(
    cv_clock * p_value,
    cv_clock_epoch e_clock_epoch)
{
    char b_result;

    cv_unused_(p_value);
    cv_unused_(e_clock_epoch);
    b_result = 0;

    return b_result;
}

