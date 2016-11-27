#include "draw.h"
#include "turtle.h"
#include <stdlib.h>
#include <time.h>

int main(){
	draw::setpenwidth(10); // thick lines
	draw::setrange(-100, 100);
	srand(time(0));
	Turtle raphael(0, 0, 0);
	Turtle a (0,0,0);
	Turtle b(0,0,0);
	Turtle c(0,0,0);
	b.move(10);
	c.move(20);
	int dist = 0;
	for(int i = 0; i < 20; i++) {
		raphael.move(dist);
		a.move(-dist);
		draw::show(100);
		raphael.turn(90);
		raphael.setColor(Color(rand()%255,rand()%255,rand()%255));
		dist+=10;
	}
	return 0;
}
