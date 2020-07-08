/* See LICENSE for license details */

/*
 *
 */

#include <cv_clock/cv_clock_tick.h>
#include <cv_clock/cv_clock_tool.h>


/* Detect if RDTSC is available for compiler and architected */
#if defined __GNUC__
#if defined __x86_64__
#define cv_have_rdtsc_
#elif defined __i386__
#define cv_have_rdtsc_
#endif
#endif /* #if defined __GNUC__ */


/*
 *
 */

cv_bool cv_clock_tick_is_supported(void) {
    cv_bool b_supported = cv_false;
#if defined cv_have_rdtsc_
    b_supported = cv_true;
#else /* #if defined cv_have_rdtsc_ */
    b_supported = cv_false;
#endif /* #if defined cv_have_rdtsc_ */
    return b_supported;
}

/*
 *
 */

cv_bool cv_clock_tick_read(
    cv_clock_tick * r_value) {
    cv_bool b_result = cv_false;
#if defined cv_have_rdtsc_
    {
        cv_ull const ll_value = __builtin_ia32_rdtsc();
        cv_clock_set(&r_value->o_clock, ll_value);
        b_result = cv_true;
    }
#else /* #if defined cv_have_rdtsc_ */
    b_result = cv_false;
#endif /* #if defined cv_have_rdtsc_ */
    return b_result;
}

/* end-of-file: cv_clock_tick.c */
