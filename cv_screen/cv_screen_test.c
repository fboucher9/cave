/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_test.h>
#include <cv_screen/cv_screen_device.h>
#include <cv_screen/cv_screen_device_desc.h>
#include <cv_screen/cv_screen_window.h>
#include <cv_screen/cv_screen_window_desc.h>
#include <cv_file/cv_file_std.h>
#include <cv_file/cv_file_poll.h>
#include <cv_test_print.h>
#include <cv_runtime.h>
#include <cv_algo/cv_array.h>

/*
 *
 */

void cv_screen_test(void) {
    cv_screen_device_desc o_device_desc;
    cv_screen_device_desc_init(&o_device_desc);
    o_device_desc.p_file = cv_file_std_out();
    o_device_desc.i_key_count = 64;
    o_device_desc.i_attribute_count = 16;
    o_device_desc.i_glyph_count = 128;
    o_device_desc.i_window_count = 4;
    o_device_desc.i_width = 50;
    o_device_desc.i_height = 14;
    {
        cv_screen_device * p_device = 0;
        p_device = cv_screen_device_create(&o_device_desc);
        if (p_device) {
            /* setup attributes */
            /* setup keys */
            {
            }
            /* setup glyphs */
            /* setup windows */


            cv_print_0("before", 80);
            cv_print_nl();
            cv_screen_device_enter(p_device);
            cv_print_0("\033[?25l", 80);
            cv_print_0("during\r\n", 80);
            cv_print_0("\n\n\n\n\n\n\n\n\n\n\033[10A", 80);

            {
                cv_screen_window_desc o_desc;
                cv_screen_window * p_root = 0;
                cv_screen_window_desc_init(&o_desc);
                o_desc.i_width = 40;
                o_desc.i_height = 10;
                o_desc.i_left = 5;
                o_desc.i_top = 2;
                p_root = cv_screen_window_create( &o_desc);
                if (p_root) {
                    cv_bool b_continue = cv_true;
                    unsigned short i_player_x = 20;
                    unsigned short i_player_y = 5;
                    while (b_continue) {
                        cv_bool b_render = cv_false;
                        cv_file_poll a_poll[1u];
                        cv_file_poll_init(&a_poll[0u]);
                        a_poll[0u].p_file = cv_file_std_in();
                        a_poll[0u].i_flags_in = cv_file_poll_flag_read;
                        if (cv_file_poll_dispatch(a_poll, 1, 0)) {
                            static unsigned char a_buffer[32u];
                            cv_array o_buffer;
                            cv_uptr i_buffer_len = 0;
                            cv_runtime_memset(a_buffer, 0, sizeof(a_buffer));
                            cv_array_init_vector(&o_buffer, a_buffer, sizeof(a_buffer));
                            i_buffer_len = cv_screen_device_read(p_device, &o_buffer);
                            if (i_buffer_len) {
                                cv_uptr i_buffer_iterator = 0;
                                while (i_buffer_iterator < i_buffer_len) {
                                    unsigned char const c_token = a_buffer[i_buffer_iterator];
                                    if (i_buffer_iterator) {
                                        cv_print_0(", ", 80);
                                    }
                                    if ((32 <= c_token) &&
                                        (127 > c_token)) {
                                        cv_print_char('\'');
                                        cv_print_char(c_token);
                                        cv_print_char('\'');
                                        if ('w' == c_token) {
                                            if (i_player_y > 0) {
                                                i_player_y --;
                                            }
                                        } else if ('a' == c_token) {
                                            if (i_player_x > 0) {
                                                i_player_x --;
                                            }
                                        } else if ('s' == c_token) {
                                            if ((i_player_y + 1) < 10) {
                                                i_player_y ++;
                                            }
                                        } else if ('d' == c_token) {
                                            if ((i_player_x + 1) < 40) {
                                                i_player_x ++;
                                            }
                                        }
                                    } else {
                                        cv_print_0("0x", 80);
                                        cv_print_hex(c_token);
                                    }
                                    i_buffer_iterator ++;
                                }
                                cv_print_0("\033[K\r\n", 80);
                                b_render = cv_true;
                                if ('q' == a_buffer[0u]) {
                                    b_continue = cv_false;
                                }
                            }
                            cv_array_cleanup(&o_buffer);
                        } else {
                            /* timeout ... */
                        }

                        if (b_render) {
                            /* fill in windows */
                            /* modify windows */
                            cv_screen_window_goto(p_root,
                                i_player_x, i_player_y);
                            cv_screen_window_attribute(p_root, 2);
                            cv_screen_window_write(p_root, 'F');

                            /* render of screen */
                            cv_screen_device_set_window(p_device, 0, p_root);
                            cv_screen_device_apply(p_device);
                            cv_screen_device_set_window(p_device, 0, 0);
                            cv_screen_window_goto(p_root,
                                i_player_x, i_player_y);
                            cv_screen_window_attribute(p_root, 2);
                            cv_screen_window_write(p_root, 'f');
                        }


                        cv_file_poll_cleanup(&a_poll[0u]);
                    }
                    cv_screen_window_destroy(p_root);
                }
                cv_screen_window_desc_cleanup(&o_desc);
            }


            cv_screen_device_leave(p_device);
            cv_print_0("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", 80);
            cv_print_0("\033[?25h", 80);
            cv_print_0("after", 80);
            cv_print_nl();
            cv_screen_device_destroy(p_device);
        }
    }
    cv_screen_device_desc_cleanup(&o_device_desc);
}

/* end-of-file: cv_screen_test.c */
