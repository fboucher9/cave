/* See LICENSE for license details */

/*

Module: cv_manager.c

Description: None.

*/

#include <cv_manager.h>
#include <cv_heap/cv_heap_plugin.h>
#include <cv_thread/cv_mutex_plugin.h>
#include <cv_thread/cv_thread_plugin.h>
#include <cv_options/cv_options_plugin.h>
#include <cv_file/cv_file_std.h>
#include <cv_clock/cv_clock_plugin.h>
#include <cv_debug_plugin.h>
#include <cv_misc/cv_null.h>

/*

*/
cv_bool cv_manager_load(void)
{
    cv_bool b_result = cv_false;
    cv_debug_load();
    if (cv_file_std_load()) {
        if (cv_mutex_load()) {
            if (cv_heap_load()) {
                if (cv_thread_load()) {
                    if (cv_clock_load()) {
                        if (cv_options_load()) {
                            b_result = cv_true;
                        }
                        if (!b_result) {
                            cv_clock_unload();
                        }
                    }
                    if (!b_result) {
                        cv_thread_unload();
                    }
                }
                if (!b_result) {
                    cv_heap_unload();
                }
            }
            if (!b_result) {
                cv_mutex_unload();
            }
        }
        if (!b_result) {
            cv_file_std_unload();
        }
    }
    if (!b_result) {
        cv_debug_unload();
    }
    return b_result;
}

void cv_manager_unload(void)
{
    cv_options_unload();
    cv_clock_unload();
    cv_thread_unload();
    cv_heap_unload();
    cv_mutex_unload();
    cv_file_std_unload();
    cv_debug_unload();
}

