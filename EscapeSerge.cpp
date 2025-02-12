// if its stupid but works then it isn't stupid
//~someone wiser than me

#include <cstdio>
#include <iostream>

#ifdef _WIN32 //si sur Windows,
#include <conio.h>
#else //si pas sur Windows,
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
    "      $  #     #                 #              #        #  #",
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
    
const char* cadenas4ChiffresOuvert[] = {
"     .--------.                ",
"    / .------. \\               ",
"   / /        \\ \\              ",
"   | |        | |              ",
"   | |       _| |________ _    ",
"   |_|     .' |_|           '. ",
"           '._____ ____ _____.'",
"           |     .'____'.     |",
"           '.__.'.'    '.'.__.'",
"           '.__  | GOOD |  __.'",
"           |   '.'.____.'.'   |",
"           '.____'.____.'____.'",
"           '.________________.'"
};

Coordinates cadenas4ChiffresOuvertC = {32, 13};


const char* cadenas4ChiffresFerme[] = {
"     .--------.     ",
"    / .------. \\    ",
"   / /        \\ \\   ",
"   | |        | |   ",
"  _| |________| |_  ",
".' |_|        |_| '.",
"'._____ ____ _____.'",
"|     .'____'.     |",
"'.__.'.'    '.'.__.'",
"'.__  | 0000 |  __.'",
"|   '.'.____.'.'   |",
"'.____'.____.'____.'",
"'.________________.'"
};

bool interactingLock = false;
bool unlocked = false;

Coordinates cadenas4ChiffresFermeC = {20, 13};

int selectionCadenas = 3;
int Cadenas[4] = {};

//Verification que le joueur peut aller ou il veut aller
static bool is_move_valid(const Coordinates *player_coordinate) {
  bool not_out_of_bounds =
      player_coordinate->x >= 0 && player_coordinate->x <= maze_dimen.x &&
      player_coordinate->y >= 0 && player_coordinate->y <= maze_dimen.y;
  if (!not_out_of_bounds)
    return false;
  return maze[player_coordinate->y][player_coordinate->x] != '#';
}
//Verification que la tuile est vide (peut etre vide, mur, porte, ...)
bool isASpecialTile(const Coordinates *player_coordinate){
	if (!(is_move_valid(player_coordinate))){
		return false;
	}
	return maze[player_coordinate->y][player_coordinate->x] != ' ';
}

//Deplacement du joueur, inclue verifications
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
	  if (isASpecialTile(&new_coord)){
		  if(maze[new_coord.y][new_coord.x] == '$'){
			  if (unlocked){
				  *player_coordinate = new_coord;
				  return true;
			  }
			  interactingLock = true;
		  }
		  return false;
	  }
    *player_coordinate = new_coord;
    return true;
  }
  return false;
}
//Sortir du jeu
static bool should_quit(char key_presed, const Coordinates *player_coordinate) {
  switch (key_presed) {
  case 'Q':
  case 'q':
    return true;
  default:
    return false;
  }
}
//Imprimer labyrinthe (au debut et suite de jeux)
static void print_maze() {
  for (size_t i = 0; i <= maze_dimen.y; i++) {
    cout << maze[i];
    Coordinates c = {0, ((int)i) + 1};
    move_cursor(&c);
  }
}
//Apres avoir deplace le joueur
static void remove_player_char(const Coordinates *player_coord) {
  move_cursor(player_coord);
  cout << ' ';
  move_cursor(&origin);
}
//Deplacer le joueur
static void print_player_char(const Coordinates *player_coord) {
  move_cursor(player_coord);
  cout << 'o';
  move_cursor(&origin);
}

static void clear_screen() { cout << "\033[2J\033[1H"; }

//Afficher un cadenas 4 chiffres ferme
void afficherCadenasFerme(){
	clear_screen();
	for(int i=0; i<cadenas4ChiffresFermeC.y; i++){
		cout << cadenas4ChiffresFerme[i];
		Coordinates c = {0, ((int)i) + 1};
		move_cursor(&c);
	}
	cout << endl << "W & D : Changer le chiffre" << endl << "A & D : Changer la selection" << endl << "E : Valider la combinaison" << endl << "C : Sortir" << endl;
}
//Une fois le cadenas 4 chiffres ouvert,
void afficherCadenasOuvert(){
	clear_screen();
	for(int i=0; i<cadenas4ChiffresOuvertC.y; i++){
		cout << cadenas4ChiffresOuvert[i];
		Coordinates c = {0, ((int)i) + 1};
		move_cursor(&c);
	}
}
//Modifier les chiffres du cadenas 4 chiffres pcq il affiche 0000 sinon
void updateCadenasFerme(){
	Coordinates a = {8, 9};
	move_cursor(&a);
	for(int i=0; i<4; i++){
		cout << Cadenas[i];
	}
	
	
}
//Changer les chiffres du cadenas 4 chiffres
void changerChiffreCadenas(int signe){
	Cadenas[selectionCadenas] += signe;
	
	if(Cadenas[selectionCadenas] <= -1){
		Cadenas[selectionCadenas] = 9;
	}
	if(Cadenas[selectionCadenas] >= 10){
		Cadenas[selectionCadenas] = 0;
	}
	updateCadenasFerme();
}
//Changer le chiffre qu'on modifie du cadenas 4 chiffres
void changerSelectionCadenas(int signe){
	selectionCadenas += signe;
	if(selectionCadenas >= 4){
		selectionCadenas = 0;
	}
	if(selectionCadenas <= -1){
		selectionCadenas = 3;
	}
	updateCadenasFerme();
}

//Verifier la combinaison du cadenas
void verifierCombinaisonCadenas(){
	Coordinates b = {1, 15};
	move_cursor(&b);
	if(Cadenas[0] == 1 && Cadenas[1] == 2 && Cadenas[2] == 3 && Cadenas[3] == 4){		
		unlocked = true;
		afficherCadenasOuvert();
		return;
	}
	cout << "Bad job" << endl;
	updateCadenasFerme();
	return;
}
//Quand le joueur veut sortir du cadenas
void sortirCadenas(Coordinates *coord){
	interactingLock = false;
	clear_screen();
	print_maze();
	print_player_char(coord);
}




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
  
	//initialisation du cadenas a 4 chiffres
  for(int i=0; i<4; i++){
	  Cadenas[i] = 0;
  }
  
	//loop
  while (true) {
    char user_input = getch();
    
    if (should_quit(user_input, &player_coordinate))
      break;
      
	//mode de navigation normal du labyrinthe
if(!interactingLock){      
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
    
    //si dans l'interface cadenas
if(interactingLock){
	if(unlocked){ //this is hacky
		sortirCadenas(&player_coordinate);
		user_input = 'c'; 
	}
	afficherCadenasFerme();
    switch (user_input){
		case 'W':
		case 'w':
			changerChiffreCadenas(1);
			break;
		case 'S':
		case 's':
			changerChiffreCadenas(-1);
			break;
		case 'A':
		case 'a':
			changerSelectionCadenas(-1);
			break;
		case 'D':
		case 'd':
			changerSelectionCadenas(1);
			break;
		case 'E':
		case 'e':
			verifierCombinaisonCadenas();
			break;
		case 'C':
		case 'c':
			sortirCadenas(&player_coordinate);
			break;
	}
    
  }
}
	clear_screen();
  return 0;
};
