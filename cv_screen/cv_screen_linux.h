/* See LICENSE for license details */

#ifndef cv_screen_linux_h_
#define cv_screen_linux_h_

/*
 *
 */

#include <cv_screen/cv_screen_pred.h>
#include <cv_file/cv_file_pred.h>

#if defined cv_linux_

struct cv_screen_raw * cv_screen_raw_create(cv_file const * p_file);

void cv_screen_raw_destroy(struct cv_screen_raw * p_screen_raw);

#endif /* #if defined cv_linux_ */

#endif /* #if defined cv_screen_linux_h_ */

/* end-of-file: cv_screen_linux.h */
