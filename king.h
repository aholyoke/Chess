#ifndef KING__H_
#define KING__H_

#include <iostream>
#include <string>
#include <vector>

#include "tile.h"
#include "player.h"
#include "piece.h"


class King: public Piece {
	
	public:
	King(Player*,char,int,int);	
	std::vector<Tile*> getMoves(Tile**);
	bool inCheck(Tile**);
	bool inCheck(Tile**, int, int);
	bool adjacentKing(Tile**,int,int);
	bool inCheckmate(Tile**);
	bool inStalemate(Tile**);
};

#endif

