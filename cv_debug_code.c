/* See LICENSE for license details */

/*
 *
 */

#include <cv_debug_code.h>
#include <cv_algo/cv_array.h>
#include <cv_algo/cv_array_tool.h>

static unsigned char const a_debug_code_null_ptr[] = {
    'n', 'u', 'l', 'l', ' ', 'p', 't', 'r' };

static unsigned char const a_debug_code_error[] = {
    'e', 'r', 'r', 'o', 'r' };

static unsigned char const a_debug_code_already_loaded[] = {
    'a', 'l', 'r', 'e', 'a', 'd', 'y', ' ',
    'l', 'o', 'a', 'd', 'e', 'd' };

static unsigned char const a_debug_code_already_unloaded[] = {
    'a', 'l', 'r', 'e', 'a', 'd', 'y', ' ',
    'u', 'n', 'l', 'o', 'a', 'd', 'e', 'd' };

static unsigned char const a_debug_code_not_loaded[] = {
    'n', 'o', 't', ' ',
    'l', 'o', 'a', 'd', 'e', 'd' };

static unsigned char const a_debug_code_invalid_length[] = {
    'i', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'l', 'e', 'n', 'g', 't', 'h' };

static unsigned char const a_debug_code_alternative[] = {
    'a', 'l', 't', 'e', 'r', 'n', 'a', 't', 'i', 'v', 'e' };

static unsigned char const a_debug_code_out_of_memory[] = {
    'o', 'u', 't', ' ', 'o', 'f', ' ', 'm', 'e', 'm', 'o', 'r', 'y' };

static unsigned char const a_debug_code_not_empty[] = {
    'n', 'o', 't', ' ',
    'e', 'm', 'p', 't', 'y' };

static unsigned char const a_debug_code_not_implemented[] = {
    'n', 'o', 't', ' ',
    'i', 'm', 'p', 'l', 'e', 'm', 'e', 'n', 't', 'e', 'd' };

static unsigned char const a_debug_code_invalid_parameter[] = {
    'i', 'n', 'v', 'a', 'l', 'i', 'd', ' ',
    'p', 'a', 'r', 'a', 'm', 'e', 't', 'e', 'r'
};

static unsigned char const a_debug_code_dont_panic[] = {
    'd', 'o', 'n', 't', ' ', 'p', 'a', 'n', 'i', 'c'
};

static unsigned char const a_debug_code_leak[] = {
    'l', 'e', 'a', 'k'
};

static cv_array const g_debug_code_null_ptr =
cv_array_text_initializer_(a_debug_code_null_ptr);

static cv_array const g_debug_code_error =
cv_array_text_initializer_(a_debug_code_error);

static cv_array const g_debug_code_already_loaded =
cv_array_text_initializer_(a_debug_code_already_loaded);

static cv_array const g_debug_code_already_unloaded =
cv_array_text_initializer_(a_debug_code_already_unloaded);

static cv_array const g_debug_code_not_loaded =
cv_array_text_initializer_(a_debug_code_not_loaded);

static cv_array const g_debug_code_invalid_length =
cv_array_text_initializer_(a_debug_code_invalid_length);

static cv_array const g_debug_code_alternative =
cv_array_text_initializer_(a_debug_code_alternative);

static cv_array const g_debug_code_out_of_memory =
cv_array_text_initializer_(a_debug_code_out_of_memory);

static cv_array const g_debug_code_not_empty =
cv_array_text_initializer_(a_debug_code_not_empty);

static cv_array const g_debug_code_not_implemented =
cv_array_text_initializer_(a_debug_code_not_implemented);

static cv_array const g_debug_code_invalid_parameter =
cv_array_text_initializer_(a_debug_code_invalid_parameter);

static cv_array const g_debug_code_dont_panic =
cv_array_text_initializer_(a_debug_code_dont_panic);

static cv_array const g_debug_code_leak =
cv_array_text_initializer_(a_debug_code_leak);

cv_debug_code cv_debug_code_null_ptr = &g_debug_code_null_ptr;

cv_debug_code cv_debug_code_error = &g_debug_code_error;

cv_debug_code cv_debug_code_already_loaded = &g_debug_code_already_loaded;

cv_debug_code cv_debug_code_already_unloaded = &g_debug_code_already_unloaded;

cv_debug_code cv_debug_code_not_loaded = &g_debug_code_not_loaded;

cv_debug_code cv_debug_code_invalid_length = &g_debug_code_invalid_length;

cv_debug_code cv_debug_code_alternative = &g_debug_code_alternative;

cv_debug_code cv_debug_code_out_of_memory = &g_debug_code_out_of_memory;

cv_debug_code cv_debug_code_not_empty = &g_debug_code_not_empty;

cv_debug_code cv_debug_code_not_implemented = &g_debug_code_not_implemented;

cv_debug_code cv_debug_code_invalid_parameter = &g_debug_code_invalid_parameter;

cv_debug_code cv_debug_code_dont_panic = &g_debug_code_dont_panic;

cv_debug_code cv_debug_code_leak = &g_debug_code_leak;

/* end-of-file: cv_debug_code.c */
