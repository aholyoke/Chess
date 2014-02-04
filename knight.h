#ifndef KNIGHT__H_
#define KNIGHT__H_

#include <iostream>
#include <string>
#include <vector>

#include "tile.h"
#include "player.h"
#include "piece.h"


class Knight: public Piece {
	
	public:
	Knight(Player*,char,int,int);	
	std::vector<Tile*> getMoves(Tile**);
};

#endif

