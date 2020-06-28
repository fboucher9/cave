/* See LICENSE for license details */

#include <cv_screen/cv_screen_linux.h>
#if defined cv_linux_
#include <cv_misc/cv_bool.h>
#include <cv_file/cv_file.h>
#include <cv_heap/cv_heap.h>
#include <unistd.h>
#include <termios.h>

union cv_screen_termios_storage {
    struct termios o_data;
    /* -- */
    void * a_padding[
        (sizeof(struct termios) + sizeof(void *) - 1) / sizeof(void *)];
};

struct cv_screen_raw {
    cv_file const * p_file;
    /* -- */
    union cv_screen_termios_storage o_termios_storage;
};

union cv_screen_raw_ptr {
    void const * pc_void;
    void * p_void;
    struct cv_screen_raw const * pc_screen_raw;
    struct cv_screen_raw * p_screen_raw;
};

static cv_bool cv_screen_raw_init( struct cv_screen_raw * p_this,
    cv_file const * p_file) {
    cv_bool b_result = cv_false;
    p_this->p_file = p_file;
    {
        int const i_tty_fd =
            cv_file_get_index(p_this->p_file);
        if (isatty(i_tty_fd)) {
            int const i_tcgetattr_result =
                tcgetattr(i_tty_fd, &p_this->o_termios_storage.o_data);
            if (0 <= i_tcgetattr_result) {
                struct termios o_termios_raw = {0};
                o_termios_raw = p_this->o_termios_storage.o_data;
                cfmakeraw(&o_termios_raw);
                {
                    int const i_tcsetattr_result =
                        tcsetattr(i_tty_fd, TCSADRAIN, &o_termios_raw);
                    if (0 <= i_tcsetattr_result) {
                        b_result = cv_true;
                    }
                }
            } else {
                b_result = cv_false;
            }
        } else {
            b_result = cv_false;
        }
    }
    return b_result;
}

static void cv_screen_raw_cleanup(struct cv_screen_raw * p_this) {
    int const i_tty_fd = cv_file_get_index(p_this->p_file);
    int const i_tcsetattr_result = tcsetattr( i_tty_fd, TCSADRAIN,
            &p_this->o_termios_storage.o_data);
    if (0 <= i_tcsetattr_result) {
    }
}

struct cv_screen_raw * cv_screen_raw_create(cv_file const * p_file) {
    union cv_screen_raw_ptr o_ptr = {0};
    cv_uptr const i_placement_len = sizeof(struct cv_screen_raw);
    o_ptr.p_void = cv_heap_alloc(i_placement_len);
    if (o_ptr.p_void) {
        if (cv_screen_raw_init(o_ptr.p_screen_raw, p_file)) {
        } else {
            cv_heap_free(o_ptr.p_void);
            o_ptr.p_void = 0;
        }
    }
    return o_ptr.p_screen_raw;
}

void cv_screen_raw_destroy(struct cv_screen_raw * p_screen_raw) {
    cv_screen_raw_cleanup(p_screen_raw);
    {
        union cv_screen_raw_ptr o_ptr = {0};
        o_ptr.p_screen_raw = p_screen_raw;
        cv_heap_free(o_ptr.p_void);
    }
}

#endif /* #if defined cv_linux_ */

/* end-of-file: cv_screen_linux.c */
