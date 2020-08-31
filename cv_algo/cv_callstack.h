/* See LICENSE for license details */

#ifndef cv_callstack_h_
#define cv_callstack_h_

/*
 *
 */

#include <cv_algo/cv_array_pred.h>

void cv_callstack_push( unsigned short i_symbol_key);
void cv_callstack_pop(void);
unsigned char cv_callstack_count(void);
unsigned short cv_callstack_query( unsigned char i_index);

#endif /* #ifndef cv_callstack_h_ */

/* end-of-file: cv_callstack.h */
