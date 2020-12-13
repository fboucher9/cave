

memory mapped binary file

split the file into objects

struct cv_trace_object {
    uint32_t i_magic;
    uint32_t i_length;
};

struct cv_trace_section_object {
    struct cv_trace_object o_object;
    uint16_t i_offset;
    uint16_t i_count;
    uint16_t a_padding[2];
    struct cv_trace_section_node {
        uint16_t i_length;
        uint16_t i_process;
        uint16_t i_thread;
        uint16_t i_name;
        uint64_t i_tick;
        char c_text[];
    };
};

struct cv_trace_process_object {
    struct cv_trace_object o_object;
    uint16_t i_offset;
    uint16_t a_padding[3];
    struct cv_trace_process_node {
        uint16_t i_unique;
        uint16_t a_padding[3];
        uint64_t i_pid;
    };
};

struct cv_trace_thread_object {
    struct cv_trace_object o_object;
    uint16_t i_offset;
    uint16_t a_padding[3];
    struct cv_trace_thread_node {
        uint16_t i_unique;
        uint16_t a_padding[3];
        uint64_t i_tid;
    };
};

struct cv_trace_clock_object {
    struct cv_trace_object o_object;
    uint16_t i_offset;
    uint16_t a_padding[3];
    struct cv_trace_clock_node {
        uint16_t i_process;
        uint16_t a_padding[3];
        uint64_t i_clock;
        uint64_t i_tick;
    };
};

struct cv_trace_name_object {
    struct cv_trace_object o_object;
    struct cv_trace_name_node {
        uint16_t i_process;
        uint16_t i_unique;
        uint16_t i_parent;
        uint16_t i_text_len;
        char a_text[32];
    };
};

struct cv_trace_event_object {
    struct cv_trace_object o_object;
    uint16_t i_offset;
    uint16_t i_count;
    uint16_t a_padding[2];
    struct cv_trace_event_node {
        uint16_t i_event_unique;
        uint16_t i_process_unique;
        uint16_t i_name_unique;
        uint16_t e_value_type;
        uint64_t i_count;
        uint64_t i_value;
    };
};

#if 0

struct cv_trace_object {
    cv_uint32_t i_magic;
    cv_uint32_t i_length;
};

struct cv_trace_number_object {
    cv_trace_object o_object;
    cv_uint64_t i_value;
};

struct cv_trace_string_object {
    cv_trace_object o_object;
    char c_payload[];
};

struct cv_trace_clock_object {
    cv_trace_object o_object;
    cv_uint64_t i_value;
};


typedef struct cv_trace_buffer {

} cv_trace_buffer;


/*
 *
 */

typedef struct cv_trace_root {

    struct cv_trace_process_root {
        uint16_t i_position;
        uint16_t i_length;
        uint16_t i_current_process_unique;
        uint16_t s_padding[1u];
        uint32_t i_current_process_handle;
        uint32_t i_padding[1u];
        struct cv_trace_process_node {
            uint16_t i_process_unique;
            uint16_t s_padding[1u];
            uint32_t i_process_handle;
        };
    } o_process;

    struct cv_trace_thread_root {
        uint16_t i_position;
        uint16_t i_length;
        uint16_t i_current_thread_unique;
        uint16_t s_padding[1u];
        struct cv_trace_thread_node {
            uint16_t i_thread_unique;
            uint16_t i_process_unique;
            uint16_t s_padding[2u];
            uint32_t i_thread_handle;
            uint32_t i_padding[1u];
        };
    } o_thread;

    struct cv_trace_clock_root {
        uint16_t i_position;
        uint16_t i_length;
        uint16_t i_clock_unique;
        uint16_t s_padding[1u];
        struct cv_trace_clock_node {
            uint16_t i_clock_unique;
            uint16_t s_padding[3u];
            uint64_t i_tick_ref;
            uint64_t i_clock_ref;
        };
    } o_clock;

    struct cv_trace_name_root {
        uint16_t i_position;
        uint16_t i_length;
        uint16_t i_name_unique;
        uint16_t s_padding[1u];
        struct cv_trace_name_node {
            uint16_t i_name_unique;
            uint16_t i_parent_name_unique;
            uint16_t s_padding[1u];
            char a_name_text[16];
        };
    } o_name;

    struct cv_trace_event_root {
        uint16_t i_position;
        uint16_t i_length;
        uint16_t i_unique;
        uint16_t s_padding[1u];
        struct cv_trace_event_node {
            uint16_t i_event_unique;
            uint16_t i_name_unique;
            uint16_t e_value_type;
            uint16_t a_padding[1u];
            uint64_t i_count;
            uint64_t i_value;
        };
    } o_event;

    struct cv_trace_section_root {
        uint16_t i_position;
        uint16_t i_length;
        uint32_t i_offset;
        uint64_t i_flags;
        char a_name [32];
        struct cv_trace_section_node {
            uint16_t i_length;
            uint16_t i_thread_unique;
            uint16_t i_name_unique;
            uint16_t s_padding[1];
            uint64_t i_tick;
            char c_message[];
        };
    } a_section[32];

} cv_trace_root;

#endif



/* report is done once every 10 seconds, so compression may be done */
/* first trick is the delta, it brings numbers close to zero. */
/* second trick is unicode encoding, numbers close to zero require less bytes */
/* third trick is scaling, by ignoring least significant bits */
struct cv_trace_stat_report {
    uint16_t i_process_unique;
    uint16_t i_count;
    uint64_t i_tick;
    struct cv_trace_stat_sector {
        uint16_t i_count;
        uint16_t i_process_unique;
        uint32_t i_flags;
        struct cv_trace_stat_node {
            unsigned char a_count_delta[n];
            unsigned char a_value_delta[n];
        } a_events[];
    };
};

/* minimum of 6 bytes per event */
/* 20 events means 120 bytes per report */

