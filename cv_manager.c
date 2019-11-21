/* See LICENSE for license details */

#include <cv_manager.h>

#include <cv_heap_plugin.h>

#include <cv_mutex_plugin.h>

#include <cv_options_plugin.h>

char cv_manager_load(void)
{
    char b_result = 0;
    if (cv_heap_load())
    {
        if (cv_mutex_load())
        {
            if (cv_options_load())
            {
                b_result = 1;
            }
        }
    }
    return b_result;
}

void cv_manager_unload(void)
{
    cv_options_unload();

    cv_mutex_unload();

    cv_heap_unload();
}

