#include "subject.h"
#include "display.h"
using namespace std;


void Subject::attach(GraphicsDisplay *o) {
	this->o = o;
}

void Subject::notify(bool singleMove) {
	if (singleMove)
		o->update();
	else
		o->update2();
}
