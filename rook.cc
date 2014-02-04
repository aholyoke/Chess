#include <iostream>
#include <string>
#include <vector>

#include "piece.h"
#include "rook.h"
#include "tile.h"

using namespace std;

Rook::Rook(Player* p,char gp,int row, int col):Piece(p,gp,row,col){}



std::vector<Tile*> Rook::getMoves(Tile** theGrid){	
        vector<Tile*> moves;
        Piece* piece = this; 
        Player* curPlayer = piece->getPlayer();
	int direction = curPlayer->getDirection();
	int r = getRow();
	int c = getCol();
		//forward
		bool checkMid = true;
		bool checkMidDown = true;
		bool checkRightCol = true;
		bool checkLeftCol = true;
		
		for(int i = 1; i<8; i++){
			if(checkMid){
				//valid tile?
				if(validTile(r+(i*direction),c)){
					//check if there is somebody on it
					if(theGrid[r+(i*direction)][c].getPiece()==NULL){
						//if there isn't then that move is valid
						moves.push_back(&(theGrid[r+(i*direction)][c]));	
					}
					else{
						//check if its your own oppenent on the grid or not
						if(theGrid[r+(i*direction)][c].getPiece()->getPlayer()!=curPlayer){
							moves.push_back(&(theGrid[r+(i*direction)][c]));	
						}
					
						//stop checking left	
						checkMid = false;	
					}		
				}
				else{
					checkMid=false;
				}		
			}	
			if(checkMidDown){
				//valid tile?
				if(validTile(r-(i*direction),c)){
					//check if there is somebody on it
					if(theGrid[r-(i*direction)][c].getPiece()==NULL){
						//if there isn't then that move is valid
						moves.push_back(&(theGrid[r-(i*direction)][c]));	
					}
					else{
						//check if its your own oppenent on the grid or not
						if(theGrid[r-(i*direction)][c].getPiece()->getPlayer()!=curPlayer){
							moves.push_back(&(theGrid[r-(i*direction)][c]));	
						}
					
						//stop checking left	
						checkMidDown = false;	
					}		
				}
				else{
					checkMidDown=false;

				}		
			}	
			if(checkRightCol){
				//valid tile?
				if(validTile(r,c+i)){
					//check if there is somebody on it
					if(theGrid[r][c+i].getPiece()==NULL){
						//if there isn't then that move is valid
						moves.push_back(&(theGrid[r][c+i]));	
					}
					else{
						//check if its your own oppenent on the grid or not
						if(theGrid[r][c+i].getPiece()->getPlayer()!=curPlayer){
							moves.push_back(&(theGrid[r][c+i]));	
						}
					
						//stop checking left	
						checkRightCol = false;	
					}		
				}
				else{
					checkRightCol=false;

				}		
			}
			if(checkLeftCol){
				//valid tile?
				if(validTile(r,c-i)){
					//check if there is somebody on it
					if(theGrid[r][c-i].getPiece()==NULL){
						//if there isn't then that move is valid
						moves.push_back(&(theGrid[r][c-i]));	
					}
					else{
						//check if its your own oppenent on the grid or not
						if(theGrid[r][c-i].getPiece()->getPlayer()!=curPlayer){
							moves.push_back(&(theGrid[r][c-i]));	
						}
					
						//stop checking left	
						checkLeftCol = false;	
					}		
				}
				else{
					checkLeftCol=false;

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
