/* See LICENSE for license details */

#include <cv_options_it.h>

#include <cv_options.h>

#include <cv_options_desc.h>

#include <cv_unused.h>

char cv_options_it_init(
    cv_options_it * p_this,
    cv_options const * p_options)
{
    char b_result = 0;
    if (p_this && p_options)
    {
        p_this->p_cur = p_options->o_desc.p_args_min;
        p_this->p_end = p_options->o_desc.p_args_max;
        b_result = 1;
    }
    return b_result;
}

void cv_options_it_cleanup(
    cv_options_it * p_this)
{
    cv_unused_(p_this);
}

char cv_options_it_next(
    cv_options_it * p_this,
    char const * * r_cur)
{
    char b_result;

    if (p_this->p_cur != p_this->p_end)
    {
        *(r_cur) = *(p_this->p_cur);
        p_this->p_cur ++;
        b_result = 1;
    }
    else
    {
        b_result = 0;
    }

    return b_result;
}

