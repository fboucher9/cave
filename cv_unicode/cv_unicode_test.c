/* See LICENSE for license details */

/*
 *
 */

#include <cv_unicode/cv_unicode_test.h>
#include <cv_unicode/cv_utf16.h>
#include <cv_unicode/cv_utf16be_decoder.h>
#include <cv_unicode/cv_utf8_decoder.h>
#include <cv_unicode/cv_utf8_encoder.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_it.h>
#include <cv_test_print.h>

static void step_utf16be_decoder(
    cv_utf16be_decoder * p_this,
    unsigned char i_input) {
    if (cv_utf16be_decoder_produce(p_this, i_input)) {
        unsigned long i_output = 0;
        if (cv_utf16be_decoder_consume(p_this, &i_output)) {
            cv_print_0("0x", 80);
            cv_print_hex(i_output);
            if (i_output <= 0x10fffful) {
            } else {
                cv_print_char('!');
            }
            cv_print_nl();
        }
    }
}

static void step_utf8_decoder(
    cv_utf8_decoder * p_this,
    unsigned char i_input) {
    if (cv_utf8_decoder_produce(p_this, i_input)) {
        unsigned long i_output = 0;
        if (cv_utf8_decoder_consume(p_this, &i_output)) {
            cv_print_0("0x", 80);
            cv_print_hex(i_output);
            if (i_output <= 0x10fffful) {
            } else {
                cv_print_char('!');
            }
            cv_print_nl();
        }
    }
}

static void step_utf8_encoder(
    cv_utf8_encoder * p_this,
    unsigned long i_input) {
    cv_uptr i_count = cv_utf8_encoder_produce(p_this, i_input);
    if (i_count) {
        cv_uptr i_index = 0;
        while (i_count --) {
            unsigned char i_output = 0;
            cv_utf8_encoder_consume(p_this, &i_output);
            cv_print_0("0x", 80);
            cv_print_hex(i_output);
            if (0 == i_index) {
                if ((0xc0 <= i_output) && (0xf7 >= i_output)) {
                } else {
                    cv_print_char('!');
                }
            } else {
                if ((0x80 <= i_output) && (0xc0 > i_output)) {
                } else {
                    cv_print_char('!');
                }
            }
            if (i_count) {
                cv_print_char(',');
            }
            cv_print_char(' ');
            i_index ++;
        }
        cv_print_nl();
    }
}

/*
 *
 */

void cv_unicode_test(void) {
    {
        static unsigned char const a_input[] = {
            0x12, 0x34
        };
        static cv_array const g_input =
            cv_array_initializer_(a_input, a_input + sizeof a_input);
        cv_array_it o_input;
        cv_array_it_init(&o_input, &g_input);
        {
            unsigned long i_output = 0;
            if (cv_utf16be_decode(&o_input, &i_output)) {
                cv_print_0("0x", 80);
                cv_print_hex(i_output);
                cv_print_nl();
            }
        }
        cv_array_it_cleanup(&o_input);
    }

    {
        unsigned char a_storage[2u];
        cv_array o_storage;
        cv_array_it o_output;
        cv_array_init_vector(&o_storage, a_storage, sizeof a_storage);
        cv_array_it_init(&o_output, &o_storage);
        {
            if (cv_utf16be_encode(0x1234ul, &o_output)) {
                cv_print_0("0x", 80);
                cv_print_hex(a_storage[0u]);
                cv_print_0(", 0x", 80);
                cv_print_hex(a_storage[1u]);
                cv_print_nl();
            }
        }
        cv_array_it_cleanup(&o_output);
        cv_array_cleanup(&o_storage);
    }

    {
        cv_utf16be_decoder o_decoder;
        cv_utf16be_decoder_init(&o_decoder);
        step_utf16be_decoder(&o_decoder, 0x12);
        step_utf16be_decoder(&o_decoder, 0x34);
        step_utf16be_decoder(&o_decoder, 0xd8);
        step_utf16be_decoder(&o_decoder, 0x00);
        step_utf16be_decoder(&o_decoder, 0xdc);
        step_utf16be_decoder(&o_decoder, 0x00);
        step_utf16be_decoder(&o_decoder, 0xdb);
        step_utf16be_decoder(&o_decoder, 0xff);
        step_utf16be_decoder(&o_decoder, 0xdf);
        step_utf16be_decoder(&o_decoder, 0xff);
        cv_utf16be_decoder_cleanup(&o_decoder);
    }

    {
        cv_utf8_decoder o_decoder;
        cv_utf8_decoder_init(&o_decoder);
        step_utf8_decoder(&o_decoder, 0xe1);
        step_utf8_decoder(&o_decoder, 0x88);
        step_utf8_decoder(&o_decoder, 0xb4);
        step_utf8_decoder(&o_decoder, 0xf4);
        step_utf8_decoder(&o_decoder, 0x8f);
        step_utf8_decoder(&o_decoder, 0xbf);
        step_utf8_decoder(&o_decoder, 0xbf);
        cv_utf8_decoder_cleanup(&o_decoder);
    }
    {
        cv_utf8_encoder o_encoder;
        cv_utf8_encoder_init(&o_encoder);
        step_utf8_encoder(&o_encoder, 0x1234);
        step_utf8_encoder(&o_encoder, 0x10000);
        step_utf8_encoder(&o_encoder, 0x10ffff);
        step_utf8_encoder(&o_encoder, 0x1fffff);
        cv_utf8_encoder_cleanup(&o_encoder);
    }
}

/* end-of-file: cv_unicode_test.c */
