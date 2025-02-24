#pragma once
#include <stddef.h>

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

bool cpy_bytes_to_buff(const void *src, size_t count);
}
#else
#include <stdbool.h>

bool add_to_print_buffer(const char *);

void print_buffer(void);

void init_print_buffer(void);

void destroy_print_buffer(void);

void clear_print_buffer(void);

bool format_to_print_buffer(const char *restrict format, ...)
#if defined(__clang__) || defined(__GNUC__)
    __attribute__((format(printf, 1, 2)))
#endif
    ;

bool cpy_bytes_to_buff(const void *restrict src, size_t count);
#endif
