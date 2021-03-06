/* See LICENSE for license details */

/*
 *
 */

#include <cv_heap/cv_heap_test.h>
#include <cv_heap/cv_heap.h>
#include <cv_thread/cv_thread.h>
#include <cv_thread/cv_thread_desc.h>
#include <cv_thread/cv_mutex.h>
#include <cv_options/cv_options_it.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_tool.h>
#include <cv_debug/cv_debug.h>
#include <cv_memory.h>
#include <cv_clock/cv_clock.h>
#include <cv_clock/cv_clock_mono.h>
#include <cv_clock/cv_clock_duration.h>
#include <cv_clock/cv_clock_tool.h>
#include <cv_misc/cv_cast.h>
#include <cv_misc/cv_limits.h>
#include <cv_test_print.h>
#include <cv_number/cv_number_format.h>
#include <cv_misc/cv_thread_local.h>
#include <cv_random/cv_random.h>
#include <cv_random/cv_random_crypto.h>

#if defined cv_have_libc_
#include <time.h>
#include <stdlib.h>
#endif /* #if defined cv_have_libc_ */

enum cv_heap_stress_const {
    cv_heap_stress_max_thread = 16,
    cv_heap_stress_max_node = 16
};

/*
 *
 */

struct cv_heap_stress_node {
    struct cv_random o_random;
    /* -- */
    void * p_buffer;
    /* -- */
    cv_uptr i_buffer_len;
    /* -- */
    unsigned long i_alloc_count;
    unsigned long i_free_count;
    /* -- */
    unsigned char a_pattern[8u];
};

/*
 *
 */

struct cv_heap_stress_thread {
    cv_thread o_thread;
    /* -- */
    cv_mutex o_mutex;
    /* -- */
    struct cv_random o_random;
    /* -- */
    cv_bool b_continue;
    cv_bool b_valid;
    char ac_padding[6u];
};

static cv_mutex g_random_lock;

static unsigned int cv_heap_stress_pick(
    unsigned int i_modulo) {
    unsigned int i_result = 0;
    int i_rand_result = 0;
    cv_mutex_lock(&g_random_lock);
    {
#if defined cv_have_libc_
        i_rand_result = rand();
#endif /* #if defined cv_have_libc_ */
        if (i_rand_result >= 0) {
            i_result = (i_rand_result & cv_signed_int_max_);
            if (i_modulo) {
                i_result = (i_result % i_modulo);
            }
        }
    }
    cv_mutex_unlock(&g_random_lock);
    return i_result;
}

static void cv_heap_stress_sleep_usec(
    unsigned long i_useconds) {
    cv_clock_duration o_clock_duration;
    cv_clock_duration_init_usec(&o_clock_duration,
        i_useconds / 1000000UL,
        i_useconds % 1000000UL);
    cv_clock_duration_until(&o_clock_duration);
    cv_clock_duration_cleanup(&o_clock_duration);
}

static void cv_heap_stress_node_init(struct cv_heap_stress_node * p_this,
    unsigned long i_seed) {
    cv_random_init(&p_this->o_random, i_seed);
    p_this->p_buffer = 0;
    p_this->i_alloc_count = 0;
    p_this->i_free_count = 0;
}

static void cv_heap_stress_node_cleanup(struct cv_heap_stress_node * p_this) {
    if (p_this->p_buffer) {
        cv_heap_free(p_this->p_buffer);
        p_this->i_free_count ++;
        p_this->p_buffer = 0;
    }
    cv_random_cleanup(&p_this->o_random);
}

static void cv_heap_stress_node_toggle(struct cv_heap_stress_node * p_this) {
    if (p_this->p_buffer) {
#if 0 /* verbose */
        cv_print_0("free", 80);
        cv_print_nl();
#endif /* verbose */
        /* Verify corruption */
        {
            cv_bool b_valid = cv_true;
            cv_uptr i_buffer_iterator = 0;
            cv_array_ptr o_ptr;
            o_ptr.p_void = p_this->p_buffer;
            while (b_valid && (i_buffer_iterator < p_this->i_buffer_len)) {
                if (p_this->a_pattern[0u] !=
                    o_ptr.pc_uchar[i_buffer_iterator]) {
                    b_valid = cv_false;
                }
                i_buffer_iterator ++;
            }
            cv_debug_assert_(b_valid, cv_debug_code_error);
        }
        cv_heap_free(p_this->p_buffer);
        p_this->i_free_count ++;
        p_this->p_buffer = 0;
    } else {
        /* allocate memory */
        /* select pattern */
        /* fill with pattern */
        p_this->i_buffer_len = (30000UL * 100UL / (100UL +
                cv_random_pick(&p_this->o_random, 29901U)));
#if 0 /* verbose */
        cv_print_0("alloc ", 80);
        cv_print_unsigned((p_this->i_buffer_len & 0x7fffU),
            cv_number_format_dec());
        cv_print_nl();
#endif /* verbose */
        p_this->p_buffer = cv_heap_alloc(p_this->i_buffer_len,
            "heap_stress_node", 0);
        if (p_this->p_buffer) {
            p_this->i_alloc_count ++;
            p_this->a_pattern[0u] = (cv_random_pick(&p_this->o_random, 256) & 0xffU);
            /* Fill in memory */
            cv_memory_fill(p_this->p_buffer, p_this->i_buffer_len,
                p_this->a_pattern[0u]);
        }
    }
}

static void cv_heap_stress_thread_entry(void * p_context) {
    static cv_thread_local_ struct cv_heap_stress_node
        a_node[cv_heap_stress_max_node];
    struct cv_heap_stress_thread * p_this =
        cv_cast_(struct cv_heap_stress_thread *)(p_context);
    cv_bool b_continue = cv_true;
    unsigned int i_node_index = 0;
    {
        i_node_index = 0;
        while (i_node_index < cv_heap_stress_max_node) {
            struct cv_heap_stress_node * const p_stress_node =
                a_node + i_node_index;
            unsigned long i_node_seed = cv_random_pick(&p_this->o_random, 0);
            cv_heap_stress_node_init(p_stress_node, i_node_seed);
            i_node_index ++;
        }
    }
    i_node_index = 0;
    while (b_continue) {
        /* cv_mutex_lock(&p_this->o_mutex); */
        b_continue = p_this->b_continue;
        /* cv_mutex_unlock(&p_this->o_mutex); */
        if (b_continue) {
            /* Allocate and free one buffer */
            i_node_index = cv_heap_stress_pick(cv_heap_stress_max_node);
#if 0 /* verbose */
            cv_print_0("toggle ", 80);
            cv_print_unsigned(i_node_index, cv_number_format_dec());
            cv_print_nl();
#endif /* verbose */
            cv_heap_stress_node_toggle(a_node + i_node_index);
            i_node_index ++;
            if (i_node_index >= cv_heap_stress_max_node) {
                i_node_index = 0;
            }
            {
                unsigned int const i_delay_usec = cv_heap_stress_pick(1000);
                if (i_delay_usec > 800) {
                    cv_heap_stress_sleep_usec(i_delay_usec - 800UL);
                    cv_mutex_lock(&p_this->o_mutex);
                    b_continue = p_this->b_continue;
                    cv_mutex_unlock(&p_this->o_mutex);
                }
            }
        }
    }
    {
        i_node_index = 0;
        while (i_node_index < cv_heap_stress_max_node) {
            struct cv_heap_stress_node * const p_stress_node =
                a_node + i_node_index;
            cv_heap_stress_node_cleanup(p_stress_node);
            i_node_index ++;
        }
    }
    {
        i_node_index = 0;
        while (i_node_index < cv_heap_stress_max_node) {
            struct cv_heap_stress_node * const p_stress_node =
                a_node + i_node_index;
#if 0 /* verbose */
            cv_print_0("node=", 80);
            cv_print_unsigned(i_node_index, cv_number_format_dec());
            cv_print_0(",alloc=", 80);
            cv_print_unsigned(p_stress_node->i_alloc_count,
                cv_number_format_dec());
            cv_print_0(",free=", 80);
            cv_print_unsigned(p_stress_node->i_free_count,
                cv_number_format_dec());
            cv_print_nl();
#endif /* verbose */
#if 0
            cv_debug_assert_(
                p_stress_node->i_alloc_count,
                cv_debug_code_error);
#endif
            cv_debug_assert_(
                p_stress_node->i_alloc_count == p_stress_node->i_free_count,
                cv_debug_code_error);
            i_node_index ++;
        }
    }
}

cv_debug_decl_(cv_heap_stress_thread_class, "stress_heap",
    sizeof(struct cv_heap_stress_thread));

static void cv_heap_stress_thread_init(
    struct cv_heap_stress_thread * p_this, unsigned long i_seed) {
    cv_debug_construct_(cv_heap_stress_thread_class, p_this);
    cv_mutex_init(&p_this->o_mutex);
    cv_random_init(&p_this->o_random, i_seed);
    p_this->b_continue = cv_true;
    p_this->b_valid = cv_false;
}

static void cv_heap_stress_thread_cleanup(
    struct cv_heap_stress_thread * p_this) {
    if (p_this->b_valid) {
        cv_mutex_lock(&p_this->o_mutex);
        p_this->b_continue = cv_false;
        cv_mutex_unlock(&p_this->o_mutex);
        cv_thread_cleanup(&p_this->o_thread);
        p_this->b_valid = cv_false;
    }
    cv_random_cleanup(&p_this->o_random);
    cv_mutex_cleanup(&p_this->o_mutex);
    cv_debug_destruct_(cv_heap_stress_thread_class, p_this);
}

static void cv_heap_stress_thread_toggle(
    struct cv_heap_stress_thread * p_this) {

    if (p_this->b_valid) {
        cv_mutex_lock(&p_this->o_mutex);
        p_this->b_continue = cv_false;
        cv_mutex_unlock(&p_this->o_mutex);
        cv_thread_cleanup(&p_this->o_thread);
        p_this->b_valid = cv_false;
    } else {
        cv_thread_desc o_desc;
        cv_thread_desc_init(&o_desc);
        o_desc.o_callback.p_func = & cv_heap_stress_thread_entry;
        o_desc.o_callback.p_context = p_this;
        cv_thread_init(&p_this->o_thread, &o_desc);
        cv_thread_desc_cleanup(&o_desc);
        p_this->b_valid = cv_true;
    }
}

/*
 *
 */

struct cv_heap_stress_manager {
    struct cv_random o_random;
    struct cv_heap_stress_thread a_thread[cv_heap_stress_max_thread];
};

cv_debug_decl_(cv_heap_stress_manager_class, "stress_manager",
    sizeof(struct cv_heap_stress_manager));

static void cv_heap_stress_manager_init(
    struct cv_heap_stress_manager * p_this,
    unsigned long i_seed) {
    cv_debug_construct_(cv_heap_stress_manager_class, p_this);
    cv_random_init(&p_this->o_random, i_seed);
    {
        unsigned int i_index = 0;
        while (i_index < cv_heap_stress_max_thread) {
            struct cv_heap_stress_thread * const p_stress_thread =
                p_this->a_thread + i_index;
            unsigned long i_thread_seed = cv_random_pick(&p_this->o_random, 0);
            cv_heap_stress_thread_init(p_stress_thread, i_thread_seed);
            i_index ++;
        }
    }
}

static void cv_heap_stress_manager_cleanup(
    struct cv_heap_stress_manager * p_this) {
    unsigned int i_index = 0;
    while (i_index < cv_heap_stress_max_thread) {
        struct cv_heap_stress_thread * const p_stress_thread =
            p_this->a_thread + i_index;
        cv_heap_stress_thread_cleanup(p_stress_thread);
        i_index ++;
    }
    cv_random_cleanup(&p_this->o_random);
    cv_debug_destruct_(cv_heap_stress_manager_class, p_this);
}

static void cv_heap_stress_manager_run(
    struct cv_heap_stress_manager * p_this) {
    /* Start all threads */ {
        unsigned int i_index = 0;
        while (i_index < cv_heap_stress_max_thread) {
            struct cv_heap_stress_thread * const p_stress_thread =
                p_this->a_thread + i_index;
            cv_heap_stress_thread_toggle(p_stress_thread);
            i_index ++;
        }
    }
    /* Loop */ {
        unsigned long i_remain_usec = 0;
        i_remain_usec = 2000000UL;
        while (i_remain_usec) {
            /* wait a bit for thread to work */
            unsigned long i_sleep_usec = 0;
            i_sleep_usec = cv_heap_stress_pick(1000UL * 100UL);
            if (i_sleep_usec) {
                if (i_sleep_usec > i_remain_usec) {
                    i_sleep_usec = i_remain_usec;
                }
                cv_heap_stress_sleep_usec(i_sleep_usec);
                i_remain_usec -= i_sleep_usec;
            }
            /* Toggle a thread */
            {
                /* Randomly select a thread to start or stop */
                unsigned int i_index = cv_heap_stress_pick(
                    cv_heap_stress_max_thread);
                struct cv_heap_stress_thread * const p_stress_thread =
                    p_this->a_thread + i_index;
#if 0 /* verbose */
                cv_print_0("toggle thread ", 80);
                cv_print_unsigned(i_index, cv_number_format_dec());
                cv_print_nl();
#endif /* verbose */
                cv_heap_stress_thread_toggle(p_stress_thread);
            }
        }
    }
}

/*
 *
 */

static void cv_heap_test_stress(cv_options_it * p_options_it) {
    static struct cv_heap_stress_manager o_stress_manager;
    /* create threads */
    /* allocate memory */
    /* write memory */
    /* read memory */
    /* free memory */
    /* sleep */
    (void)p_options_it;
    cv_mutex_init(&g_random_lock);
    /* Grab seed from options... */
    {
        unsigned long i_manager_seed = 12345;
        struct cv_random_crypto o_crypto;
        if (cv_random_crypto_init(&o_crypto)) {
            i_manager_seed = cv_random_crypto_pick(&o_crypto, 0);
            cv_random_crypto_cleanup(&o_crypto);
        } else {
            cv_clock_mono o_clock_mono;
            if (cv_clock_mono_read(&o_clock_mono)) {
                i_manager_seed = o_clock_mono.o_clock.i_fraction;
            }
        }
        cv_heap_stress_manager_init(&o_stress_manager, i_manager_seed);
    }
    cv_heap_stress_manager_run(&o_stress_manager);
    cv_heap_stress_manager_cleanup(&o_stress_manager);
    cv_mutex_cleanup(&g_random_lock);
}

/*
 *
 */

void cv_heap_test(cv_options_it * p_options_it) {
    static unsigned char const a_stress[] = {
        's', 't', 'r', 'e', 's', 's' };
    static cv_array const g_stress =
        cv_array_text_initializer_(a_stress);
    cv_array o_argument;
    cv_array_init(&o_argument);
    if (cv_options_it_next(p_options_it, &o_argument)) {
        if (cv_array_compare(&o_argument, &g_stress)) {
            cv_heap_test_stress(p_options_it);
        } else {
        }
    } else {
    }
    cv_array_cleanup(&o_argument);
}

/* end-of-file: cv_heap_test.c */
