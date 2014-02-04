#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "piece.h"
#include "king.h"
#include "tile.h"
#include "grid.h"

using namespace std;

King::King(Player* p,char gp,int row, int col):Piece(p,gp,row,col){
	p->setKing(this);
}

std::vector<Tile*> King::getMoves(Tile** theGrid){	

	int row = getRow();
	int col = getCol(); 

	int testRow;
	int testCol;

	Player* curPlayer = getPlayer();

	vector<Tile*> moves;

	//set our rows and columns to test
	
	testRow = row-1;
	testCol = col-1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()==NULL){
			//if its null then we need to test if that would cause us to be in check
				if(!inCheck(theGrid,testRow,testCol)){
					//if moving there won't put me in check, add it to the list
					//and there is no king around me
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
		}
		else{
			//if there is a piece there, we can take it.. as long as it's not our colour
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer){
				//check that moving here won't put us in check
				if(!inCheck(theGrid,testRow,testCol)){
					if(!adjacentKing(theGrid,testRow,testCol))
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
			}
		}
	
	testRow = row-1;
	testCol = col;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()==NULL){
			//if its null then we need to test if that would cause us to be in check
				if(!inCheck(theGrid,testRow,testCol)){
					//if moving there won't put me in check, add it to the list
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
		}
		else{
			//if there is a piece there, we can take it.. as long as it's not our colour
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer){
				//check that moving here won't put us in check
				if(!inCheck(theGrid,testRow,testCol)){
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
			}
		}
	}
	
	testRow = row-1;
	testCol = col+1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()==NULL){
			//if its null then we need to test if that would cause us to be in check
				if(!inCheck(theGrid,testRow,testCol)){
					//if moving there won't put me in check, add it to the list
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
		}
		else{
			//if there is a piece there, we can take it.. as long as it's not our colour
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer){
				//check that moving here won't put us in check
				if(!inCheck(theGrid,testRow,testCol)){
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
			}
		}
	}

	testRow = row;
	testCol = col+1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()==NULL){
			//if its null then we need to test if that would cause us to be in check
				if(!inCheck(theGrid,testRow,testCol)){
					//if moving there won't put me in check, add it to the list
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
		}
		else{
			//if there is a piece there, we can take it.. as long as it's not our colour
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer){
				//check that moving here won't put us in check
				if(!inCheck(theGrid,testRow,testCol)){
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
			}
		}
	}
	testRow = row;
	testCol = col-1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()==NULL){
			//if its null then we need to test if that would cause us to be in check
				if(!inCheck(theGrid,testRow,testCol)){
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
		}
		else{
			//if there is a piece there, we can take it.. as long as it's not our colour
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer){
				//check that moving here won't put us in check
				if(!inCheck(theGrid,testRow,testCol)){
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
			}
		}
	}

	testRow = row+1;
	testCol = col-1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()==NULL){
			//if its null then we need to test if that would cause us to be in check
				if(!inCheck(theGrid,testRow,testCol)){
					//if moving there won't put me in check, add it to the list
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
		}
		else{
			//if there is a piece there, we can take it.. as long as it's not our colour
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer){
				//check that moving here won't put us in check
				if(!inCheck(theGrid,testRow,testCol)){
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
			}
		}
	}
	testRow = row+1;
	testCol = col;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()==NULL){
			//if its null then we need to test if that would cause us to be in check
				if(!inCheck(theGrid,testRow,testCol)){
					//if moving there won't put me in check, add it to the list
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
		}
		else{
			//if there is a piece there, we can take it.. as long as it's not our colour
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer){
				//check that moving here won't put us in check
				if(!inCheck(theGrid,testRow,testCol)){
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
			}
		}
	}

	testRow = row+1;
	testCol = col+1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()==NULL){
			//if its null then we need to test if that would cause us to be in check
				if(!inCheck(theGrid,testRow,testCol)){
					//if moving there won't put me in check, add it to the list
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
		}
		else{
			//if there is a piece there, we can take it.. as long as it's not our colour
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer){
				//check that moving here won't put us in check
				if(!inCheck(theGrid,testRow,testCol)){
					if(!adjacentKing(theGrid,testRow,testCol)){
						moves.push_back(&(theGrid[testRow][testCol]));
					}
				}
			}
		}
	}


	/*
		check to see if castling is possible
	*/

	
	//check if first move
	if(isPieceFirstMove()){
		int row = getRow();		
		int lcol = getCol()-2;
		int rcol = getCol()+2;
		//check to see if any rook on the left or right side exists
		if(theGrid[getRow()][0].getPiece()!=NULL){
			Piece* rook = theGrid[getRow()][0].getPiece();
			if(rook->getGamePiece()=='R'){
				if(rook->isPieceFirstMove()){
					if(theGrid[getRow()][1].getPiece()==NULL&&theGrid[getRow()][2].getPiece()==NULL&&theGrid[getRow()][3].getPiece()==NULL){
						if(!inCheck(theGrid,getRow(),getCol()-1)&&!inCheck(theGrid,getRow(),getCol()-2)){
							moves.push_back(&(theGrid[getRow()][lcol]));		
						}	
					}
				}
			}

		}
		if(theGrid[getRow()][7].getPiece()!=NULL){
			Piece* rook = theGrid[getRow()][7].getPiece();
			if(rook->getGamePiece()=='R'){
				if(rook->isPieceFirstMove()){
					if(theGrid[getRow()][6].getPiece()==NULL&&theGrid[getRow()][6].getPiece()==NULL){
						if(!inCheck(theGrid,getRow(),getCol()+1)&&!inCheck(theGrid,getRow(),getCol()+2)){
							moves.push_back(&(theGrid[getRow()][rcol]));		
						}	
					}
				}
			}

		}
		
	}



	return moves;

}

bool King::adjacentKing(Tile** theGrid, int row, int col){
	

	Player* curPlayer = getPlayer();

	int testRow = row-1;
	int testCol = col-1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()!=NULL){
			//if its null then we need not test it
			//return true if there is a king
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer && theGrid[testRow][testCol].getPiece()->getGamePiece()=='K'){
				return true;
			}	
		}
	}

	testRow = row-1;
	testCol = col;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()!=NULL){
			//if its null then we need not test it
			//return true if there is a king
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer && theGrid[testRow][testCol].getPiece()->getGamePiece()=='K'){
				return true;
			}	
		}
	}

	testRow = row-1;
	testCol = col+1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()!=NULL){
			//if its null then we need not test it
			//return true if there is a king
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer && theGrid[testRow][testCol].getPiece()->getGamePiece()=='K'){
				return true;
			}	
		}
	}

	testRow = row;
	testCol = col+1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()!=NULL){
			//if its null then we need not test it
			//return true if there is a king
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer && theGrid[testRow][testCol].getPiece()->getGamePiece()=='K'){
				return true;
			}	
		}
	}

	testRow = row;
	testCol = col-1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()!=NULL){
			//if its null then we need not test it
			//return true if there is a king
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer && theGrid[testRow][testCol].getPiece()->getGamePiece()=='K'){
				return true;
			}	
		}
	}

	testRow = row+1;
	testCol = col-1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()!=NULL){
			//if its null then we need not test it
			//return true if there is a king
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer && theGrid[testRow][testCol].getPiece()->getGamePiece()=='K'){
				return true;
			}	
		}
	}

	testRow = row+1;
	testCol = col;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()!=NULL){
			//if its null then we need not test it
			//return true if there is a king
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer && theGrid[testRow][testCol].getPiece()->getGamePiece()=='K'){
				return true;
			}	
		}
	}

	testRow = row+1;
	testCol = col+1;

	//see if the row,col pair exists	
	if(validTile(testRow,testCol)){
		//if it exists, see if there is anybody on it
		if(theGrid[testRow][testCol].getPiece()!=NULL){
			//if its null then we need not test it
			//return true if there is a king
			if(theGrid[testRow][testCol].getPiece()->getPlayer()!=curPlayer && theGrid[testRow][testCol].getPiece()->getGamePiece()=='K'){
				return true;
			}	
		}
	}


	return false;
}

/*
Two in check functions exist for a simple reason:

The inCheck function that takes just one argument checks the current state of the grid. Is the king in check in that grid
the other one takes a possible movement. in that function the board is reset and an "alternate reality" is created in which we can
check the state of that game to see if the king would be in check given moving to that square


*/


bool King::inCheck(Tile** theGrid){
	Player* curPlayer = getPlayer();
	int row = getRow();
	int col = getCol();


	//check adjacent king case
	if(adjacentKing(theGrid,row,col)){
		return true;
	}


	for(int i = 0; i<8; i++){
		for(int j =0; j<8; j++){
			if(theGrid[i][j].getPiece()!=NULL){
				if(theGrid[i][j].getPiece()->getPlayer()!=curPlayer){
					std::vector<Tile*> moves;
					//make sure we don't check for king or we'll get an infinite loop
					//the case of being next to a king will be covered in get moves
					if(theGrid[i][j].getPiece()->getGamePiece()!='K'){		
						moves = theGrid[i][j].getPiece()->getMoves(theGrid);
						for(int m = 0; m<moves.size(); m++){
							if(moves[m]->getRow()==row && moves[m]->getCol()==col){
								return true;
							}		
						}
					}
				}
			}
		}
	}

	return false;		
}


bool King::inCheck(Tile** theGrid,int row,int col){

	Player* curPlayer = getPlayer();
	/*
		temporarily move kind to new spot and see if he's in check there
	*/

	bool ret = false;
	
	Piece* curPiece = theGrid[row][col].getPiece();

	int curRow = getRow();
	int curCol = getCol();


	
	theGrid[curRow][curCol].releasePiece();

	

	theGrid[row][col].replacePiece(this);		


	ret = inCheck(theGrid);	

		

	/*
		reset pieces
	*/

		
	theGrid[row][col].replacePiece(curPiece);
	
	theGrid[curRow][curCol].replacePiece(this);
	

	return ret;		
}

bool King::inCheckmate(Tile** theGrid){

	vector<Tile*> moves = getMoves(theGrid);

	/*
		make sure the king is in check
	*/	

	if(!(inCheck(theGrid))){
		return false;
	}
       // King is in check
	
	if(moves.size()!=0){
		return false;	
	}
	//King has no moves
	
	/*
	list all the players who are putting the king in check
	*/
	
	vector<Piece*> predators;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j<8; j++){
			Piece* piece;
			if(theGrid[i][j].getPiece()!=NULL){
				piece = theGrid[i][j].getPiece();
				if(piece->getPlayer()!=getPlayer()){
					vector<Tile*> pieceMoves = piece->getMoves(theGrid);
					for(int m = 0; m<pieceMoves.size(); m++){
						if((pieceMoves[m]->getRow()==getRow())&&(pieceMoves[m]->getCol()==getCol())){
							predators.push_back(piece);	
						}
					}
				}
			}
		}
	}
	if(predators.size()>1){
		return true;
	} 
	else{
		vector<Tile*> predMoves = predators[0]->getMoves(theGrid);
		for(int i = 0; i < 8; i++){
			for(int j = 0; j<8; j++){
				Piece* piece;
				if(theGrid[i][j].getPiece()!=NULL){
					piece = theGrid[i][j].getPiece(); // Candidate sacrifice or defender of king
					if(piece->getPlayer()==getPlayer()){
						vector<Tile*> pieceMoves = piece->getMoves(theGrid);
						for(int m = 0; m<pieceMoves.size(); m++){
							/*check if one of our players can take the predator*/
							if((pieceMoves[m]->getRow()==predators[0]->getRow())&&(pieceMoves[m]->getCol()==predators[0]->getCol())){
								return false;
							}
							/*check to see if they can just get in the way of the check*/
							int kingRow = getRow();
							int kingCol = getCol();
	
							int predRow = predators[0]->getRow();
							int predCol = predators[0]->getCol();
		
							int pieceRow = pieceMoves[m]->getRow();
							int pieceCol = pieceMoves[m]->getCol();
	
/*
this next part checks all the cases to see if there is possibly any move that would allow a piece to move infront of the predator in such a way that the king wouldn't be in check anymore
*/

								if(kingRow == predRow){
									if(pieceRow == kingRow){	
										if(predCol > kingCol){
											if((pieceCol<predCol)&&(pieceCol>kingCol)){
												return false;	
											}
										}
									}
									if(pieceRow == kingRow){	
										if(predCol < kingCol){
											if((pieceCol>predCol)&&(pieceCol<kingCol)){
												return false;	
											}
										}
									}
					
								}
                                                                if(kingCol == predCol){
                                                                        if(pieceCol == kingCol){
                                                                                if(predRow > kingRow){
                                                                                        if((pieceRow<predRow)&&(pieceRow>kingRow)){
                                                                                                return false;
                                                                                        }
                                                                                }
                                                                        }
                                                                        if(pieceCol == kingCol){
                                                                                if(predRow < kingRow){
                                                                                        if((pieceRow>predRow)&&(pieceRow>kingRow)){
                                                                                                return false;
                                                                                        }
                                                                                }
                                                                        }


                                                                }
								
								if((kingRow!=predRow)&&(kingCol!=predCol)){
									if((predCol>kingCol)&&(predRow>kingRow)){
										if((pieceCol>kingCol)&&(pieceRow>kingRow)){
											return false;
										}
									}										
									if((predCol<kingCol)&&(predRow<kingRow)){
										if((pieceCol<kingCol)&&(pieceRow<kingRow)){
											return false;
										}
									}										
									if((predCol>kingCol)&&(predRow<kingRow)){
										if((pieceCol>kingCol)&&(pieceRow<kingRow)){
											return false;
										}
									}										
									if((predCol<kingCol)&&(predRow>kingRow)){
										if((pieceCol<kingCol)&&(pieceRow>kingRow)){
											return false;
										}
									}										
								}

							
						}	
					}	
				}
			}
		}
	}
	return true;

}

bool King::inStalemate(Tile** theGrid){	

	vector<Tile*> kmoves = getMoves(theGrid);
	if(kmoves.size()!=0){
		return false;
	}
//the king has no moves	
	if(inCheck(theGrid)){
		return false;
	}
//the king is not in check

	for(int i = 0; i<8; i++){
		for(int j=0; j<8; j++){
			if(theGrid[i][j].getPiece()!=NULL){
				Piece* piece = theGrid[i][j].getPiece();
				if(piece->getPlayer()==getPlayer()){
					if(piece->getGamePiece()!='K'){
						vector<Tile*> pieceMoves = piece->getMoves(theGrid);
						if(pieceMoves.size()!=0){
							return false;
						}
					}
				}
			}
		}
	}	

//no other piece on the board has any moves and all other conditions satisfied so it must be stalemate
	return true;

}
	
