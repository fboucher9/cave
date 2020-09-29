/* See LICENSE for license details */

#ifndef cv_callstack_h_
#define cv_callstack_h_

/*
 *  Module: cv_algo/cv_callstack.h
 *
 *  Description:
 *
 *      Internal stack for debugging, trace, profiling and leak detection.  It
 *      is highly recommended to enable this feature from release builds.
 *      Implementation must be fast.  Information is stored in thread local
 *      storage so no lock is required when updating stack state.
 *
 *  Comments:
 *
 *      - Arguments are optional, they may be filtered during reports by
 *      ignoring all types except functions.
 *
 *      - For object arguments, it is recommended to push the object's
 *      unique identifier which is composed of a class string and an
 *      instance number.
 */

/*
 *  Example:
 *      void demo(void) {
 *          unsigned long bp = cv_callstack_enter("demo");
 *          cv_callstack_push_string("hello");
 *          cv_callstack_push_number(1234);
 *          ...
 *          cv_callstack_leave(bp);
 *      }
 */

#include <cv_misc/cv_types.h>

#define cv_have_callstack_

#if defined cv_have_callstack_

/* Types returned by query() */
enum cv_callstack_type {
    /* Function name pushed on stack on enter() */
    cv_callstack_type_function = 1,
    /* String argument pushed with push_string() */
    cv_callstack_type_string = 2,
    /* Number argument pushed with push_number() */
    cv_callstack_type_number = 3
};

/* Value returned by query() */
union cv_callstack_value {
    char const * p_text;
    cv_uptr i_number;
};

unsigned long cv_callstack_enter( char const * p_function);
void cv_callstack_push_string( char const * p_string);
void cv_callstack_push_number( cv_uptr i_number);
void cv_callstack_leave(unsigned long i_stack_pointer);
unsigned char cv_callstack_count(void);
unsigned char cv_callstack_query( unsigned char i_index,
    union cv_callstack_value * r_value);

#endif /* #if defined cv_have_callstack_ */

#endif /* #ifndef cv_callstack_h_ */

/* end-of-file: cv_callstack.h */
