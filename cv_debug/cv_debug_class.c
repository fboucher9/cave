/* See LICENSE for license details */

/*
 *
 */

#include <cv_debug/cv_debug_class.h>
#include <cv_debug/cv_debug_plugin.h>

#if defined cv_debug_

#include <cv_thread/cv_mutex_impl.h>
#include <cv_runtime.h>
#include <cv_misc/cv_cast.h>

#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

static long g_debug_class_count = 0;

static cv_debug_class g_debug_class_footer;

static cv_debug_class * g_debug_class_list = &g_debug_class_footer;

static cv_mutex g_debug_class_mutex;

/*
 *
 */

static void cv_debug_class_register( cv_debug_class * p_class) {
    if (p_class->p_next) {
    } else {
        p_class->p_next = g_debug_class_list;
        g_debug_class_list = p_class;
    }
}

/*
 *
 */

void xx_debug_class_construct( cv_debug_class * p_class, void * p_buf) {
    cv_mutex_impl_lock(&g_debug_class_mutex);
    cv_runtime_memset(p_buf, 0xcc, p_class->i_placement_len);
    cv_debug_class_register(p_class);
    p_class->i_init_count ++;
    g_debug_class_count ++;
    cv_mutex_impl_unlock(&g_debug_class_mutex);
}

/*
 *
 */

void xx_debug_class_destruct( cv_debug_class * p_class, void * p_buf) {
    cv_mutex_impl_lock(&g_debug_class_mutex);
    cv_runtime_memset(p_buf, 0xcd, p_class->i_placement_len);
    cv_debug_class_register(p_class);
    p_class->i_init_count --;
    g_debug_class_count --;
    cv_mutex_impl_unlock(&g_debug_class_mutex);
}

/*
 *
 */

static void cv_debug_class_report_node(cv_debug_class const * p_iterator) {
    if (p_iterator->i_init_count) {
#if defined cv_have_libc_
        signed long const i_init_count =
            cv_cast_(signed long)(p_iterator->i_init_count);
        fprintf(stderr, "%s:%ld\n",
            p_iterator->p_name,
            i_init_count);
#endif /* #if defined cv_have_libc_ */
    }
}

/*
 *
 */

static void cv_debug_class_report(void) {
    cv_debug_class * p_iterator = g_debug_class_list;
    while (p_iterator && p_iterator != &g_debug_class_footer) {
        cv_debug_class_report_node(p_iterator);
        p_iterator = p_iterator->p_next;
    }
}

#endif /* #if defined cv_debug_ */

/*
 *
 */

void cv_debug_load(void) {
#if defined cv_debug_
    cv_runtime_memset(&g_debug_class_mutex, 0, sizeof(g_debug_class_mutex));
#endif /* #if defined cv_debug_ */
}

/*
 *
 */

void cv_debug_unload(void) {
    /* Print report of class leaks */
#if defined cv_debug_
    cv_debug_class_report();
    if (0 != g_debug_class_count)
    {
        cv_runtime_exit(43);
    }
#endif /* #if defined cv_debug_ */
}

/* end-of-file: cv_debug_class.c */
