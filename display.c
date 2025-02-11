#include "headers/display.h"
#include "headers/coord.h"
#include <stdio.h>

#define CLEAR_SEQUENCE "\033[2J\033[1;1H"
#define CURSOR_MOVE_FORMAT "\033[%d;%dH"
#define PLAYER_STR "o"

void move_cursor(const Coordinates *restrict coord) {
  printf(CURSOR_MOVE_FORMAT, coord->y + 1, coord->x + 1);
}

void print_maze(const char *restrict const *restrict maze,
                const Coordinates *restrict maze_dimen) {
  clear_screen();
  for (size_t i = 0; i <= maze_dimen->y; i++) {
    printf("%s" CURSOR_MOVE_FORMAT, maze[i], (int)(i + 2), 1);
  }
}

void remove_player_char(const Coordinates *restrict player_coord) {
  printf(CURSOR_MOVE_FORMAT " " CURSOR_MOVE_FORMAT, player_coord->y + 1,
         player_coord->x + 1, 1, 1);
}

void print_player_char(const Coordinates *restrict player_coord) {
  printf(CURSOR_MOVE_FORMAT PLAYER_STR CURSOR_MOVE_FORMAT, player_coord->y + 1,
         player_coord->x + 1, 1, 1);
}

void clear_screen() { printf(CLEAR_SEQUENCE); }
