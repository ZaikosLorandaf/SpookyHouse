#pragma once
#include "coord.h"
#include <stdbool.h>

struct Maze {
  Coordinates dimen;
  Coordinates entrance;
  Coordinates exit;
  char *content;
};

#ifdef __cplusplus
extern "C" {
bool print_title_screen();

bool read_maze(const char *maze_path, struct Maze *out_maze);
}
#else
bool print_title_screen();

bool read_maze(const char *restrict maze_path, struct Maze *restrict out_maze);
#endif
