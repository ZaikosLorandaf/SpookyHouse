#include "headers/print_buffer.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 10000

struct PrintBuffer {
  char buff[BUFF_SIZE];
  size_t size;
};

static struct PrintBuffer *restrict buff_ptr = NULL;

void init_print_buffer() {
  buff_ptr = malloc(sizeof(struct PrintBuffer));
  buff_ptr->size = 0;
}

void destroy_print_buffer() {
  free(buff_ptr);
  buff_ptr = NULL;
}

void clear_print_buffer() { buff_ptr->size = 0; }

bool add_to_print_buffer(const char *restrict str) {
  size_t remaining_size = BUFF_SIZE - buff_ptr->size;
  size_t len_of_str = strlen(str);
  if (len_of_str > remaining_size) {
    return false;
  }
  memcpy(buff_ptr->buff + buff_ptr->size, str, len_of_str);
  buff_ptr->size += len_of_str;
  return true;
}

bool format_to_print_buffer(const char *restrict format, ...) {
  va_list ap;
  va_start(ap, format);
  const int max_cpy = (int)(BUFF_SIZE - buff_ptr->size);
  const int copied =
      vsnprintf(buff_ptr->buff + buff_ptr->size, max_cpy, format, ap);
  if (copied < 0 || copied > max_cpy) {
    return false;
  }
  buff_ptr->size += (size_t)(copied);
  return true;
}

void print_buffer() {
#ifdef _WIN32
  _fwrite_noblock(buff_ptr->buff, sizeof(char), buff_ptr->size, stdout);
#else
  fwrite_unlocked(buff_ptr->buff, sizeof(char), buff_ptr->size, stdout);
#endif
  clear_print_buffer();
}
