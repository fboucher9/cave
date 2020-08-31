/* See LICENSE for license details */

#ifndef cv_symbol_h_
#define cv_symbol_h_

/*
 *
 */

#include <cv_algo/cv_array_pred.h>
#include <cv_misc/cv_bool.h>

void cv_symbol_load(void);

void cv_symbol_unload(void);

unsigned short cv_symbol_register( cv_array const * p_name);

void cv_symbol_unregister(unsigned short i_symbol_key);

cv_bool cv_symbol_query( unsigned short i_symbol_key, cv_array * r_name);

#endif /* #ifndef cv_symbol_h_ */

/* end-of-file: cv_symbol.h */
