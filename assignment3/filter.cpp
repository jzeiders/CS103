#include <iostream>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include "bmplib.h"

using namespace std;

//============================Add function prototypes here======================
void dummy(unsigned char out[][SIZE][RGB],unsigned char in[][SIZE][RGB]);
void convolve(unsigned char out[][SIZE][RGB],unsigned char in[][SIZE][RGB],
	      int N, double kernel[][11]);
void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB]);
void gaussian(double k[][11], int N, double sigma);
void gaussian_filter(unsigned char out[][SIZE][RGB]
  , unsigned char in[][SIZE][RGB], int N, double sigma);
void unsharp(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB],
  int N, double sigma, double alpha);



//============================Do not change code in main()======================

#ifndef AUTOTEST

int main(int argc, char* argv[]){
	//First check argc
	if(argc < 3){
		//we need at least ./filter <input file> <filter name> to continue
		cout << "usage: ./filter <input file> <filter name> <filter parameters>";
		cout << " <output file name>" << endl;
		return -1;
	}
	//then check to see if we can open the input file
	unsigned char input[SIZE][SIZE][RGB];
	unsigned char output[SIZE][SIZE][RGB];
	char* outfile;
	int N;
	double sigma, alpha;
	// read file contents into input array
	int status = readRGBBMP(argv[1], input);
	if(status != 0){
		cout << "unable to open " << argv[1] << " for input." << endl;
		return -1;
	}
	//Input file is good, now look at next argument
	if( strcmp("sobel", argv[2]) == 0){
		sobel(output, input);
		outfile = argv[3];
	}
	else if( strcmp("blur", argv[2]) == 0){
		if(argc < 6)
		{
			cout << "not enough arguments for blur." << endl;
			return -1;
		}
		N = atoi(argv[3]);
		sigma = atof(argv[4]);
		outfile = argv[5];
		gaussian_filter(output, input, N, sigma);
	}
	else if( strcmp("unsharp", argv[2]) == 0){
		if(argc < 7)
		{
			cout << "not enough arguments for unsharp." << endl;
			return -1;
		}
		N = atoi(argv[3]);
		sigma = atof(argv[4]);
		alpha = atof(argv[5]);
		outfile = argv[6];
		unsharp(output, input, N, sigma, alpha);

	}
	else if( strcmp("dummy", argv[2]) == 0){
		//do dummy
		dummy(output, input);
		outfile = argv[3];
	}
	else{
		cout << "unknown filter type." << endl;
		return -1;
	}
	if(writeRGBBMP(outfile, output) != 0){
		cout << "error writing file " << argv[3] << endl;
	}
}

#endif

//=========================End Do not change code in main()=====================


// Creates an identity kernel (dummy kernel) that will simply
// copy input to output image and applies it via convolve()
//
// ** This function is complete and need not be changed.
// Use this as an example of how to create a kernel array, fill it in
// appropriately and then use it in a call to convolve.
void dummy(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
	double k[11][11];
	for (int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			k[i][j] = 0;
		}
	}
	k[1][1] = 1;
	convolve(out, in, 3, k);
}


// Convolves an input image with an NxN kernel to produce the output kernel
// You will need to complete this function by following the
//  instructions in the comments

void convolve(unsigned char out[][SIZE][RGB],
	      unsigned char in[][SIZE][RGB],
	      int N, double kernel[][11])
{

	int padded[SIZE+11][SIZE+11][RGB]; // Use for input image with appropriate
	                                   // padding
	int temp[SIZE][SIZE][RGB];     // Use for the unclamped output pixel
	                               // values then copy from temp to out,

	//first set all of padded to 0 (black)
	for(int i = 0; i < 6; i++) {
		for(int j = 0; j < 6; j++) {
			for(int k = 0; k < 3; k++) {
				padded[i][j][k] = 0; //Top Line
				padded[i+SIZE][j][k] = 0; //Bottom Line
				padded[j][i][k] = 0;//Left Line
				padded[j+SIZE][i][k] = 0; //Right Line
			}
		}
	}
	//now copy input into padding to appropriate locations
	for(int i = 0; i< SIZE; i++) {
		for(int j = 0; j< SIZE; j++) {
			for(int k = 0; k < 3; k++)
				padded[i+5][j+5][k] = in[i][j][k];
		}
	}
	//initialize temp pixels to 0 (black)
	for(int i = 0; i< SIZE; i++) {
		for(int j = 0; j< SIZE; j++) {
			for(int k = 0; k < 3; k++) {
				temp[i][j][k] = 0;
			}
		}
	}
	//now perform convolve (using convolution equation on each pixel of the
	// actual image) placing the results in temp (i.e. unclamped result)
	// for(int i = 0; i < )
	for(int i = 5; i< SIZE+5; i++) {
		for(int j = 5; j< SIZE+5; j++) {
			int val[3] = {0,0,0};
			for(int k = -1*(N)/2; k < (N+1)/2; k++) {
				for(int l= -1*(N)/2; l < (N+1)/2; l++) {
					val[0] += padded[i+k][j+l][0]*kernel[k+N/2][l+N/2];
					val[1] += padded[i+k][j+l][1]*kernel[k+N/2][l+N/2];
					val[2] += padded[i+k][j+l][2]*kernel[k+N/2][l+N/2];
				}
			}
			for(int k = 0; k < 3; k++) {
				temp[i-5][j-5][k] = val[k];
			}
		}
	}
	//now clamp and copy to output
	// You may need to cast to avoid warnings from the compiler:
	// (i.e. out[i][j][k] = (unsigned char) temp[i][j][k];)
	for(int i = 0; i< SIZE; i++) {
		for(int j = 0; j< SIZE; j++) {
			for(int k = 0; k < 3; k++) {
				if(temp[i][j][k] < 0)
					out[i][j][k] = (unsigned char) 0;
				else if (temp[i][j][k] > 255)
					out[i][j][k] =  (unsigned char) 255;
				else {
					out[i][j][k] = (unsigned char)temp[i][j][k];
				}
			}
		}
	}
}

// You will need to complete this function by following the
//  instructions in the comments
void sobel(unsigned char out[][SIZE][RGB], unsigned char in[][SIZE][RGB])
{
	double k[11][11];
	double s_h1[3][3] = { {-1, 0, 1},
			      {-2, 0, 2},
			      {-1, 0, 1} };
	double s_h2[3][3] = { {1, 0, -1},
			      {2, 0, -2},
			      {1, 0, -1} };

	unsigned char h1_sobel[SIZE][SIZE][RGB]; //hold intemediate images
	unsigned char h2_sobel[SIZE][SIZE][RGB];

	for (int i = 0; i < 11; i++) {
		for(int j=0; j < 11; j++) {
			k[i][j] = 0;
		}
	}
	// Copy in 1st 3x3 horizontal sobel kernel (i.e. copy s_h1 into k)
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			k[i][j] = s_h1[i][j];
		}
	}
	// Call convolve to apply horizontal sobel kernel with result in h1_soble
	convolve(h1_sobel,in,3,k);
	// Copy in 2nd 3x3 horizontal sobel kernel (i.e. copy s_h2 into k)
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			k[i][j] = s_h2[i][j];
		}
	}
	// Call convolve to apply horizontal sobel kernel with result in h2_soble
	convolve(h2_sobel,in,3,k);
	// Add the two results (applying clamping) to produce the final output
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			for(int l = 0; l < 3; l++) {
				if(h1_sobel[i][j][l] + h2_sobel[i][j][l] < 0)
					out[i][j][l] = 0;
				if(h1_sobel[i][j][l] + h2_sobel[i][j][l] > 255)
					out[i][j][l] = 255;
				else
					out[i][j][l] = h1_sobel[i][j][l] + h2_sobel[i][j][l];
			}
		}
	}
}

void gaussian(double k[][11], int N, double sigma){
  //Calc Values
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			double val = -1*(pow(abs(i - N/2),2)/(2*pow(sigma,2))
        +(pow(abs(j-N/2),2)/(2*pow(sigma,2))));
			k[i][j] = exp(val);
		}
	}

  //Calc Sum for normalize
	double sum = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			sum+=k[i][j];
		}
	}
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			k[i][j]/=sum;
		}
	}
}
void gaussian_filter(unsigned char out[][SIZE][RGB]
  ,unsigned char in[][SIZE][RGB], int N, double sigma){
  //Create Kernel
  double k[11][11];
	for (int i = 0; i < 11; i++)
	{
		for(int j = 0; j < 11; j++)
		{
			k[i][j] = 0;
		}
	}
	gaussian(k,N,sigma);
	convolve(out, in, N, k);
}
void unsharp(unsigned char out[][SIZE][RGB],unsigned char in[][SIZE][RGB]
  , int N, double sigma, double alpha){
	unsigned char temp[SIZE][SIZE][3]; // Holds Gaussian
	int detail[SIZE][SIZE][3]; // Holds Detail
	gaussian_filter(temp,in,N,sigma); //Generate Gaussian
  //Calulates the Detail
	for(int i =0; i < SIZE; i++) {
		for(int j =0; j < SIZE; j++) {
			for(int k =0; k < 3; k++) {
				int val = (int)(((int)in[i][j][k] - (int)temp[i][j][k])*alpha);
				detail[i][j][k] = val;
			}
		}
	}
  //Calculates the output
	for(int i =0; i < SIZE; i++) {
		for(int j =0; j < SIZE; j++) {
			for(int k =0; k < 3; k++) {
				int val = in[i][j][k] + detail[i][j][k];
				if(val < 0) out[i][j][k] = 0;
				else if(val > 255) out[i][j][k]= 255;
				else out[i][j][k] = (unsigned char)(int) val;
			}
		}
	}
	return;
}
