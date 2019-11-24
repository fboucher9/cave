/* See LICENSE for license details */

#include <cv_main.h>

#include <cv_manager.h>

#include <cv_options.h>

#include <cv_bool.h>

static cv_options g_cv_main_options = cv_options_initializer_;

static cv_bool g_cv_main_init_done = cv_false;

/* Setup all managers, convert arguments to an options object and provide
options to application callback.  */
cv_options * cv_main_init(
    int argc,
    char const * const * argv)
{
    cv_options * p_options = cv_null_;

    if (!g_cv_main_init_done)
    {
        /* load all plugins */
        if (cv_manager_load())
        {
            if (cv_options_init(&g_cv_main_options))
            {
                cv_options_desc o_options_desc = cv_options_desc_initializer_;

                if (cv_options_desc_init(&o_options_desc,
                        argv,
                        argv + argc))
                {
                    if (cv_options_setup(&g_cv_main_options, &o_options_desc))
                    {
                        g_cv_main_init_done = cv_true;

                        p_options = & g_cv_main_options;
                    }

                    cv_options_desc_cleanup(&o_options_desc);
                }

                if (!p_options)
                {
                    cv_options_cleanup(&g_cv_main_options);
                }
            }

            if (!p_options)
            {
                cv_manager_unload();
            }
        }
    }
    return p_options;
}

void cv_main_cleanup(
    cv_options * p_options)
{
    if (g_cv_main_init_done)
    {
        if (p_options)
        {
            cv_options_cleanup(& g_cv_main_options);
        }

        /* unload all plugins */
        cv_manager_unload();

        g_cv_main_init_done = cv_false;
    }
}

