/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_test.h>
#include <cv_screen/cv_screen_device.h>
#include <cv_screen/cv_screen_device_desc.h>
#include <cv_file/cv_file_std.h>
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
    o_device_desc.i_width = 80;
    o_device_desc.i_height = 24;
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
            cv_print_0("during\r\n", 80);

            {
                cv_bool b_continue = cv_true;
                while (b_continue) {
                    static unsigned char a_buffer[32u];
                    unsigned short i_key = 0;
                    cv_array o_buffer;
                    cv_uptr i_buffer_len = 0;
                    cv_runtime_memset(a_buffer, 0, sizeof(a_buffer));
                    cv_array_init_vector(&o_buffer, a_buffer, sizeof(a_buffer));
                    i_buffer_len = cv_screen_device_read(p_device, &o_buffer, &i_key);
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
                            } else {
                                cv_print_0("0x", 80);
                                cv_print_hex(c_token);
                            }
                            i_buffer_iterator ++;
                        }
                        cv_print_0("\r\n", 80);
                        if ('q' == a_buffer[0u]) {
                            b_continue = cv_false;
                        }
                    } else {
                        cv_print_0("err!\r\n", 80);
                    }
                    cv_array_cleanup(&o_buffer);
                }
            }

            /* fill in windows */
            /* render of screen */
            /* modify windows */
            /* render of screen */

            cv_screen_device_leave(p_device);
            cv_print_0("after", 80);
            cv_print_nl();
            cv_screen_device_destroy(p_device);
        }
    }
    cv_screen_device_desc_cleanup(&o_device_desc);
}

/* end-of-file: cv_screen_test.c */
