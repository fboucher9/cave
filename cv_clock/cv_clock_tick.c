/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock/cv_clock_tick.h>
#include <cv_clock/cv_clock_tool.h>


/* Detect if RDTSC is available for compiler and architected */
#if defined __GNUC__
#if defined __x86_64__
#define CV_HAVE_RDTSC
#elif defined __i386__
#define CV_HAVE_RDTSC
#endif
#endif /* #if defined __GNUC__ */


/*
 *
 */

cv_bool cv_clock_tick_is_supported(void) {
    cv_bool b_supported = cv_false;
#if defined CV_HAVE_RDTSC
    b_supported = cv_true;
#else /* #if defined CV_HAVE_RDTSC */
    b_supported = cv_false;
#endif /* #if defined CV_HAVE_RDTSC */
    return b_supported;
}

/*
 *
 */

cv_bool cv_clock_tick_read(
    cv_clock_tick * r_value) {
    cv_bool b_result = cv_false;
#if defined CV_HAVE_RDTSC
    {
        cv_ull const ll_value = __builtin_ia32_rdtsc();
        cv_clock_set(&r_value->o_clock, ll_value);
        b_result = cv_true;
    }
#else /* #if defined CV_HAVE_RDTSC */
    b_result = cv_false;
#endif /* #if defined CV_HAVE_RDTSC */
    return b_result;
}

/* end-of-file: cv_clock_tick.c */
