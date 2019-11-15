/* See LICENSE for license details */

#include <cv_main.h>

#include <cv_manager.h>

#include <cv_options.h>

/* Setup all managers, convert arguments to an options object and provide
options to application callback.  */
char cv_main_dispatch(
    /* Pointer to command line arguments */
    cv_options_desc const * p_options_desc,
    /* Pointer to callback */
    cv_main_func * p_func)
{
    char b_result = 0;

    /* Validate input parameters and descriptor contents */
    if (p_options_desc &&
        p_func)
    {
        /* load all plugins */
        if (cv_manager_load())
        {
            cv_options * p_options = cv_options_create(p_options_desc);
            if (p_options)
            {
                b_result = (*p_func)(p_options);

                cv_options_destroy(p_options);
            }

            /* unload all plugins */
            cv_manager_unload();
        }
        else
        {
        }
    }
    else
    {
    }
    return b_result;
}
