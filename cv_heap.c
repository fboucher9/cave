/* See LICENSE for license details */

#include <cv_heap.h>

#include <cv_null.h>

#include <stdlib.h>

#include <string.h>

void * cv_heap_alloc(
    long i_buffer_length)
{
    void * p_buffer;

    if (i_buffer_length)
    {
        p_buffer = calloc((size_t)i_buffer_length, 1);
    }
    else
    {
        p_buffer = cv_null_;
    }
    return p_buffer;
}

void cv_heap_free(
    void * p_buffer)
{
    if (p_buffer)
    {
        free(p_buffer);
    }
    else
    {
    }
}

