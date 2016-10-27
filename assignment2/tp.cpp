/*********************************************************
* File name : tp.cpp
* Author    : John Zeiders
* Date      :
* Purpose   : Simulates the toilet-paper problem
* Notes     : None
*********************************************************/

#include <iostream>   // Basic I/O => cin, cout, etc.
#include <cstdlib>    // Other helpful functions => rand(), RANDMAX

using namespace std;
// Prototype/declaration of a function that returns a
// uniform random number between [0,1]
double rand_uniform();

// Prototype/declaration of a function that will perform a single
// simulation of two rolls of paper and users
// Returns the number of squares left on the non-empty roll
int single_sim(int N, double p);

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int N;          // initial number of squares on each roll

	double p;       // probability of a big-chooser

	int sims;       // number of trials for our simulation
	cin >> N >> p >> sims;
  cout << N << p << sims;
	// Add your code here
  double avg =0;
  for(int i =0 ; i < sims; i++){
    avg+=(double)single_sim(N,p);
  }
  avg/=(double)sims;
  cout << "Average: " << avg;


	// Be sure you produce an output of the form:
	//    Average: 1.2314
	// where the number is the correct average
	return 0;
}

// return the number of squares on the non-empty roll
//  for this simulation of the problem
int single_sim(int N, double p)
{
	int n1 = N; // Close Roll
	int n2 = N; // Far Rol
	while(n1 > 0 && n2 > 0) {
		if(rand_uniform() < p) {
			if(n1 >= n2) {
				n1--;
			}
			else {
				n2--;
			}
		}
		else {
			if(n1 >= n2) {
				n2--;
			}
			else {
				n1--;
			}
		}
	}
  return n1 == 0 ? n2 : n1;
}

// returns a uniformly-distributed number in the range [0,1]
//  The caller can use the return result to then determine
//  if it should treat it as a big- or little-chooser by
//  also using the p parameter.  This code only needs to
//  produce a random number in the range [0,1]
double rand_uniform()
{
	return rand()/(double)RAND_MAX;
}
