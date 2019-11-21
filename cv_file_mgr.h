/* See LICENSE for license details */

#ifndef cv_file_mgr_h_
#define cv_file_mgr_h_

#include <cv_file_pred.h>

extern cv_file cv_file_stdin;

extern cv_file cv_file_stdout;

extern cv_file cv_file_stderr;

void cv_file_mgr_load(void);

void cv_file_mgr_unload(void);

#endif /* #ifndef cv_file_mgr_h_ */

/* end-of-file: cv_file_mgr.h */
