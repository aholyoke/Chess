#ifndef __GRID_H__
#define __GRID_H__
#include <iostream>
#include <vector>

#include "tile.h"
#include "player.h"
#include "move.h"
#include "piece.h"
#include "subject.h"


class Grid: public Subject {
  Tile **theGrid;  
  int gridSize; 
  Player* player1;
  Player* player2;
  Player* curPlayer;
  std::istream* in;
  bool cont;
  Piece* lastMoved;

 public:
  Grid(std::istream*);
  ~Grid();
  bool isSetup;
  bool inGame;
  bool validTile(int, int);
  void addNeighbour(Tile&, int, int);
  void clearGrid();  
  void init(Player, Player);  
  void setup();
  void endTurn();
  void endGame(Player*);
  bool gameContinue();
  void changeCurrentPlayer();
  std::vector<Tile*> getMoves(int,int);
  void stdSetup();
  Piece* getLastMove(); 
  bool makeMove();
  bool isValidMove(Tile*, Tile*);
  Player* getCurrentPlayer(); 
  void resign();
  void continueGames();
  void printScoreboard();
  void setCurrentPlayer(Player* );
  void printGrid();
  Tile** getTheGrid(); //Alex wants this dont delete it jonah. lol.
  void setLastMoved(Piece*);
  void deleteGrid();
  void debugMoves();
  void promotePawn(Tile*,char,Player*);
  void startGame();

  Player* getPlayer1();
  Player* getPlayer2();


  friend std::ostream& ::operator<<(std::ostream &out, const Grid &g);
};

#endif

