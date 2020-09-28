/* See LICENSE for license details */

#ifndef cv_callstack_h_
#define cv_callstack_h_

/*
 *
 */

void cv_callstack_push( char const * p_symbol);
void cv_callstack_pop(void);
unsigned char cv_callstack_count(void);
char const * cv_callstack_query( unsigned char i_index);

#endif /* #ifndef cv_callstack_h_ */

/* end-of-file: cv_callstack.h */
