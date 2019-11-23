/* See LICENSE for license details */

#include <cv_clock.h>

#include <cv_unused.h>

#if defined cv_have_libc_
#include <time.h>

#include <unistd.h>
#endif /* #if defined cv_have_libc_ */

cv_bool cv_clock_read(
    cv_clock_epoch e_clock_epoch,
    cv_clock * p_value)
{
    cv_bool b_result;

    cv_unused_(e_clock_epoch);
    cv_unused_(p_value);
    b_result = cv_false_;

    return b_result;
}

cv_bool cv_clock_sleep(
    cv_clock const * p_value)
{
    cv_bool b_result;

    cv_unused_(p_value);
    b_result = cv_false_;

    return b_result;
}

cv_bool cv_clock_convert_freq(
    cv_clock * p_value,
    cv_ull i_freq)
{
    cv_bool b_result;

    cv_unused_(p_value);
    cv_unused_(i_freq);
    b_result = cv_false_;

    return b_result;
}

cv_bool cv_clock_convert_epoch(
    cv_clock * p_value,
    cv_clock_epoch e_clock_epoch)
{
    cv_bool b_result;

    cv_unused_(p_value);
    cv_unused_(e_clock_epoch);
    b_result = cv_false_;

    return b_result;
}

