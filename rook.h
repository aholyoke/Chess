#ifndef ROOK__H_
#define ROOK__H_

#include <iostream>
#include <string>
#include <vector>

#include "tile.h"
#include "player.h"
#include "piece.h"


class Rook: public Piece {
	
	public:
	Rook(Player*,char,int,int);	
	std::vector<Tile*> getMoves(Tile**);
};

#endif

