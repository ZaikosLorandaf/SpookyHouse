// if its stupid but works then it isn't stupid
//~someone wiser than me

#include "assets.h"
#include "coord.h"
#include "display.h"
#include "init.h"
#include "print_buffer.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#ifdef _WIN32
#include <conio.h>
#else
static inline int getch(void) { return getc(stdin); }
#endif

static const char *const clear_sequence = "\033[2J\033[1;1H";

// static const Coordinates origin = {0, 0};

typedef enum {
  up,
  down,
  left,
  right,
} Move;

static bool is_move_valid(const Coordinates *player_coordinate,
                          const struct Maze *restrict maze) {
  const int x = player_coordinate->x;
  const int y = player_coordinate->y;
  bool not_out_of_bounds =
      x >= 0 && x <= maze->dimen.x && y >= 0 && y <= maze->dimen.y;
  if (!not_out_of_bounds)
    return false;
  return maze->content[x + y * maze->dimen.x] != '#';
}

static bool move_player(char key_presed, Coordinates *player_coordinate,
                        const struct Maze *restrict maze) {
  Coordinates new_coord = *player_coordinate;
  switch (key_presed) {
  case 'W':
  case 'w':
    new_coord.y--;
    break;
  case 'S':
  case 's':
    new_coord.y++;
    break;
  case 'A':
  case 'a':
    new_coord.x--;
    break;
  case 'D':
  case 'd':
    new_coord.x++;
    break;
  default:
    return false;
  }
  if (is_move_valid(&new_coord, maze)) {
    *player_coordinate = new_coord;
    return true;
  }
  return false;
}

static bool should_quit(char key_presed) {
  switch (key_presed) {
  case 'Q':
  case 'q':
    return true;
  default:
    return false;
  }
}

int main(void) {
  init_direct_mode();
  init_print_buffer();
  assert(print_title_screen());
  (void)getch();
  clear_screen();
  // code de couleur. je voulais ajouter une cle pis une porte mais
  // trop complique a mon gout. mais je laisse ca ici au cas ou

  //	cout << "\033[32mThis is green text";
  //	cout << "\033[34mThis is blue text";
  //	cout << "\033[37mThis is white text";

  // print_maze(maze, &maze_dimen);
  struct Maze maze;
  assert(read_maze("assets/mazes/main.txt", &maze));
  print_maze(&maze);
  Coordinates player_coordinate = maze.entrance;
  print_player_char(&player_coordinate);
  while (true) {
    print_buffer();
    char user_input = (char)(getch());
    if (should_quit(user_input)) {
      clear_screen();
      print_buffer();
      break;
    }
    Coordinates old_player = player_coordinate;
    if (move_player(user_input, &player_coordinate, &maze)) {
      remove_player_char(&old_player);
      print_player_char(&player_coordinate);
    }
    if (player_coordinate.x == maze.exit.x &&
        player_coordinate.y == maze.exit.y) {
      format_to_print_buffer("%s%s%s", clear_sequence, "you won!", "\033[2H");
      print_buffer();
      break;
    }
  }
  reset_term();
  destroy_print_buffer();
  return 0;
}
