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

const int W = 'w';
const int S = 's';
const int D = 'd';
const int A = 'a';
const int E = 'e';
const int C = 'c';

char screen[120 * 30 + 1] = {0};

typedef struct {
  int x;
  int y;
} Coordinates;

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

void print_title_screen() {
  cout << title_screen_logo << "\nPress any key to play." << endl;
};

static const Coordinates maze_dimen = {60, 14};
static const Coordinates win_condition = {13, 59};
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

void resetScreen() {
  for (int i = 0; i < 120 * 30; i++) {
    screen[i] = ' ';
  }
};

static bool is_move_valid(const Coordinates *player_coordinate) {
  bool not_out_of_bounds =
      player_coordinate->x >= 0 && player_coordinate->x <= maze_dimen.x &&
      player_coordinate->y >= 0 && player_coordinate->y <= maze_dimen.y;
  if (!not_out_of_bounds)
    return false;
  return maze[player_coordinate->y][player_coordinate->x] != '#';
}

static void move_player(char key_presed, Coordinates *player_coordinate) {
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
    return;
  }
  if (is_move_valid(&new_coord))
    *player_coordinate = new_coord;
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

static void update_screen(const Coordinates *player_coordinate) {
  char buff[20];
  const int x = player_coordinate->x + 1;
  const int y = player_coordinate->y + 1;
  sprintf(buff, "\033[%d;%dHo\033[1H", y, x);
  cout << clear_sequence;
  for (size_t i = 0; i <= maze_dimen.y; i++)
    cout << maze[i] << "\033[" << i + 2 << 'H';
  cout << buff;
}

int main() {

#ifndef _WIN32
  init_direct_mode();
#endif
  print_title_screen();

  // code de couleur. je voulais ajouter une cle pis une porte mais
  // trop complique a mon gout. mais je laisse ca ici au cas ou

  //	cout << "\033[32mThis is green text";
  //	cout << "\033[34mThis is blue text";
  //	cout << "\033[37mThis is white text";

  Coordinates player_coordinate = {0, 0};
  while (true) {
    char user_input = getch();
    if (should_quit(user_input, &player_coordinate))
      break;

    move_player(user_input, &player_coordinate);
    update_screen(&player_coordinate);
    if (player_coordinate.x == win_condition.x &&
        player_coordinate.y == win_condition.y) {
      cout << clear_sequence << "you won!" << "\033[2H";
      break;
    }
  }

  return 0;
};
