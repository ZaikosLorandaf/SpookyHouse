// if its stupid but works then it isn't stupid
//~someone wiser than me

#include "headers/coord.h"
#include "headers/display.h"
#include "headers/init.h"
#include <stdbool.h>
#include <stdio.h>

#ifdef _WIN32
#include <conio.h>
#else
static inline int getch() { return getc(stdin); }
#endif

static const char *const clear_sequence = "\033[2J\033[1;1H";

static const Coordinates origin = {0, 0};

typedef enum {
  up,
  down,
  left,
  right,
} Move;

static const char *const title_screen_logo =
    "\033[2J\033[1H\033[25l"
    " _____ _____ _____ _____ _____ _____    _____ _____ _____ _____ "
    "_____\033[2H"
    "|   __|   __|     |  _  |  _  |   __|  |   __|   __| __  |   __|   "
    "__|\033[3H"
    "|   __|__   |   --|     |   __|   __|  |__   |   __|    -|  |  |   "
    "__|\033[4H"
    "|_____|_____|_____|__|__|__|  |_____|  "
    "|_____|_____|__|__|_____|_____|\033[5H";

void print_title_screen() {
  printf("%s%s", title_screen_logo, "\npress any key to play.");
};

static const Coordinates maze_dimen = {60, 14};
static const Coordinates win_condition = {60, 13};
static const char *const maze[] = {
    "    #########################################################",
    "         #     #                 #              #        #  #",
    "####  #  #  #  #  ####  #  #  #############  #######  ####  #",
    "#     #     #  #  #  #  #  #  #     #           #        #  #",
    "#  #  #  ##########  #  #######  #######  #  ####  ####  #  #",
    "#  #  #     #        #        #  #  #     #  #     #  #     #",
    "####  #  #  #  #######  #######  #  #######  ####  #  #  #  #",
    "#     #  #  #     #                 #           #  #     #  #",
    "#  #######  ####  #  ####  #############  #  #  ####  #  #  #",
    "#        #     #        #     #     #     #  #        #  #  #",
    "#  ##########  ####  #######  #  #######  #  ################",
    "#     #        #        #                 #  #     #  #     #",
    "#  #  #######  ####  ##########  ##########  ####  #  #  ####",
    "#  #  #                 #        #                           ",
    "#############################################################"};

static bool is_move_valid(const Coordinates *player_coordinate) {
  bool not_out_of_bounds =
      player_coordinate->x >= 0 && player_coordinate->x <= maze_dimen.x &&
      player_coordinate->y >= 0 && player_coordinate->y <= maze_dimen.y;
  if (!not_out_of_bounds)
    return false;
  return maze[player_coordinate->y][player_coordinate->x] != '#';
}

static bool move_player(char key_presed, Coordinates *player_coordinate) {
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
  if (is_move_valid(&new_coord)) {
    *player_coordinate = new_coord;
    return true;
  }
  return false;
}

static bool should_quit(char key_presed, const Coordinates *player_coordinate) {
  switch (key_presed) {
  case 'Q':
  case 'q':
    return true;
  default:
    return false;
  }
}

int main() {
  init_direct_mode();
  print_title_screen();
  getch();
  clear_screen();
  // code de couleur. je voulais ajouter une cle pis une porte mais
  // trop complique a mon gout. mais je laisse ca ici au cas ou

  //	cout << "\033[32mThis is green text";
  //	cout << "\033[34mThis is blue text";
  //	cout << "\033[37mThis is white text";

  Coordinates player_coordinate = origin;
  print_maze(maze, &maze_dimen);
  print_player_char(&player_coordinate);
  while (true) {
    char user_input = getch();
    if (should_quit(user_input, &player_coordinate))
      break;
    Coordinates old_player = player_coordinate;
    if (move_player(user_input, &player_coordinate)) {
      remove_player_char(&old_player);
      print_player_char(&player_coordinate);
    }
    if (player_coordinate.x == win_condition.x &&
        player_coordinate.y == win_condition.y) {
      printf("%s%s%s", clear_sequence, "you won!", "\033[2H");
      break;
    }
  }
  reset_term();
  return 0;
};
