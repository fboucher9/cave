/* See LICENSE for license details */

/*
 *
 */

#include <cv_object/cv_object.h>
#include <cv_heap/cv_heap.h>
#include <cv_algo/cv_unique.h>
#include <cv_misc/cv_cast.h>
#include <cv_thread/cv_mutex_impl.h>
#include <cv_runtime.h>
#include <cv_debug/cv_debug.h>
#if defined cv_have_libc_
#include <stdio.h>
#endif /* #if defined cv_have_libc_ */

cv_debug_decl_(g_class, "cv_object", sizeof(cv_object));

/*
 *
 */

void cv_object_load(void) {
}

/*
 *
 */

void cv_object_unload(void) {
}

/*
 *
 */

void cv_object_init(
    cv_object * p_this,
    char const * p_class,
    cv_uptr i_placement_len) {
    cv_debug_construct_(g_class, p_this);
    cv_mutex_impl_init(&p_this->o_mutex);
    p_this->i_placement_len = i_placement_len;
    p_this->i_leak_count = 0;
    cv_unique_init(&p_this->o_unique);
    cv_unique_set(&p_this->o_unique, p_class, 0);
#if defined cv_debug_
    p_this->i_debug_count = 0;
#endif /* #if defined cv_debug_ */
}

/*
 *
 */

void cv_object_cleanup(
    cv_object * p_this) {
#if defined cv_debug_
    if (p_this->i_debug_count) {
#if defined cv_have_libc_
        signed long const i_leak_count =
            cv_cast_(signed long)(p_this->i_debug_count);
        fprintf(stderr, "object debug leak %s:%ld\n", p_this->o_unique.p_class,
            i_leak_count);
#endif /* #if defined cv_have_libc_ */
    }
#endif /* #if defined cv_debug_ */
    if (p_this->i_leak_count) {
#if defined cv_have_libc_
        signed long const i_leak_count =
            cv_cast_(signed long)(p_this->i_leak_count);
        fprintf(stderr, "object leak %s:%ld\n", p_this->o_unique.p_class,
            i_leak_count);
#endif /* #if defined cv_have_libc_ */
    }
    cv_unique_cleanup(&p_this->o_unique);
    cv_mutex_impl_cleanup(&p_this->o_mutex);
    cv_debug_destruct_(g_class, p_this);
}

/*
 *
 */

void * cv_object_alloc(
    cv_object * p_this,
    cv_unique * r_unique) {
    void * p_placement = 0;
    cv_mutex_impl_lock(&p_this->o_mutex);
    cv_unique_next(&p_this->o_unique);
    /* allocate memory */
    p_placement = cv_heap_alloc(p_this->i_placement_len,
        p_this->o_unique.p_class, p_this->o_unique.i_instance);
    if (p_placement) {
        /* construct */
        p_this->i_leak_count ++;
        if (r_unique) {
            *r_unique = p_this->o_unique;
        }
    }
    cv_mutex_impl_unlock(&p_this->o_mutex);
    return p_placement;
}

/*
 *
 */

void cv_object_free(
    cv_object * p_this,
    void * p_placement) {
    cv_mutex_impl_lock(&p_this->o_mutex);
    p_this->i_leak_count --;
    /* free memory */
    cv_heap_free(p_placement);
    cv_mutex_impl_unlock(&p_this->o_mutex);
}

/*
 *
 */

void cv_object_pick(
    cv_object * p_this,
    cv_unique * r_unique) {
    cv_mutex_impl_lock(&p_this->o_mutex);
    cv_unique_next(&p_this->o_unique);
    if (r_unique) {
        *r_unique = p_this->o_unique;
    }
    cv_mutex_impl_unlock(&p_this->o_mutex);
}

/*
 *
 */

void cv_object_construct(
    cv_object * p_this,
    void * p_placement) {
#if defined cv_debug_
    cv_mutex_impl_lock(&p_this->o_mutex);
    cv_runtime_memset(p_placement, 0xcc, p_this->i_placement_len);
    p_this->i_debug_count ++;
    cv_mutex_impl_unlock(&p_this->o_mutex);
#else /* #if defined cv_debug_ */
    (void)p_this;
    (void)p_placement;
#endif /* #if defined cv_debug_ */
}

/*
 *
 */

void cv_object_destruct(
    cv_object * p_this,
    void * p_placement) {
#if defined cv_debug_
    cv_mutex_impl_lock(&p_this->o_mutex);
    cv_runtime_memset(p_placement, 0xcd, p_this->i_placement_len);
    p_this->i_debug_count --;
    cv_mutex_impl_unlock(&p_this->o_mutex);
#else /* #if defined cv_debug_ */
    (void)p_this;
    (void)p_placement;
#endif /* #if defined cv_debug_ */
}

/* end-of-file: cv_object.c */
