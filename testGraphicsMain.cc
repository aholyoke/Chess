#include <string>
#include <iostream>
#include <unistd.h>
#include "display.h"
#include "window-v2.h"

using namespace std;


int main() {
	Xwindow* w = new Xwindow(800, 800);
	GraphicsDisplay* d = new GraphicsDisplay(w);
	string s;
	d->update();
	cin >> s;
	delete d;
}
