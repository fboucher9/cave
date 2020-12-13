

/* Compression of log lines */

/* Use of markup to store strings and numbers into a log message */


struct cv_trace_message {
    unsigned char a_length[2];
    unsigned char a_process_index[2u];
    unsigned char a_thread_index[2u];
    unsigned char a_function_name[2u];
    unsigned char a_clock[8u];
    unsigned char a_mixed_text[n];
};

/* Use of unicode */

/*
 *  0-31    Number
 *  32-127  Text
 *  128-    Numbers 32+
 */

/* 0x10xxxxxx */

void cv_trace_print_begin( cv_array const * p_array);

void cv_trace_print_array( cv_array const * p_array);

void cv_trace_print_number( cv_ull ll_number);

void cv_trace_print_end(void);

