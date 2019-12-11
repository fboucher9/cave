# See LICENSE for license details

#
# GNU makefile for build of library
#

cv_src_path ?= .

cv_dst_path ?= .

cv_obj_path ?= $(cv_dst_path)/.obj

cv_test_srcs = \
    cv_test_os.c \
    cv_test.c \
    cv_test_print.c \
    cv_main.c \
    cv_algo/cv_array.c \
    cv_algo/cv_array_it.c \
    cv_algo/cv_array_tool.c \
    cv_algo/cv_buffer.c \
    cv_misc/cv_convert.c \
    cv_misc/cv_convert_test.c \
    cv_algo/cv_string0.c \
    cv_manager.c \
    cv_options/cv_options_desc.c \
    cv_options/cv_options.c \
    cv_options/cv_options_it.c \
    cv_options/cv_options_node.c \
    cv_options/cv_options_pool.c \
    cv_heap/cv_heap.c \
    cv_heap/cv_heap_primary.c \
    cv_heap/cv_heap_secondary.c \
    cv_heap/cv_heap_node.c \
    cv_heap/cv_heap_node_ptr.c \
    cv_heap/cv_heap_pool.c \
    cv_heap/cv_heap_it.c \
    cv_heap/cv_heap_section.c \
    cv_heap/cv_heap_section_lock.c \
    cv_heap/cv_heap_small.c \
    cv_heap/cv_heap_large.c \
    cv_heap/cv_heap_used.c \
    cv_debug.c \
    cv_misc/cv_sizeof.c \
    cv_thread/cv_thread_desc.c \
    cv_thread/cv_thread.c \
    cv_thread/cv_thread_impl.c \
    cv_memory.c \
    cv_number_desc.c \
    cv_number_enc.c \
    cv_clock/cv_clock.c \
    cv_clock/cv_clock_mono.c \
    cv_clock/cv_clock_test.c \
    cv_algo/cv_list_node.c \
    cv_algo/cv_list_it.c \
    cv_algo/cv_list_root.c \
    cv_algo/cv_stack.c \
    cv_algo/cv_stack_it.c \
    cv_algo/cv_stack_test.c \
    cv_thread/cv_mutex.c \
    cv_algo/cv_pool.c \
    cv_algo/cv_pool_desc.c \
    cv_algo/cv_pool_lock.c \
    cv_file/cv_file.c \
    cv_file/cv_file_std.c \
    cv_file/cv_file_disk_desc.c \
    cv_file/cv_file_disk.c \
    cv_file/cv_file_poll.c \
    cv_file/cv_file_print.c \
    cv_file/cv_file_test.c \
    cv_runtime.c \
    cv_linux.c \
    cv_windows.c \

cv_test_srcs_abs = $(addprefix $(cv_src_path)/,$(cv_test_srcs))

cv_test_objs = $(addsuffix .o,$(cv_test_srcs))

cv_test_objs_abs = $(addprefix $(cv_obj_path)/,$(cv_test_objs))

cv_test_deps = $(addsuffix .d,$(cv_test_srcs))

cv_test_deps_abs = $(addprefix $(cv_obj_path)/,$(cv_test_deps))

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

cv_gnu_warnings = \
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
    -Wframe-larger-than=1024 \
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

cv_clang_warnings = \
    -ansi \
    -pedantic \
    -Weverything

cv_cflags = \
    -g \
    -O0 \
    -no-pie \
    -fno-pie \
    -fno-stack-protector \
    -fno-unwind-tables \
    -fno-asynchronous-unwind-tables \
    $(cv_gnu_warnings)

cv_verbose ?= @

.PHONY : test all clang mingw bare
test : $(cv_obj_path)/test.exe

all : $(cv_obj_path)/test.exe
all : $(cv_obj_path)/test.m64.exe
all : $(cv_obj_path)/test.cxx.exe
all : clang
clang : $(cv_obj_path)/test.clang.exe
clang : $(cv_obj_path)/test.clangxx.exe
all : mingw
mingw : $(cv_obj_path)/test.mingw.exe
mingw : $(cv_obj_path)/test.mingwxx.exe
all : bare
bare : $(cv_obj_path)/test.bare.exe

$(cv_obj_path)/test.exe : $(cv_src_path)/makefile $(cv_test_objs_abs) $(cv_src_path)/cv_export.mak
	@echo ld $(notdir $@)
	$(cv_verbose)echo -m32 -o $(cv_obj_path)/test.exe $(cv_cflags) $(cv_profile_cflags) -rdynamic $(cv_test_objs_abs) -Wl,--version-script=$(cv_src_path)/cv_export.mak -lpthread > $@.cmd
	$(cv_verbose)gcc @$@.cmd

$(cv_test_objs_abs) : $(cv_src_path)/makefile

$(cv_obj_path)/%.c.o : $(cv_src_path)/%.c
	@echo cc $(notdir $<)
	$(cv_verbose)mkdir -p $(dir $@)
	$(cv_verbose)echo -c -m32 -x c -o $@ $(cv_cflags) $(cv_profile_cflags) $(cv_defines) $(cv_includes) $< -MMD > $@.cmd
	$(cv_verbose)gcc @$@.cmd

$(cv_obj_path)/test.m64.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	@echo ld $(notdir $@)
	$(cv_verbose)gcc -m64 -x c -o $(cv_obj_path)/test.m64.exe $(cv_cflags) $(cv_defines) $(cv_includes) $(cv_test_srcs_abs) -lpthread

$(cv_obj_path)/test.cxx.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	@echo ld $(notdir $@)
	$(cv_verbose)g++ -x c++ -o $(cv_obj_path)/test.cxx.exe -fno-rtti -fno-exceptions -Wold-style-cast $(cv_cflags) $(cv_defines) $(cv_includes) $(cv_test_srcs_abs) -lpthread

cv_mingw_cc = i686-w64-mingw32-gcc -x c

cv_mingw_cxx = i686-w64-mingw32-g++ -x c++

cv_mingw_cflags = $(cv_cflags) -D cv_debug_ -D cv_windows_ -D cv_have_libc_ -D cv_have_pthread_ $(cv_includes)

cv_mingw_cxxflags = -fno-rtti -fno-exceptions -Wold-style-cast $(cv_mingw_cflags)

cv_mingw_libs = -lpthread

$(cv_obj_path)/test.mingw.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	@echo ld $(notdir $@)
	$(cv_verbose)echo -o $@ $(cv_mingw_cflags) $(cv_test_srcs_abs) $(cv_mingw_libs) > $@.cmd
	$(cv_verbose)$(cv_mingw_cc) @$@.cmd

$(cv_obj_path)/test.mingwxx.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	@echo ld $(notdir $@)
	$(cv_verbose)echo -o $@ $(cv_mingw_cxxflags) $(cv_test_srcs_abs) $(cv_mingw_libs) > $@.cmd
	$(cv_verbose)$(cv_mingw_cxx) @$@.cmd

cv_clang_cc = clang -x c

cv_clang_cxx = clang++ -x c++

cv_clang_ld = clang

cv_clang_cflags = -g -O0 $(cv_clang_warnings) $(cv_defines) $(cv_includes)

cv_clang_cxxflags = $(cv_clang_cflags) -fno-rtti -fno-exceptions

cv_clang_libs = -lpthread

$(cv_obj_path)/test.clang.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	@echo ld $(notdir $@)
	$(cv_verbose)mkdir -p $(dir $@)
	$(cv_verbose)echo -o $@ $(cv_clang_cflags) $(cv_test_srcs_abs) $(cv_clang_libs) > $@.cmd
	$(cv_verbose)$(cv_clang_cc) @$@.cmd

$(cv_obj_path)/test.clangxx.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	@echo ld $(notdir $@)
	$(cv_verbose)mkdir -p $(dir $@)
	$(cv_verbose)echo -o $@ $(cv_clang_cxxflags) $(cv_test_srcs_abs) $(cv_clang_libs) > $@.cmd
	$(cv_verbose)$(cv_clang_cxx) @$@.cmd

$(cv_obj_path)/test.bare.exe : $(cv_src_path)/makefile $(cv_test_srcs_abs)
	@echo ld $(notdir $@)
	$(cv_verbose)mkdir -p $(dir $@)
	$(cv_verbose)echo -m64 -x c -o $@ -I . -D cv_debug_ -ansi -pedantic -nostdinc -Wall -Wextra -fno-stack-protector $(cv_test_srcs_abs) -nodefaultlibs -nostartfiles > $@.cmd
	$(cv_verbose)gcc @$@.cmd

-include $(cv_test_deps_abs)

.PHONY : clean
clean :
	rm -rf $(cv_obj_path)/*
