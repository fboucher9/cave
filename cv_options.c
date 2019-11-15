/* See LICENSE for license details */

#include <cv_options.h>

#include <cv_options_desc.h>

#include <cv_heap.h>

#include <cv_null.h>

#include <cv_sizeof.h>

#include <cv_unused.h>

struct cv_options
{
    cv_options_desc o_desc;
};

/*
 *      Initialize instance of cv_options object using provided descriptor
 *      structure.  All strings are copied, using heap allocations.
 */
static char cv_options_init(
    cv_options * p_this,
    cv_options_desc const * p_options_desc)
{
    char b_result;
    p_this->o_desc = *(p_options_desc);
    b_result = 1;
    return b_result;
}

/*
 *      Cleanup instance of cv_options object.  Undo all that was initialized
 *      during entire lifetime of object.
 */
static void cv_options_cleanup(
    cv_options * p_this)
{
    cv_unused_(p_this);
}

/*
 *      Create an instance of cv_options object.
 */
cv_options * cv_options_create(
    cv_options_desc const * p_options_desc)
{
    cv_options * p_result = cv_null_;

    /* Validate input parameters */
    if (p_options_desc)
    {
        /* Allocate memory for object */
        cv_options * const p_this = cv_new_(cv_options);

        /* Validate memory allocation */
        if (p_this)
        {
            /* Initialize object */
            if (cv_options_init(p_this, p_options_desc))
            {
                p_result = p_this;
            }
            else
            {
                /* Failed initialization, do cleanup */
                cv_delete_(p_this);
            }
        }
        else
        {
        }
    }
    else
    {
    }
    return p_result;
}

/*
 *      Destroy instance of cv_options object.  First do cleanup of object then
 *      free memory allocated for object.
 */
void cv_options_destroy(
    cv_options * p_this)
{
    /* Validate input parameters */
    if (p_this)
    {
        /* Cleanup of object */
        cv_options_cleanup(p_this);

        /* Free memory allocated for object */
        cv_delete_(p_this);
    }
}

/*

Function: cv_options_query()

Description:

    Get information about options.

*/
char cv_options_query(
    cv_options const * p_this,
    cv_options_desc * p_desc)
{
    *p_desc = p_this->o_desc;
    return 1;
}

