/* See LICENSE for license details */

#ifndef cv_utf16_h_
#define cv_utf16_h_

/*
 *
 */

#include <cv_algo/cv_array_pred.h>
#include <cv_misc/cv_bool.h>

cv_bool cv_utf16be_decode(cv_array_it * p_input, unsigned long * r_output);
cv_bool cv_utf16le_decode(cv_array_it * p_input, unsigned long * r_output);
cv_bool cv_utf16be_encode(unsigned long i_input, cv_array_it * p_output);
cv_bool cv_utf16le_encode(unsigned long i_input, cv_array_it * p_output);

#endif /* #ifndef cv_utf16_h_ */

/* end-of-file: cv_utf16.h */
