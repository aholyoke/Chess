#include <iostream>
#include <string>
#include <vector>

#include "piece.h"
#include "bishop.h"
#include "tile.h"

using namespace std;

Bishop::Bishop(Player* p,char gp,int row, int col):Piece(p,gp,row,col){}

std::vector<Tile*> Bishop::getMoves(Tile** theGrid){	
	/*
	Initialize some standard variables that will be used throughout the get moves functions
	*/
        vector<Tile*> moves;
        Piece* piece = this; 
        Player* curPlayer = piece->getPlayer();
	// a direction will identify what direction up or down is on a board
	int direction = curPlayer->getDirection();
	int r = getRow();
	int c = getCol();
		//forward
		bool checkLeft = true;
		bool checkLeftDown = true;
		bool checkRight = true;
		bool checkRightDown = true;
		/*
		the for loop is used in lieu of writing down all of the possible places a bishop could go given a board. We loop through using the iterator to add or subtract to the diagonal
		if we reach an invalid tile, then we stop checking in that direction
		*/	
		for(int i = 1; i<8; i++){
			if(checkLeft){
				//valid tile?
				if(validTile(r+(i*direction),c-i)){
					//check if there is somebody on it
					if(theGrid[r+(i*direction)][c-i].getPiece()==NULL){
						//if there isn't then that move is valid
						moves.push_back(&(theGrid[r+(i*direction)][c-i]));	
					}
					else{
						//check if its your own oppenent on the grid or not
						if(theGrid[r+(i*direction)][c-i].getPiece()->getPlayer()!=curPlayer){
							moves.push_back(&(theGrid[r+(i*direction)][c-i]));	
						}
					
						//stop checking left	
						checkLeft = false;	
					}		
				}
				else{
					checkLeft=false;
				}		
			}	
			if(checkLeftDown){
				//valid tile?
				if(validTile(r-(i*direction),c-i)){
					//check if there is somebody on it
					if(theGrid[r-(i*direction)][c-i].getPiece()==NULL){
						//if there isn't then that move is valid
						moves.push_back(&(theGrid[r-(i*direction)][c-i]));	
					}
					else{
						//check if its your own oppenent on the grid or not
						if(theGrid[r-(i*direction)][c-i].getPiece()->getPlayer()!=curPlayer){
							moves.push_back(&(theGrid[r-(i*direction)][c-i]));	
						}
					
						//stop checking left down
						checkLeftDown = false;	
					}		
				}
				else{
					checkLeftDown=false;
				}		
			}	
			if(checkRight){
				//valid tile?
				if(validTile(r+(i*direction),c+i)){
					//check if there is somebody on it
					if(theGrid[r+(i*direction)][c+i].getPiece()==NULL){
						//if there isn't then that move is valid
						moves.push_back(&(theGrid[r+(i*direction)][c+i]));	
					}
					else{
						//check if its your own oppenent on the grid or not
						if(theGrid[r+(i*direction)][c+i].getPiece()->getPlayer()!=curPlayer){
							moves.push_back(&(theGrid[r+(i*direction)][c+i]));	
						}
					
						//stop checking right up
						checkRight = false;	
					}		
				}
				else{
					checkRight=false;
				}		
			}	
			if(checkRightDown){
				//valid tile?
				if(validTile(r-(i*direction),c+i)){
					//check if there is somebody on it
					if(theGrid[r-(i*direction)][c+i].getPiece()==NULL){
						//if there isn't then that move is valid
						moves.push_back(&(theGrid[r-(i*direction)][c+i]));	
					}
					else{
						//check if its your own oppenent on the grid or not
						if(theGrid[r-(i*direction)][c+i].getPiece()->getPlayer()!=curPlayer){
							moves.push_back(&(theGrid[r-(i*direction)][c+i]));	
						}
					
						//stop checking right down
						checkRightDown = false;	
					}		
				}
				else{
					checkRightDown=false;
				}		
			}	
	
		}

		//one last check is done that removes any moves that may endanger the life of the queen	

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
