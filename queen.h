#ifndef QUEEN__H_
#define QUEEN__H_

#include <iostream>
#include <string>
#include <vector>

#include "tile.h"
#include "player.h"
#include "piece.h"


class Queen: public Piece {
	
	public:
	Queen(Player*,char,int,int);	
	std::vector<Tile*> getMoves(Tile**);

};

#endif

