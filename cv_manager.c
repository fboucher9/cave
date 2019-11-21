/* See LICENSE for license details */

/*

Module: cv_manager.c

Description: None.

*/

#include <cv_manager.h>

#include <cv_heap_plugin.h>

#include <cv_mutex_plugin.h>

#include <cv_options_plugin.h>

/*

*/
cv_bool cv_manager_load(void)
{
    cv_bool b_result = cv_false_;
    if (cv_heap_load())
    {
        if (cv_mutex_load())
        {
            if (cv_options_load())
            {
                b_result = cv_true_;
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

