#ifndef PIECE__H_
#define PIECE__H_

#include <iostream>
#include <string>
#include <vector>

#include "tile.h"
#include "player.h"
#include "move.h"

class Player;
class Tile;

class Piece {
	
	Player* player; //What team is piece on.
	std::string colour;
	char gamepiece;		
	int r,c;
	//void getCapturedAndNotifyGrid();
	//bool isPossibleMove(int r, int c); //called by moveToTile before actually moving
	//bool moveToTile(int r, int c); //returns true if successful (isPossibleMove -> true)
	MovePair lastMove;
	bool isFirstMove;
	public:
	Piece(Player*,char,int,int);	
	char getGamePiece();
	void setGamePiece(char);
	Player* getPlayer();
	bool validTile(int , int );
	virtual ~Piece();
	virtual std::vector<Tile*> getMoves(Tile**) = 0;
	int getRow();
	int getCol();
	void setCoord(int,int);
	void updateLastMove(Tile*, Tile*);
	MovePair getLastMove();
	void setColour(std::string);
	std::string getColour();
	bool isPieceFirstMove();
	void setFirstMove(bool);
	bool endangerKing(Tile**,int,int);
	bool inDanger(Tile**);

};

#endif

