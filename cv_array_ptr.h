/* See LICENSE for license details */

#ifndef cv_array_ptr_h_
#define cv_array_ptr_h_

#include <cv_array_pred.h>

#include <cv_ptr.h>

#include <cv_types.h>

union cv_array_ptr
{
    void const * pc_void;
    void * p_void;
    char const * pc_char;
    char * p_char;
    unsigned char const * pc_uchar;
    unsigned char * p_uchar;
    short const * pc_short;
    short * p_short;
    unsigned short const * pc_ushort;
    unsigned short * p_ushort;
    int const * pc_int;
    int * p_int;
    unsigned const * pc_uint;
    unsigned * p_uint;
    long const * pc_long;
    long * p_long;
    unsigned long const * pc_ulong;
    unsigned long * p_ulong;
    cv_sll const * pc_ll;
    cv_sll * p_ll;
    cv_ull const * pc_ull;
    cv_ull * p_ull;
    void const * const * ppc_void;
    void * * pp_void;
    char const * const * ppc_char;
    char * * pp_char;
    unsigned char const * const * ppc_uchar;
    unsigned char * * pp_uchar;
};

#endif /* #ifndef cv_array_ptr_h_ */

/* end-of-file: cv_array_ptr.h */
