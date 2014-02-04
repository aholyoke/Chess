#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include "piece.h"
#include "pawn.h"
#include "tile.h"

using namespace std;

Pawn::Pawn(Player* p,char gp,int row, int col):Piece(p,gp,row,col){
}



std::vector<Tile*> Pawn::getMoves(Tile** theGrid){	
        vector<Tile*> moves;
        Piece* piece = this; 
        Player* curPlayer = piece->getPlayer();
	int direction = curPlayer->getDirection();
	int r = getRow();
	int c = getCol();
        //get all POSSIBLE MOVES
        //moves for a pawn;
        if(piece->getGamePiece()=='P'){
                /*
                1. Standard One Square Forward
                2. Attack Diagonally
                3. En Passant
                4. First Move 2 Squares         
                5. can stay in the same place
                */
                //5.
                //1.
                if(validTile((r+(1*direction)),c)){
                        if(theGrid[r+(1*direction)][c].getPiece()==NULL){
                                moves.push_back(&(theGrid[r+(1*direction)][c]));
                        }
                }
                //2.
                if(validTile((r+(1*direction)),c-1)){
                        if(theGrid[r+(1*direction)][c-1].getPiece()!=NULL){
                                if(theGrid[r+(1*direction)][c-1].getPiece()->getPlayer()!=curPlayer){
                                        moves.push_back(&(theGrid[r+(1*direction)][c-1]));
                                }
                        }
                }
                if(validTile((r+(1*direction)),c+1)){
                        if(theGrid[r+(1*direction)][c+1].getPiece()!=NULL){
                                if(theGrid[r+(1*direction)][c+1].getPiece()->getPlayer()!=curPlayer){
                                        moves.push_back(&(theGrid[r+(1*direction)][c+1]));
                                }
                        }
                }

		//two spaces forward on the first move

		if(isFirstMove()){
			if(theGrid[getRow()+(direction*1)][getCol()].getPiece()==NULL&&theGrid[getRow()+(direction*2)][getCol()].getPiece()==NULL){
				moves.push_back(&(theGrid[r+2*direction][c]));
			}
		}
	
        }
	//en passsant
		if(r==3&&direction==-1){
			if(validTile(r,c-1)){
				if(theGrid[r][c-1].getPiece()!=NULL){
					if(theGrid[r][c-1].getPiece()->getPlayer()!=getPlayer()){
						if(theGrid[r][c-1].getPiece()->getPlayer()->getLastMove().cur!=NULL){
							int lmRow = theGrid[r][c-1].getPiece()->getPlayer()->getLastMove().cur->getRow();
							int lmCol = theGrid[r][c-1].getPiece()->getPlayer()->getLastMove().cur->getCol();
							if((lmRow==r)&&(lmCol==c-1)){
								if(theGrid[r-1][c-1].getPiece()==NULL&&theGrid[r][c-1].getPiece()->getGamePiece()=='P'){
									moves.push_back(&(theGrid[r-1][c-1]));
								}
							}else{
								//cerr << "R: " << lmRow << " C: " << lmCol << endl;
							}
						}		
					}
				}					
			}
			if(validTile(r,c+1)){
				if(theGrid[r][c+1].getPiece()!=NULL){
					if(theGrid[r][c+1].getPiece()->getPlayer()!=getPlayer()){
						if(theGrid[r][c+1].getPiece()->getPlayer()->getLastMove().cur!=NULL){
							int lmRow = theGrid[r][c+1].getPiece()->getPlayer()->getLastMove().cur->getRow();
							int lmCol = theGrid[r][c+1].getPiece()->getPlayer()->getLastMove().cur->getCol();
							if((lmRow==r)&&(lmCol==c+1)){
								if(theGrid[r-1][c+1].getPiece()==NULL&&theGrid[r][c+1].getPiece()->getGamePiece()=='P'){
									moves.push_back(&(theGrid[r-1][c+1]));
								}
							}else{
								//cout << "R: " << lmRow << " C: " << lmCol << endl;
							}
						}		
					}
				}					
			}	
		}

		if(r==4&&direction==1){			
			if(validTile(r,c-1)){
				if(theGrid[r][c-1].getPiece()!=NULL){	
					if(theGrid[r][c-1].getPiece()->getGamePiece()=='P'){
					if(theGrid[r][c-1].getPiece()->getPlayer()!=getPlayer()){
						if(theGrid[r][c-1].getPiece()->getPlayer()->getLastMove().cur!=NULL){
							int lmRow = theGrid[r][c-1].getPiece()->getPlayer()->getLastMove().cur->getRow();			
							
							int lmCol = theGrid[r][c-1].getPiece()->getPlayer()->getLastMove().cur->getCol();
							if((lmRow==r)&&(lmCol==c-1)){
								if(theGrid[r+1][c-1].getPiece()==NULL&&theGrid[r][c-1].getPiece()->getGamePiece()=='P'){
									moves.push_back(&(theGrid[r+1][c-1]));
								}
							}else{
							}
						}		
					}
					}
				}					
			}
			if(validTile(r,c+1)){
				if(theGrid[r][c+1].getPiece()!=NULL){
					if(theGrid[r][c+1].getPiece()->getPlayer()!=getPlayer()){
						if(theGrid[r][c+1].getPiece()->getPlayer()->getLastMove().cur!=NULL){
							int lmRow = theGrid[r][c+1].getPiece()->getPlayer()->getLastMove().cur->getRow();
							int lmCol = theGrid[r][c+1].getPiece()->getPlayer()->getLastMove().cur->getCol();
							if((lmRow==r)&&(lmCol==c+1)){
								if(theGrid[r+1][c+1].getPiece()==NULL&&theGrid[r][c+1].getPiece()->getGamePiece()=='P'){
									moves.push_back(&(theGrid[r+1][c+1]));
								}
							}else{
							}
						}		
					}
				}					
			}
	}

                if(getPlayer()->isCurPlayer){
                vector<Tile*>::iterator iter = moves.begin();
                while(iter != moves.end()){
                        int trow = (*iter)->getRow();
                        int tcol = (*iter)->getCol();
                        if(endangerKing(theGrid,trow,tcol)){
                                iter = moves.erase(iter);
                        }
                        else{
                                ++iter;
                        }
                }
                }

	return moves;


}

/*
for en passant we check to see if the pawn is in its starting position
*/
bool Pawn::isFirstMove(){
	if(getPlayer()->getDirection() == -1){
		if(getRow()==6){
			return true;
		}
	}
	else{
		if(getRow()==1){
			return true;
		}
	}
}

