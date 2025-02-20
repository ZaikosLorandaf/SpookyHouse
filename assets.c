#include "headers/assets.h"
#include "headers/print_buffer.h"
#include <stdio.h>
#include <string.h>

#define TITLE_SCREEN_ASSET_PATH "assets/title_screen.txt"
#define BUFF_SIZE 120
#define CLEAR_SEQUENCE "\033[2J\033[1;1H"
#define NEWLINE_SEQUENCE "\033[E"

bool print_title_screen() {
  FILE *f = fopen(TITLE_SCREEN_ASSET_PATH, "r");
  if (f == NULL)
    return false;
  add_to_print_buffer(CLEAR_SEQUENCE);
  char buff[BUFF_SIZE];
  while (NULL != fgets(buff, BUFF_SIZE, f)) {
    size_t len = strlen(buff);
    for (size_t i = 0; i < len; i++) {
      if (buff[i] == '\n') {
        buff[i] = '\0';
        break;
      }
    }
    if (!format_to_print_buffer("%s" NEWLINE_SEQUENCE, buff))
      return false;
  }
  print_buffer();
  return true;
}
