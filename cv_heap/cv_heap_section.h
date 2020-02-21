/* See LICENSE for license details */

#ifndef cv_heap_section_h_
#define cv_heap_section_h_

/*

Module: cv_heap_section.h

Description: Linked list of memory sections used to allocate small objects
or to allocate same sized objects like pools.  Memory may be allocated from
the sections but never freed.  Management of free objects is responsability
of caller.

Comments: The primary heap uses a section to implement its allocations.
The section may be configured with the cv_heap_section_desc structure.  It
is suggested to set the i_grow_len to a value that is several times larger
than largest allocation.

*/

#include <cv_heap/cv_heap_pred.h>

#include <cv_algo/cv_list_root.h>

#include <cv_algo/cv_array_it.h>

/*

Structure: cv_heap_section_desc

Description: Options for initialization of cv_heap_section object.

Comments: If i_grow_len is a large value, larger than 64KB, then please try
to use a multiple of 4KB to reduce wasted space.

*/
struct cv_heap_section_desc
{
    /* Size in bytes of each section node, a part of size is lost to
    section node header */
    cv_uptr i_grow_len;

};

/*

Structure: cv_heap_section

Description: State for sections object.

*/
struct cv_heap_section
{
    cv_heap_section_desc o_desc;
    /* -- */
    cv_list_root o_list;
    /* -- */
    cv_array_it o_array_it;
};

/* Functions: see cv_heap_section.c for more details */

void cv_heap_section_init(
    cv_heap_section * p_this,
    cv_heap_section_desc const * p_desc);

void cv_heap_section_cleanup(
    cv_heap_section * p_this);

void * cv_heap_section_alloc(
    cv_heap_section * p_this,
    cv_uptr i_len);

#endif /* #ifndef cv_heap_section_h_ */

/* end-of-file: cv_heap_section.h */
