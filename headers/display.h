#include "assets.h"
#include "coord.h"

#ifdef __cplusplus
extern "C" {
void move_cursor(const Coordinates *coord);
void new_print_maze(const struct Maze *maze);
void remove_player_char(const Coordinates *player_coord);
void print_player_char(const Coordinates *player_coord);
void clear_screen();
}
#else
void move_cursor(const Coordinates *restrict coord);

void print_maze(const struct Maze *restrict maze);

void remove_player_char(const Coordinates *restrict player_coord);

void print_player_char(const Coordinates *restrict player_coord);

void clear_screen();
#endif
