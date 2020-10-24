/* See LICENSE for license details */

/*
 *
 */

#include <cv_screen/cv_screen_test.h>
#include <cv_screen/cv_screen_device.h>
#include <cv_screen/cv_screen_device_desc.h>
#include <cv_file/cv_file_std.h>
#include <cv_test_print.h>

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
            cv_print_0("before", 80);
            cv_print_nl();
            cv_screen_device_enter(p_device);
            cv_print_0("during", 80);
            cv_print_nl();
            cv_screen_device_leave(p_device);
            cv_print_0("after", 80);
            cv_print_nl();
            cv_screen_device_destroy(p_device);
        }
    }
    cv_screen_device_desc_cleanup(&o_device_desc);
}

/* end-of-file: cv_screen_test.c */
