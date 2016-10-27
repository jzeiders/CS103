#include "turtle.h"
#include "draw.h"
#include <math.h>

Turtle::Turtle(double x0, double y0, double dir0){
	x = x0;
	y= y0;
	dir = dir0;
  isOn = true;
  curColor = Color(0,0,0);
};
void Turtle::move(double dist){
  double x2 = x + cos(dir/180 * M_PI);
  double y2 = y + sin(dir/180 * M_PI);
  draw.line(x,y,x2,y2);
}
void Turn::turn(double angle){
  dir += angle;
}
