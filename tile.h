#ifndef __TILE_H__
#define __TILE_H__
#include <iostream>
#include "piece.h"
#include "player.h"

class Piece;

class Tile {
  Player* player;
  Piece* piece; 
  //Piece* piece;
  int r,c;

 public:
  Tile();  // Default constructor
  ~Tile();
  void setCoords(int r, int c);
  int getRow();
  int getCol(); 
  // void setCoords(int x, int y, int width, int height, Xwindow *w);
  void setPiece(Piece*);
  void releasePiece();
  void replacePiece(Piece*);
  Piece* getPiece();
  void clearTile();

};

#endif
