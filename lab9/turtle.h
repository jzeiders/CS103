#indef Turtle_H
#define Turtle_H

class Turtle {
  struct Color {
    int red;
    int green;
    int blue
  }
private:
  double x;
  double y;
  double dir;
  bool isOn;
  Color curColor;
public:
  Turtle(double x0, double y0, double dir0);
  void move(double dist);
  void turn(double angle);
};

#endif
