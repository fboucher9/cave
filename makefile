# See LICENSE for license details

#
# GNU makefile for build of library
#
#
cv_src_path = .

cv_dst_path = .

cv_test_srcs = \
$(cv_src_path)/cv_test.c \
$(cv_src_path)/cv_main.c \
$(cv_src_path)/cv_string.c \
$(cv_src_path)/cv_string0.c \
$(cv_src_path)/cv_manager.c \
$(cv_src_path)/cv_options_desc.c \
$(cv_src_path)/cv_options.c \
$(cv_src_path)/cv_options_it.c \
$(cv_src_path)/cv_heap.c \
$(cv_src_path)/cv_debug.c \
$(cv_src_path)/cv_thread_desc.c \
$(cv_src_path)/cv_thread.c \
$(cv_src_path)/cv_thread_impl.c \
$(cv_src_path)/cv_memory.c \
$(cv_src_path)/cv_clock.c \

cv_profile_cflags = \
    -pg \
    -ftest-coverage \
    -fprofile-arcs \

cv_cflags = \
    -g \
    -O0 \
    -no-pie \
    -fno-unwind-tables \
    -fno-asynchronous-unwind-tables \
    -D _DEFAULT_SOURCE \
    -D cv_debug_ \
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
    -Wstrict-overflow=5 \
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
$(cv_dst_path)/test.exe : $(cv_test_srcs)
$(cv_dst_path)/test.exe :
	gcc -x c -o $(cv_dst_path)/test.exe $(cv_cflags) $(cv_test_srcs) -lpthread
	gcc -x c++ -o $(cv_dst_path)/test.cxx.exe -fno-rtti -fno-exceptions $(cv_cflags) $(cv_test_srcs) -lpthread

