#include "draw.h"

#define Turtle_H

class Turtle {
  
private:
  Color color;
  double x;
  double y;
  double dir;
  bool isOn;
public:
  Turtle(double x0, double y0, double dir0);
  void move(double dist);
  void turn(double angle);
  void setColor(Color newColor);
  void off();
  void on();
};

