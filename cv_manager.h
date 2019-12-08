/* See LICENSE for license details */

#ifndef cv_manager_h_
#define cv_manager_h_

/*

Module: cv_manager.h

Description: Init and cleanup of main application context.  The manager
does init and cleanup of all modules.

*/

#include <cv_misc/cv_bool.h>

cv_bool cv_manager_load(void);

void cv_manager_unload(void);

#endif /* #ifndef cv_manager_h_ */

/* end-of-file: cv_manager.h */
