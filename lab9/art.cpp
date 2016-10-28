#include "draw.h"
#include "turtle.h"
#include <stdlib.h>
#include <time.h>

int main(){
	draw::setpenwidth(10); // thick lines
	draw::setrange(-100, 100);
	srand(time(0));
	Turtle raphael(0, 0, 0);
	int dist = 0;
	for(int i = 0; i < 20; i++) {
		raphael.move(dist);
		raphael.turn(90);
		raphael.setColor(Color(rand()%255,rand()%255,rand()%255));
		dist+=10;
	}
	return 0;
}
