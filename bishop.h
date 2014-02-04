#ifndef BISHOP__H_
#define BISHOP__H_

#include <iostream>
#include <string>
#include <vector>

#include "tile.h"
#include "player.h"
#include "piece.h"


class Bishop: public Piece {
	
	public:
	Bishop(Player*,char,int,int);	
	std::vector<Tile*> getMoves(Tile**);
};

#endif

