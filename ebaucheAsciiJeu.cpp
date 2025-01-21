//if its stupid but works then it isn't stupid
//~someone wiser than me

#include <iostream>
#include <conio.h>
#include <string.h>
using namespace std;

const int W = 119;
const int S = 115;
const int D = 100;
const int A = 97;
const int E = 101;
const int C = 99;

char screen[120*30];
	
struct Ancrage{
   int x;
   int y;
};

class Joueur{

   
public:
	Ancrage ancrage;
	char str = 'o';
	Joueur(int x, int y);
	Bouger(int dir);
	int plusRecentMouvement;
};

Joueur::Bouger(int d){
	plusRecentMouvement = d;
	switch(d){
		case -1: //haut
			if(ancrage.y+1 <30){
				ancrage.y = ancrage.y + 1;
			}
			break;
		case 2: //gauche
			ancrage.x = ancrage.x - 1;
			break;
		case 1: //bas
			if(ancrage.y-1 >0){
				ancrage.y = ancrage.y - 1;
			}
			break;
		case -2: //droite
			ancrage.x = ancrage.x + 1;
			break;
	}
	return 0;
};

Joueur::Joueur(int x, int y){
   ancrage.x = x;
   ancrage.y = y;
};

////////

void titleScreen(){
cout <<
" _____ _____ _____ _____ _____ _____    _____ _____ _____ _____ _____ " << endl <<
"|   __|   __|     |  _  |  _  |   __|  |   __|   __| __  |   __|   __|" << endl <<
"|   __|__   |   --|     |   __|   __|  |__   |   __|    -|  |  |   __|" << endl <<
"|_____|_____|_____|__|__|__|  |_____|  |_____|_____|__|__|_____|_____|" << endl << endl <<

"Press any key to play." << endl;


                                                                                                                          
};

//POURQUOI TU PRENDS UNE ETOILE AAAAA
const char *maze =
"    #########################################################"
"         #     #                 #              #        #  #"
"####  #  #  #  #  ####  #  #  #############  #######  ####  #"
"#     #     #  #  #  #  #  #  #     #           #        #  #"
"#  #  #  ##########  #  #######  #######  #  ####  ####  #  #"
"#  #  #     #        #        #  #  #     #  #     #  #     #"
"####  #  #  #  #######  #######  #  #######  ####  #  #  #  #"
"#     #  #  #     #                 #           #  #     #  #"
"#  #######  ####  #  ####  #############  #  #  ####  #  #  #"
"#        #     #        #     #     #     #  #        #  #  #"
"#  ##########  ####  #######  #  #######  #  ################"
"#     #        #        #                 #  #     #  #     #"
"#  #  #######  ####  ##########  ##########  ####  #  #  ####"
"#  #  #                 #        #                           "
"#############################################################";

void resetScreen(){
   for(int i=0; i<120*30; i++){
      screen[i] = ' ';
   }
};



void updateScreen(Joueur joebama){
	for(int i=0; i<15; i++){
		for(int j=0; j<61; j++){
			screen[120*i+j]= maze[j+i*61];
		}
	}
	screen[joebama.ancrage.x + joebama.ancrage.y*120] = 'o';
};

void displayScreen(){
	cout << screen;
	if(screen[120*13+60] == 'o'){
		system("cls");
		cout << "You win!" <<endl;
	}
};

void gameLoop(Joueur joueur){
   resetScreen();
   system("cls"); //causes flickering, but ensures the 30 x 120 stays 30 x 120 (terminal format, non-fullscreen.
   updateScreen(joueur);
   displayScreen();
};

Joueur joe(0,0);

int main(){
   
	titleScreen();

// code de couleur. je voulais ajouter une cle pis une porte mais
// trop complique a mon gout. mais je laisse ca ici au cas ou

//	cout << "\033[32mThis is green text";
//	cout << "\033[34mThis is blue text";
//	cout << "\033[37mThis is white text";

  
	while(true){
	   int a = getch();

	   if(a == C){
//		   return 0; //to close the game. unnecessary because theres a huge X button up to the right
	   }
	   //this is not smart but it works. please forgive me
	   if(a == A){
		   if(maze[joe.ancrage.x + joe.ancrage.y*61 -1] != '#'){
			   joe.Bouger(2);
           }
		   
	   }
	   if(a == S){
		   if(maze[joe.ancrage.x + joe.ancrage.y*61 +61] != '#'){
			   joe.Bouger(-1);
           }
	   }
	   if(a == D){
		   if(maze[joe.ancrage.x + joe.ancrage.y*61 +1] != '#'){
			   joe.Bouger(-2);
           }
	   }
	   if(a == W){
		   if(maze[joe.ancrage.x + joe.ancrage.y*61 -61] != '#'){
			   joe.Bouger(1);
           }
	   }
	   gameLoop(joe); 
   }
   
   
   
   return 0;
};
