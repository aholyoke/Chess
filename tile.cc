#include <iostream>
#include "tile.h"
#include "piece.h"

using namespace std;

Tile::Tile(){
	piece = NULL;
}

Tile::~Tile(){
	delete piece;
}

void Tile::clearTile(){
	delete piece;
	piece = NULL;

}

void Tile::setCoords(int r, int c){
	this->r = r;
	this->c = c;
}

void Tile::setPiece(Piece* p){
	delete piece;
	piece = p;
	p->setCoord(r,c);
	
}

void Tile::replacePiece(Piece* p){
	piece = p;
	if(p!=NULL){
		p->setCoord(r,c);
	}
}

void Tile::releasePiece(){
	piece = NULL;
}

Piece* Tile::getPiece(){
	return piece;
}

int Tile::getRow(){
	return r;
}

int Tile::getCol(){
	return c;
}	
