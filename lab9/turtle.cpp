#include "turtle.h"
#include "draw.h"
#include <math.h>

Turtle::Turtle(double x0, double y0, double dir0){
	x= x0;
	y= y0;
	dir = dir0;
  isOn = true;
  color = draw::BLACK;
};
void Turtle::move(double dist){
  double x2 = x + cos(dir/180 * M_PI)*dist;
  double y2 = y + sin(dir/180 * M_PI)*dist;
  if(isOn){
  	draw::setcolor(color);
  	draw::line(x,y,x2,y2);
  }
  x = x2;
  y = y2;
}
void Turtle::turn(double angle){
  dir += angle;
}
void Turtle::setColor(Color newColor){
	color = newColor;
}
void Turtle::on(){
	isOn = true;
}
void Turtle::off(){
	isOn = false;
}