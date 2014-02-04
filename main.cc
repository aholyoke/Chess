#include <iostream>
#include <string>
#include "grid.h"
#include "tile.h"
#include "display.h"
#include "window-v2.h"

using namespace std;

int main(){
	Xwindow* w = new Xwindow(850, 920);
	bool exit = true;
	istream* in = &cin;
	Grid* gr = new Grid(in);
	GraphicsDisplay* gDisplay = new GraphicsDisplay(w,gr);
	gr->attach(gDisplay);
	Player p1(-1);
	p1.value = "W";
	Player p2(1);
	p2.value = "B";
	gr->init(p1,p2);
	string input;
	*in >> input;
	if(input=="exit") exit = false;

	while(!in->fail()&&exit){
		if(input=="game" && !gr->inGame){
			gr->startGame();
			cout << *gr << endl;
		}
		else if(input=="moves" && gr->inGame){
			gr->debugMoves();
		}
		else if(input=="resign" && gr->inGame){
			gr->resign();
		}
		else if(input=="move" && gr->inGame){
			if(gr->makeMove()){
				gr->endTurn();
			}
			cout << *gr << endl;	
		}
		else if(input=="setup" && !gr->inGame){
			gr->setup();
			gr->isSetup = true;
		}
		
		if(gr->gameContinue()){	
			*in >> input;
			if(input == "exit"){
				exit = false;
			}
		}	
		else{
			gr->printScoreboard();
			bool replay = true;		
			while(replay){
				cout << "Do you want to play again?[y]es [n]o" << endl;		
				string answer;	
				*in >> answer;
				if(answer=="y"){
					replay = false;
				}
				if(answer=="n"){
					replay = false;
					exit = false;
				}
			}
				
							
			gr->continueGames();
			input = "";	
		}

	}
	gr->printScoreboard();

	delete gr;
	delete gDisplay;
	
}
