#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  int r,g,b;
  double w,c,y,m,k;   // Lots of variables
	cin >> r;
	cin >> g;
	cin >> b;
	w = max(r/255,max(g/255,b/255));
	c = (w - r/255)/w;
	y = (w - g/255)/w;
	m = (w - b/255)/w;
	k = 1- w;
	cout << endl << "cyan:" << c << endl;
	cout << "yellow:" << y << endl;
	cout << "magenta:" << m << endl;
	cout << "black:" << k << endl;
	return 0;
}
