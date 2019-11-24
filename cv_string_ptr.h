/* See LICENSE for license details */

#ifndef cv_string_ptr_h_
#define cv_string_ptr_h_

#include <cv_string_pred.h>

#include <cv_ptr.h>

/*

Family of compatible pointers.  A string may be composed of signed or unsigned
characters.  The characters may be const or mutable.  The void is used to
when passing pointers to or from apis that require void pointers.

Note: this trick works only if all pointers have the same size.  That is the
case for most architectures.  The compiler-time assertions below are used
to verify the size of the union.

*/

union cv_string_ptr
{
    void const * pc_void;
    void * p_void;
    char const * pc_char;
    char * p_char;
    unsigned char const * pc_uchar;
    unsigned char * p_uchar;
};

/* Verify that sizeof union matches size of each member */
typedef char cv_verify_sizeof_string_ptr [
    (sizeof(cv_string_ptr) == sizeof(void *))
    && (sizeof(cv_string_ptr) == sizeof(void const *))
    && (sizeof(cv_string_ptr) == sizeof(char *))
    && (sizeof(cv_string_ptr) == sizeof(char const *))
    && (sizeof(cv_string_ptr) == sizeof(unsigned char *))
    && (sizeof(cv_string_ptr) == sizeof(unsigned char const *)) ? 1 : -1 ];

#endif /* #ifndef cv_string_ptr_h_ */
