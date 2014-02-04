#include <iostream>
#include <string>
#include <vector>

#include "piece.h"
#include "knight.h"
#include "tile.h"

using namespace std;

Knight::Knight(Player* p,char gp,int row, int col):Piece(p,gp,row,col){}

std::vector<Tile*> Knight::getMoves(Tile** theGrid){	
        vector<Tile*> moves;
        Piece* piece = this; 
        Player* curPlayer = piece->getPlayer();
	int direction = curPlayer->getDirection();
	int r = getRow();
	int c = getCol();
		//*(x+-2,y+-1) (x+-1,y+-2)
		//check 8 distinct moves
		if(validTile(r+2,c+1)){
			if(theGrid[r+2][c+1].getPiece()==NULL){
				moves.push_back(&(theGrid[r+2][c+1]));	
			}		
			else if(theGrid[r+2][c+1].getPiece()->getPlayer()!=curPlayer){
				moves.push_back(&(theGrid[r+2][c+1]));	
			}		
		}
		if(validTile(r+2,c-1)){
			if(theGrid[r+2][c-1].getPiece()==NULL){
				moves.push_back(&(theGrid[r+2][c-1]));	
			}		
			else if(theGrid[r+2][c-1].getPiece()->getPlayer()!=curPlayer){
				moves.push_back(&(theGrid[r+2][c-1]));	
			}		
		}
		if(validTile(r-2,c+1)){
			if(theGrid[r-2][c+1].getPiece()==NULL){
				moves.push_back(&(theGrid[r-2][c+1]));	
			}		
			else if(theGrid[r-2][c+1].getPiece()->getPlayer()!=curPlayer){
				moves.push_back(&(theGrid[r-2][c+1]));	
			}		
		}
		if(validTile(r-2,c-1)){
			if(theGrid[r-2][c-1].getPiece()==NULL){
				moves.push_back(&(theGrid[r-2][c-1]));	
			}		
			else if(theGrid[r-2][c-1].getPiece()->getPlayer()!=curPlayer){
				moves.push_back(&(theGrid[r-2][c-1]));	
			}		
		}


		if(validTile(r+1,c+2)){
			if(theGrid[r+1][c+2].getPiece()==NULL){
				moves.push_back(&(theGrid[r+1][c+2]));	
			}		
			else if(theGrid[r+1][c+2].getPiece()->getPlayer()!=curPlayer){
				moves.push_back(&(theGrid[r+1][c+2]));	
			}		
		}
		if(validTile(r+1,c-2)){
			if(theGrid[r+1][c-2].getPiece()==NULL){
				moves.push_back(&(theGrid[r+1][c-2]));	
			}		
			else if(theGrid[r+1][c-2].getPiece()->getPlayer()!=curPlayer){
				moves.push_back(&(theGrid[r+1][c-2]));	
			}		
		}
		if(validTile(r-1,c+2)){
			if(theGrid[r-1][c+2].getPiece()==NULL){
				moves.push_back(&(theGrid[r-1][c+2]));	
			}		
			else if(theGrid[r-1][c+2].getPiece()->getPlayer()!=curPlayer){
				moves.push_back(&(theGrid[r-1][c+2]));	
			}		
		}
		if(validTile(r-1,c-2)){
			if(theGrid[r-1][c-2].getPiece()==NULL){
				moves.push_back(&(theGrid[r-1][c-2]));	
			}		
			else if(theGrid[r-1][c-2].getPiece()->getPlayer()!=curPlayer){
				moves.push_back(&(theGrid[r-1][c-2]));	
			}		
		}

/*
make sure that none of these moves will put the king in danger
*/	
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
