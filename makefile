# See LICENSE for license details

#
# GNU makefile for build of library
#

cv_src_path ?= .

cv_dst_path ?= .

cv_test_srcs = \
    cv_test.c \
    cv_main.c \
    cv_string.c \
    cv_string0.c \
    cv_string1.c \
    cv_manager.c \
    cv_options_desc.c \
    cv_options.c \
    cv_options_it.c \
    cv_options_node.c \
    cv_heap.c \
    cv_heap_primary.c \
    cv_heap_node.c \
    cv_heap_node_ptr.c \
    cv_heap_pool.c \
    cv_heap_it.c \
    cv_heap_small.c \
    cv_heap_large.c \
    cv_debug.c \
    cv_thread_desc.c \
    cv_thread.c \
    cv_thread_impl.c \
    cv_memory.c \
    cv_clock.c \
    cv_node.c \
    cv_node_it.c \
    cv_list.c \
    cv_mutex.c \
    cv_mutex_pool.c \
    cv_mutex_mgr.c \

cv_test_srcs_abs = $(addprefix $(cv_src_path)/,$(cv_test_srcs))

cv_profile_cflags = \
    -pg \
    -ftest-coverage \
    -fprofile-arcs \

cv_cflags = \
    -g \
    -O2 \
    -no-pie \
    -fno-pie \
    -fno-stack-protector \
    -fno-unwind-tables \
    -fno-asynchronous-unwind-tables \
    -D _DEFAULT_SOURCE \
    -D cv_debug_ \
    -D cv_have_libc_ \
    -I . \
    -ansi \
    -pedantic \
    -Wall \
    -Wextra \
    -Wabi \
    -Waggregate-return \
    -Warray-bounds \
    -Wattributes \
    -Wbuiltin-macro-redefined \
    -Wcast-align \
    -Wcast-qual \
    -Wconversion \
    -Wdeprecated \
    -Wdiv-by-zero \
    -Wendif-labels \
    -Wfloat-equal \
    -Wformat-contains-nul \
    -Wformat-extra-args \
    -Wformat-nonliteral \
    -Wformat-security \
    -Wformat-y2k \
    -Wlarger-than=4096 \
    -Wlong-long \
    -Wmissing-declarations \
    -Wmissing-format-attribute \
    -Wmissing-include-dirs \
    -Wmultichar \
    -Woverflow \
    -Woverlength-strings \
    -Wpacked \
    -Wpacked-bitfield-compat \
    -Wpadded \
    -Wpointer-arith \
    -Wpragmas \
    -Wredundant-decls \
    -Wsequence-point \
    -Wshadow \
    -Wstrict-overflow=2 \
    -Wsync-nand \
    -Wundef \
    -Wunused \
    -Wunused-macros \
    -Wunused-result \
    -Wvariadic-macros \
    -Wvla \
    -Wwrite-strings

.PHONY : all
all : $(cv_dst_path)/test.exe
$(cv_dst_path)/test.exe : $(cv_src_path)/makefile
$(cv_dst_path)/test.exe : $(cv_test_srcs_abs)
$(cv_dst_path)/test.exe :
	gcc -x c -o $(cv_dst_path)/test.exe $(cv_cflags) $(cv_test_srcs_abs) -lpthread
	gcc -x c++ -o $(cv_dst_path)/test.cxx.exe -fno-rtti -fno-exceptions -Wold-style-cast $(cv_cflags) $(cv_test_srcs_abs) -lpthread

