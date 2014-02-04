#ifndef PAWN__H_
#define PAWN__H_

#include <iostream>
#include <string>
#include <vector>

#include "tile.h"
#include "player.h"
#include "piece.h"


class Pawn: public Piece {


	public:
	Pawn(Player*,char,int,int);	
	std::vector<Tile*> getMoves(Tile**);
	bool isFirstMove();
};

#endif

