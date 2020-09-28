/* See LICENSE for license details */

/*

Module: cv_manager.c

Description: None.

*/

#include <cv_manager.h>
#include <cv_heap/cv_heap_plugin.h>
#include <cv_thread/cv_thread_plugin.h>
#include <cv_options/cv_options_plugin.h>
#include <cv_clock/cv_clock_plugin.h>
#include <cv_debug/cv_debug_plugin.h>
#include <cv_trace/cv_trace_plugin.h>
#include <cv_json/cv_json.h>
#include <cv_object/cv_object.h>

/*

*/
cv_bool cv_manager_load(void)
{
    cv_bool b_result = cv_false;
    cv_debug_load();
    cv_object_load();
    if (cv_heap_load()) {
        if (cv_trace_load()) {
            if (cv_thread_load()) {
                if (cv_clock_load()) {
                    if (cv_options_load()) {
                        cv_json_load();
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
                cv_trace_unload();
            }
        }
        if (!b_result) {
            cv_heap_unload();
        }
    }
    if (!b_result) {
        cv_object_unload();
        cv_debug_unload();
    }
    return b_result;
}

void cv_manager_unload(void)
{
    cv_json_unload();
    cv_options_unload();
    cv_clock_unload();
    cv_thread_unload();
    cv_heap_unload();
    cv_trace_unload();
    cv_object_unload();
    cv_debug_unload();
}

