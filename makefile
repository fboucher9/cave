# See LICENSE for license details

#
# GNU makefile for build of library
#

cv_src_path ?= .

cv_dst_path ?= .

cv_test_srcs = \
    cv_test_os.c \
    cv_test.c \
    cv_test_print.c \
    cv_main.c \
    cv_array.c \
    cv_array_it.c \
    cv_array_tool.c \
    cv_buffer.c \
    cv_convert.c \
    cv_convert_test.c \
    cv_string0.c \
    cv_string_it.c \
    cv_manager.c \
    cv_options_desc.c \
    cv_options.c \
    cv_options_it.c \
    cv_options_node.c \
    cv_options_pool.c \
    cv_heap.c \
    cv_heap_primary.c \
    cv_heap_node.c \
    cv_heap_node_ptr.c \
    cv_heap_pool.c \
    cv_heap_it.c \
    cv_heap_section.c \
    cv_heap_small.c \
    cv_heap_large.c \
    cv_debug.c \
    cv_sizeof.c \
    cv_thread_desc.c \
    cv_thread.c \
    cv_thread_impl.c \
    cv_memory.c \
    cv_number_desc.c \
    cv_number_enc.c \
    cv_clock.c \
    cv_list_node.c \
    cv_list_it.c \
    cv_list_root.c \
    cv_stack.c \
    cv_stack_it.c \
    cv_stack_test.c \
    cv_mutex.c \
    cv_mutex_pool.c \
    cv_mutex_mgr.c \
    cv_file.c \
    cv_file_std.c \
    cv_file_disk_desc.c \
    cv_file_disk.c \
    cv_file_poll.c \
    cv_file_print.c \
    cv_file_test.c \
    cv_runtime.c \
    cv_linux.c \
    cv_windows.c \

cv_test_srcs_abs = $(addprefix $(cv_src_path)/,$(cv_test_srcs))

cv_test_objs = $(addsuffix .o,$(cv_test_srcs))

cv_test_objs_abs = $(addprefix $(cv_dst_path)/.obj/,$(cv_test_objs))

cv_test_deps = $(addsuffix .d,$(cv_test_srcs))

cv_test_deps_abs = $(addprefix $(cv_dst_path)/.obj/,$(cv_test_deps))

cv_profile_cflags = \
    -pg \
    -ftest-coverage \
    -fprofile-arcs \

cv_defines = \
    -D _DEFAULT_SOURCE \
    -D cv_debug_ \
    -D cv_linux_ \
    -D cv_have_libc_ \
    -D cv_have_pthread_ \

cv_includes = \
    -I .

cv_cflags = \
    -g \
    -O0 \
    -no-pie \
    -fno-pie \
    -fno-stack-protector \
    -fno-unwind-tables \
    -fno-asynchronous-unwind-tables \
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

cv_verbose ?= @

.PHONY : test all clang mingw bare
test : $(cv_dst_path)/test.exe

all : $(cv_dst_path)/test.exe
all : $(cv_dst_path)/test.m64.exe
all : $(cv_dst_path)/test.cxx.exe
all : clang
clang : $(cv_dst_path)/test.clang.exe
clang : $(cv_dst_path)/test.clangxx.exe
all : mingw
mingw : $(cv_dst_path)/test.mingw.exe
mingw : $(cv_dst_path)/test.mingwxx.exe
all : bare
bare : $(cv_dst_path)/test.bare.exe

$(cv_dst_path)/test.exe : $(cv_src_path)/makefile $(cv_test_objs_abs)
	@echo linking $(notdir $@)
	$(cv_verbose)echo -m32 -o $(cv_dst_path)/test.exe $(cv_cflags) -rdynamic $(cv_test_objs_abs) -lpthread > $(cv_dst_path)/.obj/link.cmd
	$(cv_verbose)gcc @$(cv_dst_path)/.obj/link.cmd

$(cv_test_objs_abs) : $(cv_src_path)/makefile

$(cv_dst_path)/.obj/%.c.o : $(cv_src_path)/%.c
	@echo compiling $(notdir $<)
	$(cv_verbose)mkdir -p $(cv_dst_path)/.obj
	$(cv_verbose)echo -c -m32 -x c -o $@ $(cv_cflags) $(cv_defines) $(cv_includes) $< -MMD > $@.cmd
	$(cv_verbose)gcc @$@.cmd

$(cv_dst_path)/test.m64.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	gcc -m64 -x c -o $(cv_dst_path)/test.m64.exe $(cv_cflags) $(cv_defines) $(cv_includes) $(cv_test_srcs_abs) -lpthread

$(cv_dst_path)/test.cxx.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	g++ -x c++ -o $(cv_dst_path)/test.cxx.exe -fno-rtti -fno-exceptions -Wold-style-cast $(cv_cflags) $(cv_defines) $(cv_includes) $(cv_test_srcs_abs) -lpthread

$(cv_dst_path)/test.mingw.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	i686-w64-mingw32-gcc -x c -o $(cv_dst_path)/test.mingw.exe $(cv_cflags) -D cv_debug_ -D cv_windows_ -D cv_have_libc_ $(cv_includes) $(cv_test_srcs_abs) -lpthread

$(cv_dst_path)/test.mingwxx.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	i686-w64-mingw32-g++ -x c++ -o $(cv_dst_path)/test.mingwxx.exe -fno-rtti -fno-exceptions -Wold-style-cast $(cv_cflags) -D cv_debug_ -D cv_windows_ -D cv_have_libc_ $(cv_includes) $(cv_test_srcs_abs) -lpthread

$(cv_dst_path)/test.clang.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	clang -x c -o $(cv_dst_path)/test.clang.exe -ansi -pedantic -Weverything $(cv_defines) $(cv_includes) $(cv_test_srcs_abs) -lpthread

$(cv_dst_path)/test.clangxx.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	clang++ -x c++ -o $(cv_dst_path)/test.clangxx.exe -fno-rtti -fno-exceptions -ansi -pedantic -Weverything $(cv_defines) $(cv_includes) $(cv_test_srcs_abs) -lpthread

$(cv_dst_path)/test.bare.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	gcc -m64 -x c -o $(cv_dst_path)/test.bare.exe -I . -D cv_debug_ -ansi -pedantic -nostdinc -Wall -Wextra -fno-stack-protector $(cv_test_srcs_abs) -nodefaultlibs -nostartfiles

-include $(cv_test_deps_abs)
