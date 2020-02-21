/* See LICENSE for license details */

#include <cv_main.h>

#include <cv_manager.h>

#include <cv_options/cv_options.h>

#include <cv_debug/cv_debug.h>

#include <cv_misc/cv_bool.h>

static cv_options g_main_options = {0};

static cv_bool g_main_init_done = cv_false;

/* Setup all managers, convert arguments to an options object and provide
options to application callback.  */
cv_options * cv_main_init(
    int argc,
    char const * const * argv)
{
    cv_options * p_options = 0;
    cv_debug_assert_(!g_main_init_done, cv_debug_code_already_loaded);
    /* load all plugins */
    if (cv_manager_load()) {
        cv_options_init(&g_main_options);
        {
            cv_options_desc o_options_desc = {0};
            cv_options_desc_init(&o_options_desc, argv, argv + argc);
            if (cv_options_setup(&g_main_options, &o_options_desc)) {
                g_main_init_done = cv_true;
                p_options = & g_main_options;
            }
            cv_options_desc_cleanup(&o_options_desc);
            if (!p_options) {
                cv_options_cleanup(&g_main_options);
            }
        }
        if (!p_options) {
            cv_manager_unload();
        }
    }
    return p_options;
}

void cv_main_cleanup(
    cv_options * p_options)
{
    cv_debug_assert_(g_main_init_done, cv_debug_code_already_unloaded);
    if (p_options) {
        cv_options_cleanup(& g_main_options);
    }
    /* unload all plugins */
    cv_manager_unload();
    g_main_init_done = cv_false;
}

