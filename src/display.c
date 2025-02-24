#include "display.h"
#include "assets.h"
#include "coord.h"
#include "print_buffer.h"
#include <stddef.h>

#define CLEAR_SEQUENCE "\033[2J\033[1;1H"
#define CURSOR_MOVE_FORMAT "\033[%d;%dH"
#define NEWLINE_SEQUENCE "\033[E"
#define PLAYER_STR "o"
#define CURSOR_TO_ORIGIN "\033[1;1H"

void move_cursor(const Coordinates *restrict coord) {
  format_to_print_buffer(CURSOR_MOVE_FORMAT, coord->y + 1, coord->x + 1);
}

void print_maze(const struct Maze *restrict maze) {
  const size_t line_count = maze->dimen.y;
  const size_t line_length = maze->dimen.x;
  for (size_t i = 0; i < (line_count - 1); i++) {
    cpy_bytes_to_buff(maze->content + (i * line_length), line_length);
    cpy_bytes_to_buff(NEWLINE_SEQUENCE, sizeof(NEWLINE_SEQUENCE) - 1);
  }
  cpy_bytes_to_buff(maze->content + ((line_count - 1) * line_length),
                    line_length);
  cpy_bytes_to_buff(CURSOR_TO_ORIGIN, sizeof(CURSOR_TO_ORIGIN) - 1);
}

void remove_player_char(const Coordinates *restrict player_coord) {
  format_to_print_buffer(CURSOR_MOVE_FORMAT " " CURSOR_MOVE_FORMAT,
                         player_coord->y + 1, player_coord->x + 1, 1, 1);
}

void print_player_char(const Coordinates *restrict player_coord) {
  format_to_print_buffer(CURSOR_MOVE_FORMAT PLAYER_STR CURSOR_MOVE_FORMAT,
                         player_coord->y + 1, player_coord->x + 1, 1, 1);
}

void clear_screen() { add_to_print_buffer(CLEAR_SEQUENCE); }
