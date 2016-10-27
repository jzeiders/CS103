#include <iostream>
#include <cmath>
#include "bmplib.h"

using namespace std;

// global variable. bad style but ok for this lab
unsigned char image[SIZE][SIZE];

// Fill in this function:
void draw_rectangle(int top, int left, int height, int width) {
	for(int i = 0; i < width; i++) {
		if(left + i <SIZE && left +i >=0 && top >= 0 && top <SIZE) {
			image[top][left+i]= 0;
		}
		if(left + i <SIZE && left +i >=0 && top+height >= 0 && top+height <SIZE) {
			image[top+height][left+i] = 0;
		}
	}
	for(int i = 0; i < height; i++) {
		if(top+i >=0 && top+i <SIZE && left < SIZE && left >=0) {
			image[top+i][left]= 0;
		}
		if(top+i >=0 && top+i <SIZE && left+width >=0 && left+width <SIZE) {
			image[top+i][left+width] = 0;
		}
	}
}

// Fill in this function:
void draw_ellipse(int cy, int cx, int height, int width) {
	for(double i = 0; i < 2*M_PI; i+=0.01) {
    if((int)(cy + height/2 * sin(i)) < SIZE && (int)(cy + height/2 * sin(i)) > 0 && (int)(cx + width/2 *cos(i)) > 0 && (int)(cx + width/2 *cos(i)) < SIZE )
		image[(int)(cy + height/2 * sin(i))][(int)(cx + width/2 *cos(i))] = 0;
	}
}

int main() {
	int choice = -1;
	int one,two,three,four;
	// initialize the image to all white pixels
	for (int i=0; i < SIZE; i++) {
		for (int j=0; j < SIZE; j++) {
			image[i][j] = 255;
		}
	}
	do { // Primary Work Code
		cout << "To draw a rectangle, enter: 0 top left height width"<< endl;
		cout << "To draw an ellipse, enter: 1 cy cx height width " << endl;
		cout << "To save your drawing as 'output.bmp' and quit, enter: 2";
		cin >> choice;
		if(choice == 0) {
			cin >> one>> two>> three>> four;
			draw_rectangle(one,two,three,four);
		}
		if(choice == 1) {
			cin >> one>> two>> three>> four;
			draw_ellipse(one,two,three,four);
		}
		// showGSBMP(image); //Not used outside of VM;
	}
	while(choice!=2);
	// Write the resulting image to the .bmp file
	writeGSBMP("output.bmp", image);

	return 0;
}
