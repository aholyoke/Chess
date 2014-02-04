#ifndef _DISPLAY__H_
#define _DISPLAY__H_
#include <iostream>
#include "window-v2.h"
#include "observer.h"
#include "grid.h"


class Grid;


class GraphicsDisplay: public Observer {
	Grid *g;
	Xwindow *w;
	public:
	  GraphicsDisplay(Xwindow *w, Grid*);
	  ~GraphicsDisplay();
	  void drawScoreBoardStatic();
	  void drawScoreBoard();
	  void update2();
	  void update(); //ask grid for getLastMove(), update screen accordingly
};

#endif
