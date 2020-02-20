/* See LICENSE for license details */

/*
 *
 */

#include <cv_algo/cv_crc32_test.h>
#include <cv_algo/cv_crc32.h>
#include <cv_algo/cv_array.h>

/*
 *
 */

void cv_crc32_test(void) {
    static unsigned char const g_input[] = {
        'A', 'b', '3', '4' };
    static struct cv_array const g_input_array =
        cv_array_initializer_(g_input, g_input + sizeof(g_input));
    cv_crc32_convert(&g_input_array);
}

/* end-of-file: cv_crc32_test.c */
