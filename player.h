#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>

#include "move.h"
#include "tile.h"

class Tile;
class King;
class Player {

  int direction;
  int winCount;
  Tile* tiles;
  MovePair lastMove;
  King* king;
  public:
    Player(int);	
    std::string value;
    int getDirection();
    MovePair getLastMove();
    void setLastMove(Tile*);
    void gameWon();
    int getWins();
    void setKing(King*);
    King* getKing();
    bool isAI;
    int aiLevel;
    MovePair genAi(Tile**);
    bool isCurPlayer;
    bool isStalemate(Tile**);
    int numMoves;
};

#endif

