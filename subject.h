#ifndef _SUBJECT__H_
#define _SUBJECT__H_

class GraphicsDisplay;

class Subject {
	GraphicsDisplay *o;
	public:
	  void attach(GraphicsDisplay*);
	  void notify(bool);
};

#endif

