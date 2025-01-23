// if its stupid but works then it isn't stupid
//~someone wiser than me

#include <cstdio>
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
static void init_direct_mode() {
  struct termios tio;
  tcgetattr(STDIN_FILENO, &tio);
  cfmakeraw(&tio);
  tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}

static inline int getch() { return getc(stdin); }
#endif

static const char *const clear_sequence = "\033[2J\033[1;1H";

using namespace std;

typedef struct {
  int x;
  int y;
} Coordinates;

static const Coordinates origin = {0, 0};

typedef enum {
  Up,
  Down,
  Left,
  Right,
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

static void move_cursor(const Coordinates *coord) {
  cout << "\033[" << coord->y + 1 << ';' << coord->x + 1 << 'H';
}
void print_title_screen() {
  cout << title_screen_logo << "\nPress any key to play." << endl;
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

static void print_maze() {
  for (size_t i = 0; i <= maze_dimen.y; i++) {
    cout << maze[i];
    Coordinates c = {0, ((int)i) + 1};
    move_cursor(&c);
  }
}

static void remove_player_char(const Coordinates *player_coord) {
  move_cursor(player_coord);
  cout << ' ';
  move_cursor(&origin);
}

static void print_player_char(const Coordinates *player_coord) {
  move_cursor(player_coord);
  cout << 'o';
  move_cursor(&origin);
}

static void clear_screen() { cout << "\033[2J\033[1H"; }

int main() {

#ifndef _WIN32
  init_direct_mode();
#endif
  print_title_screen();
  getch();
  clear_screen();
  // code de couleur. je voulais ajouter une cle pis une porte mais
  // trop complique a mon gout. mais je laisse ca ici au cas ou

  //	cout << "\033[32mThis is green text";
  //	cout << "\033[34mThis is blue text";
  //	cout << "\033[37mThis is white text";

  Coordinates player_coordinate = origin;
  print_maze();
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
      cout << clear_sequence << "you won!" << "\033[2H";
      break;
    }
  }

  return 0;
};
