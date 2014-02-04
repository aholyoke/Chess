#include <iostream>
#include <string>
#include <vector>

#include "piece.h"
#include "king.h"
#include "tile.h"

using namespace std;

Piece::Piece(Player* p,char gp,int r,int c){
	player = p;
	gamepiece = gp;
	this->r = r;
	this->c = c;	
	lastMove.prev = NULL;
	lastMove.cur = NULL;
	isFirstMove = true;
}

Piece::~Piece(){}

void Piece::setGamePiece(char newPiece){
	gamepiece = newPiece;
}

char Piece::getGamePiece(){
	return gamepiece;
}

Player* Piece::getPlayer(){
	return player;
}

std::vector<Tile*> Piece::getMoves(Tile** theGrid){	
	std::vector<Tile*> vec;
	return vec;
}
bool Piece::validTile(int r, int c){
        if(r>=0&&r<=7&&c>=0&&c<=7){
                return true;
        }
        return false;
}

int Piece::getRow(){
	return r;
}

int Piece::getCol(){
	return c;
}

void Piece::setCoord(int r, int c){
	this->r = r;
	this->c = c;
}

void Piece::updateLastMove(Tile* prev, Tile* cur){
	lastMove.prev = prev;
	lastMove.cur = cur;
}

MovePair Piece::getLastMove () {
	return lastMove;
}

void Piece::setColour(std::string col){
	colour = col;		
}

std::string Piece::getColour(){
	return colour;
}

bool Piece::isPieceFirstMove(){
	return isFirstMove;
}

void Piece::setFirstMove(bool move){

	isFirstMove = move;
}

bool Piece::endangerKing(Tile** theGrid, int newRow, int newCol){
	int curRow = getRow();
	int curCol = getCol();
	vector<Tile*> moves;

	Piece* movedPiece = theGrid[newRow][newCol].getPiece();
	theGrid[newRow][newCol].releasePiece();
	theGrid[curRow][curCol].releasePiece();
	theGrid[newRow][newCol].replacePiece(this);

	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(theGrid[i][j].getPiece()!=NULL && theGrid[i][j].getPiece()->getPlayer()!=getPlayer() && theGrid[i][j].getPiece()->getGamePiece()!='K'){
				vector<Tile*> pieceMoves= theGrid[i][j].getPiece()->getMoves(theGrid);
				for(int k = 0; k<pieceMoves.size();k++){
					moves.push_back(pieceMoves[k]);
				}
			}
		}
	}

	theGrid[newRow][newCol].releasePiece();
	theGrid[newRow][newCol].replacePiece(movedPiece);
	
	theGrid[curRow][curCol].replacePiece(this);	

	int rowK = getPlayer()->getKing()->getRow();
	int colK = getPlayer()->getKing()->getCol();
	
	for(int c = 0; c<moves.size(); c++){
		if(moves[c]->getRow()==rowK && moves[c]->getCol()==colK){
			return true;
		}		
	}		

	return false;
}

bool Piece::inDanger(Tile** theGrid){
        for(int i = 0; i<8; i++){
                for(int j=0; j<8; j++){
                        if(theGrid[i][j].getPiece()!=NULL){
                                if(theGrid[i][j].getPiece()->getPlayer()!=getPlayer()){
                                        if(theGrid[i][j].getPiece()->getGamePiece()!='K'){
                                                vector<Tile*> pieceMoves= theGrid[i][j].getPiece()->getMoves(theGrid);
                                                for(int d = 0; d<pieceMoves.size();d++){
							if(pieceMoves[d]->getRow()==getRow() && pieceMoves[d]->getCol()==getCol()){
								return true;	
							}
                                                }
                                        }
                                }
                        }
                }
        }
	
	return false;
}
