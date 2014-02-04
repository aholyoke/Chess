#include <sstream>
#include <X11/Xlib.h>
#include <unistd.h>
#include "display.h"
#include "window-v2.h"
#include "move.h"
#include "grid.h"
#include "king.h"

using namespace std;


GraphicsDisplay::GraphicsDisplay(Xwindow *w, Grid* g) {
	this->g = g;
	this->w = w;
	usleep(100000);
	this->w->fillRectangle(0,0, 50, 850, 3);
	this->w->fillRectangle(0, 800, 860, 250, 3);
	this->w->drawBigString(50,  840, "a", 4, 5);
	this->w->drawBigString(150, 850, "b", 4, 5);
	this->w->drawBigString(250, 840, "c", 4, 5);
	this->w->drawBigString(350, 850, "d", 4, 5);
	this->w->drawBigString(450, 840, "e", 4, 5);
	this->w->drawBigString(550, 850, "f", 4, 5);
	this->w->drawBigString(650, 840, "g", 4, 5);
	this->w->drawBigString(750, 850, "h", 4, 5);

	this->w->drawBigString(10, 60, "8", 4, 5);
	this->w->drawBigString(10, 160, "7", 4, 5);
	this->w->drawBigString(10, 260, "6", 4, 5);
	this->w->drawBigString(10, 360, "5", 4, 5);
	this->w->drawBigString(10, 460, "4", 4, 5);
	this->w->drawBigString(10, 560, "3", 4, 5);
	this->w->drawBigString(10, 660, "2", 4, 5);
	this->w->drawBigString(10, 760, "1", 4, 5);
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			this->w->fillRectangle(50+i*100, j*100, 100, 100, (i+j) % 2);
		}
	}
}
void GraphicsDisplay::drawScoreBoardStatic() {
	/*
	Expected to be used between games when it is neither players turn and no player is in check
	*/
	w->fillRectangle(50, 855, 850, 70, 3); 
	int p1Score = 0;
	int p2Score = 0;
	if (g->getPlayer1()!=NULL) {	
		p1Score = g->getPlayer1()->getWins();
		p2Score = g->getPlayer2()->getWins();
	}

	stringstream p1; 
	p1 << "Player 1: " << p1Score;
	stringstream p2; 
	p2 << "Player 2: " << p2Score;
	
	w->drawBigString(50, 900, p1.str().c_str(), 2, 7);
	w->drawBigString(260, 900, p2.str().c_str(), 4, 7);
}

void GraphicsDisplay::drawScoreBoard() {
	/* Global Preconditions: Game is being played, players are instantiated, Xwindow exists
	Global Postconditions: region of scoreboard is completely overwritten and replaced by current score
	*/
	drawScoreBoardStatic();	
	int direction = g->getCurrentPlayer()->getDirection();
	
	w->fillRectangle(155-direction*105, 902, 150, 3, 5);	
	Tile** theGrid = g->getTheGrid();
	King* k1 = g->getPlayer1()->getKing();
	King* k2 = g->getPlayer2()->getKing();
	if (k1->inCheck(theGrid)) {
		if (k1->inCheckmate(theGrid)) w->drawBigString(500, 900, "Checkmate!", 4, 7);
		else w->drawBigString(500, 900, "Check White", 4, 7);
	}else if (k2->inCheck(theGrid)) {
		if (k2->inCheckmate(theGrid)) w->drawBigString(500, 900, "Checkmate!", 2, 7);
		else w->drawBigString(500, 900, "Check Black", 2, 7);
	}else{
		if(k1->inStalemate(theGrid)){
			 w->drawBigString(500, 900, "Stalemate!", 4, 7);
		}
		else if(k2->inStalemate(theGrid)){
			w->drawBigString(500, 900, "Stalemate!", 2, 7);
		}
	}


}

void GraphicsDisplay::update2() { //Total redrawing of game board
	drawScoreBoardStatic();
	Tile** tg = g->getTheGrid();
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 8; i++) {
			this->w->fillRectangle(50+i*100, j*100, 100, 100, (i+j) % 2);
			if (tg[j][i].getPiece()) {
				char c = tg[j][i].getPiece()->getGamePiece();
				int direction = tg[j][i].getPiece()->getPlayer()->getDirection();
				w->drawBigString(i*100+60, j*100+90, string(1, c), 3+direction, 5);
			}
		}
	}
	
}

GraphicsDisplay::~GraphicsDisplay() {
	delete w;
}

void GraphicsDisplay::update(){
	//*
	MovePair newMove = g->getLastMove()->getLastMove();
	int prevr = newMove.prev->getRow();
	int prevc = newMove.prev->getCol();
	int nextr = newMove.cur->getRow();
	int nextc = newMove.cur->getCol();
	char pieceType = newMove.cur->getPiece()->getGamePiece();
	int direction = g->getCurrentPlayer()->getDirection();
	//bool checkMate = g->getCurrentPlayer()->getKing()->inCheck();
	//bool check = g->getCurrentPlayer()->getKing()->inCheck();

	/**/
	
	w->fillRectangle(50+prevc*100, prevr*100, 100, 100, (prevr+prevc) % 2);
	w->fillRectangle(50+nextc*100, nextr*100, 100, 100, (nextr+nextc) % 2);
	w->drawBigString(nextc*100+60, nextr*100+90, string(1, pieceType), 3+direction, 5);
	drawScoreBoard();
}
