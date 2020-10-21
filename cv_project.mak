# See LICENSE for license details

#
# GNU makefile for build of library
#

cv_src_path := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

cv_dst_path ?= $(cv_src_path)

cv_obj_path ?= $(cv_dst_path)/.obj

cv_extra_makefiles := \
    cv_algo/cv_sources.mak \
    cv_clock/cv_sources.mak \
    cv_file/cv_sources.mak \
    cv_heap/cv_sources.mak \
    cv_json/cv_sources.mak \
    cv_number/cv_sources.mak \
    cv_options/cv_sources.mak \
    cv_random/cv_sources.mak \
    cv_screen/cv_sources.mak \
    cv_thread/cv_sources.mak \
    cv_trace/cv_sources.mak \
    cv_unicode/cv_sources.mak \

include $(addprefix $(cv_src_path)/,$(cv_extra_makefiles))

cv_lib_srcs := \
    cv_main.c \
    cv_manager.c \
    cv_memory.c \
    cv_runtime.c \
    cv_linux.c \
    cv_windows.c \
    cv_misc/cv_convert.c \
    cv_object/cv_object.c \
    cv_debug/cv_debug.c \
    cv_debug/cv_debug_code.c \
    cv_debug/cv_debug_class.c \
    cv_misc/cv_sizeof.c \
    $(cv_algo_lib_srcs) \
    $(cv_clock_lib_srcs) \
    $(cv_file_lib_srcs) \
    $(cv_heap_lib_srcs) \
    $(cv_json_lib_srcs) \
    $(cv_number_lib_srcs) \
    $(cv_options_lib_srcs) \
    $(cv_random_lib_srcs) \
    $(cv_screen_lib_srcs) \
    $(cv_thread_lib_srcs) \
    $(cv_trace_lib_srcs) \
    $(cv_unicode_lib_srcs) \

cv_test_srcs := \
    cv_test_os.c \
    cv_test.c \
    cv_test_print.c \
    cv_misc/cv_convert_test.c \
    $(cv_algo_test_srcs) \
    $(cv_clock_test_srcs) \
    $(cv_file_test_srcs) \
    $(cv_heap_test_srcs) \
    $(cv_json_test_srcs) \
    $(cv_number_test_srcs) \
    $(cv_options_test_srcs) \
    $(cv_random_test_srcs) \
    $(cv_screen_test_srcs) \
    $(cv_thread_test_srcs) \
    $(cv_trace_test_srcs) \
    $(cv_unicode_test_srcs) \
    $(cv_lib_srcs) \

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
    -I $(cv_src_path)

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
    -Wwrite-strings \
    -Werror

cv_clang_warnings = \
    -ansi \
    -pedantic \
    -Weverything \
    -Werror

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

cv_color_fn = [ -t 1 ] && echo -n -e $(1) || true
cv_color_green = $(call cv_color_fn,"\033[1;32m")
cv_color_yellow = $(call cv_color_fn,"\033[1;33m")
cv_color_cyan = $(call cv_color_fn,"\033[1;36m")
cv_color_normal = $(call cv_color_fn,"\033[0m")

cv_echo_message = $(cv_color_$(2));echo -n $(1);$(cv_color_normal);echo ''
cv_echo_green_message = $(call cv_echo_message,$(1),green)
cv_echo_yellow_message = $(call cv_echo_message,$(1),yellow)
cv_echo_cyan_message = $(call cv_echo_message,$(1),cyan)

.PHONY : test all clang mingw bare
test : $(cv_obj_path)/test.exe

all : $(cv_obj_path)/test.exe
all : $(cv_obj_path)/test.m32.exe
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

$(cv_obj_path)/test.exe : $(cv_test_objs_abs) $(cv_src_path)/cv_export.mak
	@$(call cv_echo_cyan_message,ld $(@:$(cv_dst_path)/%=%))
	$(cv_verbose)echo -o $(cv_obj_path)/test.exe $(cv_cflags) $(cv_profile_cflags) -rdynamic $(cv_test_objs_abs) -Wl,--version-script=$(cv_src_path)/cv_export.mak -lpthread > $@.cmd
	$(cv_verbose)gcc @$@.cmd

$(cv_test_objs_abs) : $(MAKEFILE_LIST)

$(cv_obj_path)/%.c.o : $(cv_src_path)/%.c
	@$(call cv_echo_green_message,cc $(<:$(cv_src_path)/%=%))
	$(cv_verbose)mkdir -p $(dir $@)
	$(cv_verbose)echo -c -x c -o $@ $(cv_cflags) $(cv_profile_cflags) $(cv_defines) $(cv_includes) $< -MMD > $@.cmd
	$(cv_verbose)gcc @$@.cmd

$(cv_obj_path)/test.m32.exe : $(MAKEFILE_LIST) $(cv_test_srcs_abs)
	@$(call cv_echo_cyan_message,ld $(notdir $@))
	$(cv_verbose)gcc -m32 -x c -o $(cv_obj_path)/test.m32.exe $(cv_cflags) $(cv_defines) $(cv_includes) $(cv_test_srcs_abs) -lpthread

$(cv_obj_path)/test.m64.exe : $(MAKEFILE_LIST) $(cv_test_srcs_abs)
	@$(call cv_echo_cyan_message,ld $(notdir $@))
	$(cv_verbose)gcc -m64 -x c -o $(cv_obj_path)/test.m64.exe $(cv_cflags) $(cv_defines) $(cv_includes) $(cv_test_srcs_abs) -lpthread

$(cv_obj_path)/test.cxx.exe : $(MAKEFILE_LIST) $(cv_test_srcs_abs)
	@$(call cv_echo_cyan_message,ld $(notdir $@))
	$(cv_verbose)g++ -x c++ -o $(cv_obj_path)/test.cxx.exe -fno-rtti -fno-exceptions -Wold-style-cast $(cv_cflags) $(cv_defines) $(cv_includes) $(cv_test_srcs_abs) -lpthread

cv_mingw_cc = i686-w64-mingw32-gcc -x c

cv_mingw_cxx = i686-w64-mingw32-g++ -x c++

cv_mingw_cflags = $(cv_cflags) -D cv_debug_ -D cv_windows_ -D cv_have_libc_ -D cv_have_pthread_ $(cv_includes)

cv_mingw_cxxflags = -fno-rtti -fno-exceptions -Wold-style-cast $(cv_mingw_cflags)

cv_mingw_libs = -lpthread

$(cv_obj_path)/test.mingw.exe : $(MAKEFILE_LIST) $(cv_test_srcs_abs)
	@$(call cv_echo_cyan_message,ld $(notdir $@))
	$(cv_verbose)echo -o $@ $(cv_mingw_cflags) $(cv_test_srcs_abs) $(cv_mingw_libs) > $@.cmd
	$(cv_verbose)$(cv_mingw_cc) @$@.cmd

$(cv_obj_path)/test.mingwxx.exe : $(MAKEFILE_LIST) $(cv_test_srcs_abs)
	@$(call cv_echo_cyan_message,ld $(notdir $@))
	$(cv_verbose)echo -o $@ $(cv_mingw_cxxflags) $(cv_test_srcs_abs) $(cv_mingw_libs) > $@.cmd
	$(cv_verbose)$(cv_mingw_cxx) @$@.cmd

cv_clang_cc = clang -x c

cv_clang_cxx = clang++ -x c++

cv_clang_ld = clang

cv_clang_cflags = -g -O0 $(cv_clang_warnings) $(cv_defines) $(cv_includes)

cv_clang_cxxflags = $(cv_clang_cflags) -fno-rtti -fno-exceptions

cv_clang_libs = -lpthread

$(cv_obj_path)/test.clang.exe : $(MAKEFILE_LIST) $(cv_test_srcs_abs)
	@$(call cv_echo_cyan_message,ld $(notdir $@))
	$(cv_verbose)mkdir -p $(dir $@)
	$(cv_verbose)echo -o $@ $(cv_clang_cflags) $(cv_test_srcs_abs) $(cv_clang_libs) > $@.cmd
	$(cv_verbose)$(cv_clang_cc) @$@.cmd

$(cv_obj_path)/test.clangxx.exe : $(MAKEFILE_LIST) $(cv_test_srcs_abs)
	@$(call cv_echo_cyan_message,ld $(notdir $@))
	$(cv_verbose)mkdir -p $(dir $@)
	$(cv_verbose)echo -o $@ $(cv_clang_cxxflags) $(cv_test_srcs_abs) $(cv_clang_libs) > $@.cmd
	$(cv_verbose)$(cv_clang_cxx) @$@.cmd

$(cv_obj_path)/test.bare.exe : $(MAKEFILE_LIST) $(cv_test_srcs_abs)
	@$(call cv_echo_cyan_message,ld $(notdir $@))
	$(cv_verbose)mkdir -p $(dir $@)
	$(cv_verbose)echo -x c -o $@ -I$(cv_src_path) -D cv_debug_ -ansi -pedantic -nostdinc -Wall -Wextra -fno-stack-protector $(cv_test_srcs_abs) -nodefaultlibs -nostartfiles > $@.cmd
	$(cv_verbose)gcc @$@.cmd

.PHONY : clean
clean :
	rm -rf $(cv_obj_path)/*

.PHONY : doc
doc : cv-template cv-heap cv-trace

.PHONY : cv-template
cv-template : $(cv_obj_path)/cv_template.pdf

$(cv_obj_path)/cv_template.pdf : $(MAKEFILE_LIST) \
    $(cv_src_path)/cv_doc/cv_common.tex

.PHONY : cv-heap
cv-heap : $(cv_obj_path)/cv_heap.pdf

$(cv_obj_path)/cv_heap.pdf : $(MAKEFILE_LIST) \
    $(cv_src_path)/cv_doc/cv_common.tex

.PHONY : cv-trace
cv-trace : $(cv_obj_path)/cv_trace.pdf

$(cv_obj_path)/cv_trace.pdf : $(MAKEFILE_LIST) \
    $(cv_src_path)/cv_doc/cv_trace.tex

$(cv_obj_path)/%.pdf : $(cv_src_path)/cv_doc/%.tex
	@echo latex $(notdir $@)
	$(cv_verbose)mkdir -p $(dir $@)
	$(cv_verbose)pdflatex -output-directory=$(cv_obj_path) -halt-on-error $< >/dev/null
	$(cv_verbose)pdflatex -output-directory=$(cv_obj_path) -halt-on-error $< >/dev/null

-include $(cv_test_deps_abs)

