/* See LICENSE for license details */

#include <cv_manager.h>

#include <cv_heap_plugin.h>

char cv_manager_load(void)
{
    char b_result = 0;
    if (cv_heap_load())
    {
        b_result = 1;
    }
    return b_result;
}

void cv_manager_unload(void)
{
    cv_heap_unload();
}

