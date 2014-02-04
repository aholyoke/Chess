#include <iostream>
#include <vector>
#include "player.h"
#include "move.h"
#include "PRNG.h"
#include <ctime>
#include "king.h"


using namespace std;

Player::Player(int dir){
	direction = dir;
	winCount = 0;
	isAI = false;
	isCurPlayer = false;
	numMoves = 0;
}

int Player::getDirection(){
	return direction;
}

MovePair Player::getLastMove(){
	return lastMove;
}

void Player::setLastMove(Tile* curTile){
	lastMove.cur = curTile;
}

void Player::gameWon(){
	winCount++;
}

int Player::getWins(){
	return winCount;
}

void Player::setKing(King* king){
	this->king = king;
}

King* Player::getKing(){
	return king;
}

MovePair Player::genAi(Tile** theGrid){
	cerr <<"calling genai" << endl;
	MovePair genMove;

	genMove.prev = &(theGrid[0][0]);
	genMove.cur = &(theGrid[0][0]);	

	vector<MovePair> allMoves;
	
	for(int i =0; i<8;i++){
		for(int j=0;j<8;j++){
			if(theGrid[i][j].getPiece()!=NULL){
				if(theGrid[i][j].getPiece()->getPlayer()==this){
					vector<Tile*> tmpMoves = theGrid[i][j].getPiece()->getMoves(theGrid);
					for (int k=0; k<tmpMoves.size(); k++) {
						MovePair mp;
						mp.prev = &theGrid[i][j];
						mp.cur = tmpMoves[k];
						allMoves.push_back(mp);
					}
				}
			}																	
		}
	}
	//We have now collected all the pieces at the disposal of AI which can move
	//And all moves available
	
	

	vector<int> distribution;
	for (int i=0; i < allMoves.size(); i++) {
		distribution.push_back(1);
	}
	if (aiLevel>=2) {
		for (int i=0; i < allMoves.size(); i++) {
			if (allMoves[i].cur->getPiece() != NULL) {
				int importance = 1;
				if (allMoves[i].cur->getPiece()->getGamePiece() == 'N') importance = 5;
				else if (allMoves[i].cur->getPiece()->getGamePiece() == 'R') importance = 15;
				else if (allMoves[i].cur->getPiece()->getGamePiece() == 'B') importance = 30;
				else if (allMoves[i].cur->getPiece()->getGamePiece() == 'Q') importance = 100;
				distribution[i]+= importance;
			}
		}
	} if (aiLevel>=3) {
		for (int i=0; i < allMoves.size(); i++) {
			if (allMoves[i].prev->getPiece()->inDanger(theGrid)) {
				int importance = 1;
				if (allMoves[i].prev->getPiece()->getGamePiece() == 'N') importance = 5;
				else if (allMoves[i].prev->getPiece()->getGamePiece() == 'R') importance = 15;
				else if (allMoves[i].prev->getPiece()->getGamePiece() == 'B') importance = 30;
				else if (allMoves[i].prev->getPiece()->getGamePiece() == 'Q') importance = 1000;
				distribution[i]+=importance;
			}
		}
	} if (aiLevel>=4) {
		King* k;
		for (int i = 0; i < allMoves.size(); i++) { //find enemy king 
			Piece* targetPiece = allMoves[i].cur->getPiece();
			if (targetPiece!=NULL && targetPiece->getGamePiece() == 'K') {
				k = static_cast<King*>(targetPiece);
			}
		}

		for (int i = 0; i < allMoves.size(); i++) {
			int r = allMoves[i].prev->getRow();
			int c = allMoves[i].prev->getCol();
			int nr = allMoves[i].cur->getRow();
			int nc = allMoves[i].cur->getCol();
			if (numMoves < 6) { //Make good opening moves
				if ((r == 6 || r == 1) && (c == 3 || c== 4)) {
					distribution[i]+= 4;
				} else if ((r == 7 || r == 0) && (c == 2 || c == 5)) {
					distribution[i]+= 3;
				} else if ((r == 7 || r == 0) && (c == 1 || c == 6)) {
					distribution[i]+= 6;
				}
			}
			//The following code supposes we enact the given move, then examines the quality of the move
			Piece* myPiece= theGrid[r][c].getPiece();
			Piece* targetPiece = theGrid[nr][nc].getPiece(); //Often is Null
			theGrid[r][c].releasePiece();
			theGrid[nr][nc].releasePiece();
			theGrid[nr][nc].replacePiece(myPiece);
			//prefer putting king in check
			if (k->inCheck(theGrid))
				distribution[i]+=600;
			
			if (myPiece->inDanger(theGrid)) { // If this move risks the piece
				char pieceType = myPiece->getGamePiece();
				if (pieceType == 'Q') {
					distribution[i]= 0; // never endanger queen
				} else if (pieceType == 'B') {
					distribution[i]/= 5; //rarely endanger bishop
				}
			}
			/*
			if (k->inCheckmate(theGrid)) {
				for (int k=0; k < allMoves.size(); k++)
					distribution[k] = 0;
				distribution[i] = 1;
				break;
			}
			*/
			theGrid[nr][nc].releasePiece();
			theGrid[nr][nc].replacePiece(targetPiece);
			theGrid[r][c].replacePiece(myPiece);
		}
	}
	
	PRNG p(time(NULL));
	int sumOfDistr = 0;
	for (int i = 0; i < distribution.size(); i++) {
		sumOfDistr+= distribution[i];
	}

	int randomNum = p(0, sumOfDistr);
	for (int i=0; i < distribution.size(); i++) {
		randomNum -= distribution[i];
		if (randomNum <= 0) {
			genMove = allMoves[i];
			break;
		}
	}
	
	return genMove;
}




