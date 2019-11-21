/* See LICENSE for license details */

/*

Module: cv_heap.c

Description: Public memory allocation services.  This module is a replacement
for malloc and free.  The memory allocation strategy is simpler and less
efficient than libc however the design has less fragmentation.  The functions
are thread-safe.

*/

#include <cv_heap.h>

#include <cv_heap_plugin.h>

#include <cv_heap_small.h>

#include <cv_heap_large.h>

#include <cv_heap_node.h>

#include <cv_heap_node_ptr.h>

#include <cv_heap_primary.h>

#include <cv_null.h>

#include <cv_debug.h>

#include <stdlib.h>

#include <string.h>

#include <stdio.h>

static cv_bool g_heap_loaded = cv_false_;

static long g_heap_count = 0L;

cv_bool cv_heap_load(void)
{
    cv_bool b_result = cv_false_;
    if (!g_heap_loaded)
    {
        if (cv_heap_primary_load())
        {
            if (cv_heap_small_load())
            {
                if (cv_heap_large_load())
                {
                    g_heap_loaded = cv_true_;
                    b_result = cv_true_;
                }
                else
                {
                    cv_debug_msg_("heap load large fail");
                }
            }
            else
            {
                cv_debug_msg_("heap load small fail");
            }
        }
        else
        {
            cv_debug_msg_("heap load primary fail");
        }
    }
    else
    {
        cv_debug_msg_("heap already loaded");
    }
    return b_result;
}

/*

Function: cv_heap_unload()

Description: Unload of heap module.  Cleanup global resources allocated during
lifetime of module.

Parameters: none.

Returns: none.

Comments: There's no thread safety for leak counter, some false detections
may occur.  The sub modules will produce correct leak reports.

*/
void cv_heap_unload(void)
{
    if (g_heap_loaded)
    {
#if defined cv_have_libc_
        printf("*** %ld leaks ***\n", g_heap_count);
#endif /* #if defined cv_have_libc_ */
        cv_heap_large_unload();
        cv_heap_small_unload();
        cv_heap_primary_unload();
        g_heap_loaded = cv_false_;
    }
    else
    {
        cv_debug_msg_("heap already unloaded");
    }
}

void * cv_heap_alloc(
    long i_buffer_length)
{
    void * p_buffer = cv_null_;

    if (g_heap_loaded && i_buffer_length)
    {
        if (i_buffer_length <= cv_heap_small_max_len_)
        {
            p_buffer = cv_heap_small_alloc(i_buffer_length);
        }
        else
        {
            p_buffer = cv_heap_large_alloc(i_buffer_length);
        }

        if (p_buffer)
        {
            g_heap_count ++;
        }
        else
        {
            cv_debug_msg_("out of memory");
        }
    }
    else
    {
        cv_debug_msg_("heap alloc invalid");
    }
    return p_buffer;
}

void cv_heap_free(
    void * p_buffer)
{
    if (g_heap_loaded && p_buffer)
    {
        cv_heap_node const * const p_heap_node =
            cv_heap_node_from_payload(p_buffer);

        long const i_buffer_length = p_heap_node->i_len;

        if (i_buffer_length <= cv_heap_small_max_len_)
        {
            cv_heap_small_free(p_buffer);
        }
        else
        {
            cv_heap_large_free(p_buffer);
        }

        g_heap_count --;
    }
    else
    {
        cv_debug_msg_("heap free invalid");
    }
}

