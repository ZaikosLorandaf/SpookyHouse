#pragma once

#ifdef __cplusplus
extern "C" {
bool add_to_print_buffer(const char *);

void print_buffer();

void init_print_buffer();

void destroy_print_buffer();

void clear_print_buffer();

bool format_to_print_buffer(const char *format, ...)
#if defined(__clang__) || defined(__GNUC__)
    __attribute__((format(printf, 1, 2)))
#endif
    ;
}
#else
#include <stdbool.h>

bool add_to_print_buffer(const char *);

void print_buffer();

void init_print_buffer();

void destroy_print_buffer();

void clear_print_buffer();

bool format_to_print_buffer(const char *restrict format, ...)
#if defined(__clang__) || defined(__GNUC__)
    __attribute__((format(printf, 1, 2)))
#endif
    ;
#endif
