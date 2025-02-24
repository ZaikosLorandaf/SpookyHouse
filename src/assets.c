#include "assets.h"
#include "coord.h"
#include "print_buffer.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TITLE_SCREEN_ASSET_PATH "assets/title_screen.txt"
#define BUFF_SIZE 120
#define CLEAR_SEQUENCE "\033[2J\033[1;1H"
#define NEWLINE_SEQUENCE "\033[E"

#define MAIN_MAZE_PATH "assets/mazes/main.txt"

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
    if (!format_to_print_buffer("%s" NEWLINE_SEQUENCE, buff)) {
      fclose(f);
      return false;
    }
  }
  print_buffer();
  fclose(f);
  return true;
}

bool read_maze(const char *restrict maze_path, struct Maze *restrict out_maze) {
  FILE *f = fopen(maze_path, "r");
  assert(f != NULL);
  // if (f == NULL)
  //   return false;
  char buff[BUFF_SIZE];
  if (NULL == fgets(buff, BUFF_SIZE, f)) {
    fclose(f);
    assert(false);
    return false;
  }
  if (2 != sscanf(buff, "%d %d", &(out_maze->dimen.x), &(out_maze->dimen.y))) {
    fclose(f);
    assert(false);
    return false;
  }
  out_maze->content =
      malloc(out_maze->dimen.x * out_maze->dimen.y * sizeof(char));
  for (size_t i = 0; i < out_maze->dimen.y; i++) {
    if (NULL == fgets(buff, BUFF_SIZE, f)) {
      fclose(f);
      free(out_maze->content);
      out_maze->content = NULL;
      assert(false);
      return false;
    }
    int len = 0;
    while (buff[len] != '\0') {
      if (buff[len] == '\n') {
        buff[len] = '\0';
        break;
      } else if (buff[len] == 'E') {
        out_maze->entrance = (Coordinates){len, i};
      } else if (buff[len] == 'W') {
        out_maze->exit = (Coordinates){len, i};
      }
      len++;
    }
    if (len != out_maze->dimen.x) {
      fclose(f);
      free(out_maze->content);
      out_maze->content = NULL;
      return false;
    }
    memcpy(out_maze->content + (out_maze->dimen.x * i), buff, len);
  }
  fclose(f);
  return true;
}

void free_maze(struct Maze *maze) {
  maze->dimen = (Coordinates){0, 0};
  free(maze->content);
  maze->content = NULL;
}
