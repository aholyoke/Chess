#include <iostream>
#include <string>
#include <vector>

#include "grid.h"
#include "tile.h"
#include "player.h"
#include "pawn.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "king.h"
#include "move.h"

using namespace std;

Grid::Grid(istream* str){
	/*
		Grid has a lot of booleans that can describe the state of a turn or a game at a given moment. 
	*/
	in = str;
	theGrid = NULL;
	gridSize = 8;
	curPlayer = NULL;
	cont = true;
	lastMoved = NULL;
	inGame = false;
	isSetup = false;	
}
/*Create a destruct that deletes the grid, meaning that it actually destroys all of the tiles on the grid rather than just frees them (see clear grid)*/
Grid::~Grid(){
  deleteGrid();
}

Player* Grid::getPlayer1(){
	return player1;
}

Player* Grid::getPlayer2(){
	return player2;
}
/*
we need to be able to clear the grid whenever a new game starts.This doesn't deallocate any memory, but rather resets the players and clears the grid of any pieces 
*/
void Grid::clearGrid(){
	for(int i = 0; i<gridSize; i++){
		for(int j = 0; j< gridSize; j++){
			theGrid[i][j].clearTile();
		}
	}	

	bool isSingleMove = false;
	
	player1->numMoves = 0;
	player2->numMoves = 0;
		
	notify(isSingleMove);
}
/*
delete grid will actually deallocate the memory used in the board. It deletes all of the tiles. This should be called ONLY when the grid is to be no longer used (end of game)
*/
void Grid::deleteGrid(){

	for (int i=0; i<gridSize; i++){
		delete [] theGrid[i]; // delete each row array
	}

	delete [] theGrid;  // delete the array of rows	

}
	
/*
Initializes the grid and new game with two player objects created and sent from the main class
*/
void Grid::init(Player p1, Player p2){
	if(NULL!=theGrid){	
		clearGrid();
	}
	player1 = &p1;
	player2 = &p2;
	curPlayer = player1;
	theGrid = new Tile*[gridSize];
	//new tiles created and the grid is populated with them
	for(int i =0; i<gridSize; i++){
		theGrid[i] = new Tile[gridSize];
		for(int j=0; j<gridSize; j++){
			theGrid[i][j].setCoords(i,j);	
		}
	}
}

void Grid::stdSetup(){
//set up a standard chess game


theGrid[0][0].setPiece( new Rook(player2,'R',0,0)); 
theGrid[0][1].setPiece( new Knight(player2,'N',0,1)); 
theGrid[0][2].setPiece( new Bishop(player2,'B',0,2)); 
theGrid[0][3].setPiece( new Queen(player2,'Q',0,3)); 
theGrid[0][4].setPiece( new King(player2,'K',0,4)); 
theGrid[0][5].setPiece( new Bishop(player2,'B',0,5)); 
theGrid[0][6].setPiece( new Knight(player2,'N',0,6)); 
theGrid[0][7].setPiece( new Rook(player2,'R',0,7)); 

theGrid[7][0].setPiece( new Rook(player1,'R',7,0)); 
theGrid[7][1].setPiece( new Knight(player1,'N',7,1)); 
theGrid[7][2].setPiece( new Bishop(player1,'B',7,2)); 
theGrid[7][3].setPiece( new Queen(player1,'Q',7,3)); 
theGrid[7][4].setPiece( new King(player1,'K',7,4)); 
theGrid[7][5].setPiece( new Bishop(player1,'B',7,5)); 
theGrid[7][6].setPiece( new Knight(player1,'N',7,6)); 
theGrid[7][7].setPiece( new Rook(player1,'R',7,7)); 


theGrid[6][0].setPiece( new Pawn(player1,'P',6,0)); 
theGrid[6][1].setPiece( new Pawn(player1,'P',6,1)); 
theGrid[6][2].setPiece( new Pawn(player1,'P',6,2)); 
theGrid[6][3].setPiece( new Pawn(player1,'P',6,3)); 
theGrid[6][4].setPiece( new Pawn(player1,'P',6,4)); 
theGrid[6][5].setPiece( new Pawn(player1,'P',6,5)); 
theGrid[6][6].setPiece( new Pawn(player1,'P',6,6)); 
theGrid[6][7].setPiece( new Pawn(player1,'P',6,7)); 


theGrid[1][0].setPiece( new Pawn(player2,'P',1,0)); 
theGrid[1][1].setPiece( new Pawn(player2,'P',1,1)); 
theGrid[1][2].setPiece( new Pawn(player2,'P',1,2)); 
theGrid[1][3].setPiece( new Pawn(player2,'P',1,3)); 
theGrid[1][4].setPiece( new Pawn(player2,'P',1,4)); 
theGrid[1][5].setPiece( new Pawn(player2,'P',1,5)); 
theGrid[1][6].setPiece( new Pawn(player2,'P',1,6)); 
theGrid[1][7].setPiece( new Pawn(player2,'P',1,7)); 

inGame = true;

bool isSingleMove = false;

notify(isSingleMove);

}
/*
Check ifa given position to a new position is a valid move for a piece.
*/
bool Grid::isValidMove(Tile* curPos, Tile* newPos){
	
	if(curPos == newPos){
		return false;
	}
	
	if(curPos->getPiece()==NULL){
		return false;
	}	
	else{
		if(curPos->getPiece()->getPlayer()!=curPlayer){
			return false;
		}
		vector<Tile*> moves = curPos->getPiece()->getMoves(theGrid);
		cerr << "Moves size is: " << moves.size() << endl;
		for(int i = 0; i<moves.size(); i++){
			if(moves[i] == newPos){
				return true;
			}
		}
	}
	return false;
}

/*
Make move is the central function of the movement of a piece. It decides if a movement is possible and then actually augments the grid to reflect changes
*/

bool Grid::makeMove(){



		char curCol;
		int curRow;

		char newCol;
		int newRow;

		

		int curBoardCol;
		int curBoardRow;
		int newBoardCol;
		int newBoardRow;	

		//if a player has AI on then we simply receive it's move through the genAI function rather than through std in		
		if(curPlayer->isAI==true){
				MovePair aiMove = curPlayer->genAi(theGrid);


				curBoardRow  = aiMove.prev->getRow();
				curBoardCol  = aiMove.prev->getCol();

				newBoardRow  = aiMove.cur->getRow();
				newBoardCol  = aiMove.cur->getCol();

		}
		else{	
			//if its not AI we receive the movement through stdandard in
			*in >> curCol >> curRow >> newCol >> newRow;
			curBoardCol = curCol - 97;
			curBoardRow = 8 - curRow;
			newBoardCol = newCol - 97;
			newBoardRow = 8 - newRow;	
		}

		char newPiece;

		if(validTile(curBoardRow,curBoardCol) && validTile(newBoardRow,newBoardCol)){
			if(isValidMove(&theGrid[curBoardRow][curBoardCol], &theGrid[newBoardRow][newBoardCol])){
				Piece* movedPiece = theGrid[curBoardRow][curBoardCol].getPiece();

				bool isEnPassant=false;
				bool isCastling = false;
/*
because enpassant and castling require more than one move to be changed, we need check for them and set a boolean to let the grid know it needs to change more than one piece
*/
				if(movedPiece->getGamePiece()=='P' && newBoardCol!=curBoardCol){
					if(theGrid[newBoardRow][newBoardCol].getPiece()==NULL){
						isEnPassant = true;
					}	
				}
		
				if(movedPiece->getGamePiece()=='K' && (newBoardCol==curBoardCol+2||newBoardCol==curBoardCol-2)){
					isCastling = true;
				}
				
				Piece* oldPiece = theGrid[newBoardRow][newBoardCol].getPiece();
	
				theGrid[newBoardRow][newBoardCol].setPiece(movedPiece);
				theGrid[curBoardRow][curBoardCol].releasePiece();

/*
pawn promotion requires another read from stdin so we need to check to see if a pawn from the opposite side has made it to the other side of the board
*/

                                if(movedPiece->getGamePiece()=='P'){
                                        if(movedPiece->getPlayer()->getDirection()==-1){
                                                if(newBoardRow==0){
                                                        *in >> newPiece;
                                                        promotePawn(&(theGrid[newBoardRow][newBoardCol]),newPiece,movedPiece->getPlayer());
							movedPiece = theGrid[newBoardRow][newBoardCol].getPiece();
                                                }
                                        }else{
                                                if(newBoardRow==7){
                                                        *in >> newPiece;
                                                        promotePawn(&(theGrid[newBoardRow][newBoardCol]),newPiece,movedPiece->getPlayer());
							movedPiece = theGrid[newBoardRow][newBoardCol].getPiece();
                                                }
                                        }
                               }

/*
after the primary pieces are moves, we update the move pair so that it can be referenced by other pieces, to see who the last piece was that was moved
*/
				movedPiece->updateLastMove(&(theGrid[curBoardRow][curBoardCol]),&(theGrid[newBoardRow][newBoardCol]));
				setLastMoved(movedPiece);
				curPlayer->setLastMove(&(theGrid[newBoardRow][newBoardCol]));
				/*
				en passant check	
				*/
				bool isSingleMove = true;	
				if(isEnPassant){
					//if its in en passant we need to now remove the piece that was passed
					int passedPawnC = newBoardCol;		
					int passedPawnR = newBoardRow - (movedPiece->getPlayer()->getDirection());
					Piece* passedPawn = theGrid[passedPawnR][passedPawnC].getPiece();
					theGrid[passedPawnR][passedPawnC].releasePiece();
					delete passedPawn;			
					isSingleMove = false;
				}
				if(isCastling){
					//if we castled, we need to also move the rook
					if(newBoardCol==curBoardCol+2){
						Piece* rook = theGrid[movedPiece->getRow()][7].getPiece();
						theGrid[rook->getRow()][rook->getCol()].releasePiece();
						theGrid[rook->getRow()][5].replacePiece(rook);			
					}
					else{
						Piece* rook = theGrid[movedPiece->getRow()][0].getPiece();
						theGrid[rook->getRow()][rook->getCol()].releasePiece();
						theGrid[rook->getRow()][3].replacePiece(rook);			
					}
					isSingleMove = false;
				}
				if(movedPiece->isPieceFirstMove()){
					movedPiece->setFirstMove(false);
				}
			
				curPlayer->numMoves++;
	
				notify(isSingleMove);
				return true;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}

}


/*
debug moves is a helpful feature that allows us to access the possible moves for any pieces straight from the command prompt
*/

void Grid::debugMoves(){
char col;
int row;
*in >> col >> row;
int boardCol = col-97;
int boardRow = 8-row;
if(boardRow >=0 && boardRow <=7 && boardCol >= 0 && boardCol <=7 ){
	if(theGrid[boardRow][boardCol].getPiece()!=NULL){
		Piece* piece = theGrid[boardRow][boardCol].getPiece();
		cout << "Gamepiece: " << piece->getPlayer()->value << piece->getGamePiece() << " has moves (from " << piece->getRow() << " " << piece->getCol() << "): " <<endl;
		vector<Tile*> moveList = piece->getMoves(theGrid);
		for(int i = 0; i < moveList.size(); i++){
			char colP = moveList[i]->getCol() + 97;
			int rP = 8 -  moveList[i]->getRow();
			cout << "" << colP << rP << endl;	
		}
	}
	else{
		cout << "No Piece in that Tile" << endl;
	}

}else{
	cout << "Out of Bounds" << endl;
}
}


/*
setup is the function that is called by the main function in order to create your own board to use
*/
void Grid::setup(){

string player1Type;
string player2Type;

int level;


	bool notDone=true;
	std::string op;
	std::string colour;
	char piece,col;
	int row;
	*in >> op;
	while(notDone){
		if(op=="+"){
			*in >> piece >> col >> row;
			int boardCol = col-97;	
			int boardRow = 8-row;
			if(boardRow >=0 && boardRow <=7 && boardCol >= 0 && boardCol <=7 ){
				if(piece=='P'){
					theGrid[boardRow][boardCol].setPiece( new Pawn(curPlayer,piece,boardRow,boardCol));		
				}
				else if(piece=='Q'){
					theGrid[boardRow][boardCol].setPiece( new Queen(curPlayer,piece,boardRow,boardCol));	
				}
				else if(piece=='B'){
					theGrid[boardRow][boardCol].setPiece( new Bishop(curPlayer,piece,boardRow,boardCol));	
				}
				else if(piece=='R'){
					theGrid[boardRow][boardCol].setPiece( new Rook(curPlayer,piece,boardRow,boardCol));	
				}
				else if(piece=='N'){
					theGrid[boardRow][boardCol].setPiece( new Knight(curPlayer,piece,boardRow,boardCol));	
				}
				else if(piece=='K'){
					theGrid[boardRow][boardCol].setPiece( new King(curPlayer,piece,boardRow,boardCol));	
				}
				bool isSingleMove=  false;
				notify(isSingleMove);
			}
			std::cout << *this << endl;
		}
		else if (op=="="){
			*in >> colour;
			if(!(colour == "black" && curPlayer == player2)){
				changeCurrentPlayer();	
			}
			else if(!(colour == "white" && curPlayer == player1)){
				changeCurrentPlayer();	
			}	
		}
		else if(op=="-"){
			*in >>col>>row;
			int boardCol = col-97;	
			int boardRow = 8-row;
			if(boardRow >=0 && boardRow <=7 && boardCol >= 0 && boardCol <=7 ){
				Piece* remPiece = theGrid[boardRow][boardCol].getPiece();
				theGrid[boardRow][boardCol].releasePiece();
				delete remPiece;
				std::cout << *this << endl;
				notify(false);
			}
		}
		else if(op=="done"){
			//check that they are actually done
			//check that player one has everything correctly set up
			//if the kings are both at exactly one, then we can begin
			int p2King = 0;
			int p1King = 0;
	
			for(int i = 0; i < gridSize; i++){
				for(int j=0; j< gridSize; j++){
					if(NULL!=theGrid[i][j].getPiece()){
						Piece* curPiece = theGrid[i][j].getPiece();
						if(curPiece->getGamePiece()=='K'){
							King* king = (King*)curPiece; 
							if(king->getPlayer()==player1){
								p1King++;	
							}
							else{
								p2King++;
							}
							if(king->inCheck(theGrid)){
								if(king->getPlayer()==player1){
									p1King++;	
									cout << "P1 in check " << endl;
								}
								else{
									p2King++;
									cout << "P2 in check " << endl;
								}
							}	
						}
					}
				}
			}
			if(p1King==1 && p2King==1){
				notDone = false;		
				inGame = true;
			}
			else{
				cout << "You're not quite done .. " << endl;			
			}
		}
		if(notDone){
			*in >> op;
		}
	}
	//set first move to false for all players
	//since the state of the moves prior to a set up is technically unknown, we don't allow en passant or castling to occur
	for(int r = 0; r<8; r++){
		for(int c = 0; c < 8; c++){
			if(theGrid[r][c].getPiece()!=NULL){
				theGrid[r][c].getPiece()->setFirstMove(false);
			}	
		}
	}
	
	curPlayer = player1;
	player1->isCurPlayer = true;
	player2->isCurPlayer = false;
		
}

/*
change the current player at the end of each turn so that the grid can tell what pieces can and can't be moved
*/
void Grid::changeCurrentPlayer(){
	if(curPlayer == player1){
		curPlayer = player2;
		player2->isCurPlayer = true;
		player1->isCurPlayer = false;
		cout << "Player 2's Turn: " << endl;
	}
	else{
		curPlayer = player1;
		player1->isCurPlayer = true;
		player2->isCurPlayer = false;
		cout << "Player 1's turn" << endl;
	}
}

void Grid::endTurn(){
	/*
		at the end of each turn, we should check if either player is in check mate or stalemate
		and award a point to the winner of the game
	*/

	if(player1->getKing()->inCheckmate(theGrid))
	{
		endGame(player2);
	}
	else if(player2->getKing()->inCheckmate(theGrid)){
		endGame(player1);
	}
	else{
		if(player1->getKing()->inStalemate(theGrid))
		{
			endGame(player2);
		}
		else if(player2->getKing()->inStalemate(theGrid)){
			endGame(player1);
		}
	}
	
	
	if(gameContinue()){
		changeCurrentPlayer();
	}
}
/*
if the game has ended we need to let the main function find out. this changes a grid boolean to let the main function know if the game has ended or not
*/
bool Grid::gameContinue(){
	return cont;
}
/*
get last move returns the last moved item from the grid. this is used by display to figure out which regious to redraw
*/
Piece* Grid::getLastMove(){
	return lastMoved;
}
/*
a text version of the board is drawn here with Black pieces in Red and white pieces in white
*/
ostream& operator<<(std::ostream &out, const Grid &g){
	for(int i =0; i<g.gridSize; i++){
		for(int j=0;j<g.gridSize; j++){
			if(NULL!=g.theGrid[i][j].getPiece()){
				if(g.theGrid[i][j].getPiece()->getPlayer() == g.player2){	
					out<<"|" << "\033[1;31m"
						 << g.theGrid[i][j].getPiece()->getGamePiece()
						 <<"\033[0m"  << "|";
				}
				if(g.theGrid[i][j].getPiece()->getPlayer() == g.player1){	
					out<<"|"
						 << g.theGrid[i][j].getPiece()->getGamePiece()
					         << "|";
				}


			}
			else{
				out << "| |";
			}
		}
		out << endl;
	}

	return out;
}
/*
valid tile checks to see if the tile is out of the bounds of a normal chess grid
*/
bool Grid::validTile(int r, int c){
        if(r>=0&&r<=7&&c>=0&&c<=7){
                return true;
        }
        return false;
}
/*
end game is passed a winner and lets theat winner know that they won in order to award a point
*/
void Grid::endGame(Player* winner){
	cont = false;
	inGame = false;
	winner->gameWon();
	clearGrid();
	
}

Player* Grid::getCurrentPlayer(){
	return curPlayer;
}
/*
resign ends the game and awards a point to the player that didn't resign
*/
void Grid::resign(){
	if(curPlayer!=player1){
		endGame(player1);
	}
	else{
		endGame(player2);
	}
}

void Grid::continueGames(){
	cont = true;
}
/*
print scoreboard gives the current score after each game
*/
void Grid::printScoreboard(){
        cout << "Final Score:" << endl;
        cout <<"White: " << player1->getWins() << endl;
        cout << "Black: " << player2->getWins() << endl;


}

void Grid::setCurrentPlayer(Player* newCur){
	curPlayer = newCur;
	newCur->isCurPlayer = true;
}

void Grid::printGrid(){
	cout << *this << endl;
}

Tile** Grid::getTheGrid() {
	return theGrid;
}

void Grid::setLastMoved(Piece* piece){
	lastMoved = piece;
}

void Grid::promotePawn(Tile* curTile, char xchange, Player* player){

	if(xchange=='Q'){
		curTile->setPiece( new Queen(player,'Q',curTile->getRow(),curTile->getCol()));
	}
	else if(xchange=='R'){
		curTile->setPiece( new Rook(player,'R',curTile->getRow(),curTile->getCol()));
	}
	else if(xchange=='N'){
		curTile->setPiece( new Knight(player,'N',curTile->getRow(),curTile->getCol()));
	}
	else if(xchange=='B'){
		curTile->setPiece( new Bishop(player,'B',curTile->getRow(),curTile->getCol()));
	}
	else if(xchange=='P'){
		curTile->setPiece( new Pawn(player,'P',curTile->getRow(),curTile->getCol()));
	}	
}

void Grid::startGame(){

string player1Type;
string player2Type;

int level;

/*
start game is how we begin a game. we first receive the types of players that will be playing, and set the neccarasy conditions for those states to occur.
then if the game was already set up, we just let it begin, if it wasn't we call standard setup to create new game with the chess piesces in their normal positions
*/
*in >> player1Type;
if(player1Type=="computer"){
        *in >> level;
        player1->isAI = true;
        player1->aiLevel = level;
}
else{
        player1->isAI = false;
}

*in >> player2Type;

if(player2Type=="computer"){
        *in >> level;
        player2->isAI = true;
        player2->aiLevel = level;
}
else{
        player2->isAI = false;
}



	if(!isSetup){
		stdSetup();	
	}	
	else{
		inGame = true;
	}
}
