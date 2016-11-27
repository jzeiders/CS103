#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
// You may add #includes in this program

using namespace std;

// Stores a state's name and how many
// electoral votes that state has
struct StateElectoralInfo {
	string state;
	int elecVotes;
};

// Complete the following function
//
// This function should search/find the target stateName
//  in an array of StateElectoralInfo structs
//  and return that state's electoral vote number
//
//  state_info  input array of filled in StateElectoralInfo structs
//  len         is the length/size of the state_info array
//  stateName   is the state name you need to find
//
// Return the electoral votes the target state has
// Return -1 if the stateName does not appear in the array

int getStateElecVotes(StateElectoralInfo state_info[], int len, string stateName)
{
	// Add your code here
	// Added my code down here.
	for(int i = 0; i < len; i++) {
		if(state_info[i].state.compare(stateName) == 0) {
			return state_info[i].elecVotes;
		}
	}
	return -1; // Return that neg if state no exist
}

//**************************************
// Do not change these 2 lines and don't
// add any lines between them and main()
//**************************************
#ifndef AUTO_TEST
#define AUTO_TEST
int main(int argc, char* argv[])
{
	//*********************************************************
	// Use these declarations to store the appropriate answers.
	// Our 'couts' at the bottom expect these variables to
	//  be set correctly by the end of your program.
	//*********************************************************
	string candidate1; // Store candidate 1 last name here
	string candidate2; // Store candidate 2 last name here

	int c1_electoral_votes=0; // Total (all states) candidate 1 electoral  votes
	int c2_electoral_votes=0; // Total (all states) candidate 1 electoral  votes

	int c1_total_votes=0; // Total candidate 1 popular votes from all states
	int c2_total_votes=0; // Total candidate 2 popular votes from all states

	string best_c1_state; // State with highest percentage win for candidate1
	string best_c2_state; // State with highest percentage win for candidate2

	double best_c1_percent = 0.0; // Store highest percentage of vote candidate1
	                              //  got in a state
	double best_c2_percent = 0.0; // Store highest percentage of vote candidate2
	                              //  got in a state

	// cout this message if the program fails to open the electoral file
	const string elecFileErrorMsg = "Electoral college file not found.";
	// cout this message if the program fails to open the voter file
	const string voterFileErrorMsg = "Voter totals file not found.";

	if(argc < 3) {
		cout << "Not enough command line arguments." << endl;
		cout << "Usage: ./election <electoral college data file> <voting data file>"
		     << endl;
		return -1;
	}

	//*********************************************************
	// Write your code below to perform the overall task.
	// Be sure to follow requirements.  Make sure your code
	// produces the appropriate values of the variables we
	// declared above so that the code at the bottom will print
	// out the answers in the correct format.
	//*********************************************************

	ifstream elecFile (argv[1]); // DECLARE THE ELECTORAL FILE
	ifstream voterFile (argv[2]); //LET THERE BE A VOTER FILE

	if(elecFile.fail()) {
		cout << elecFileErrorMsg; //throw error no electoral file
    return 1;
  }
	if(voterFile.fail()) {
		cout << voterFileErrorMsg; // throw error no voter file
    return 1;
  }

	voterFile >> candidate1; // STORE THAT CANDIDATE
	voterFile >> candidate2; // STORE THAT OTHER CANDIDATE

	int states; //Really means #of states, prbly should have called it lenStates..
	elecFile >> states; // Store that #
	StateElectoralInfo * statesInfo;
	statesInfo = new StateElectoralInfo [states]; //<-- Look at that dynamic alloc

	//stores ALLL the Data from the Electoral file in the Dynamically-Allocated array
	for(int i = 0; i < states; i++) {
    elecFile >> statesInfo[i].state; // Store dat name
    elecFile >> statesInfo[i].elecVotes; // Store dat vote #;
	};

	//THE BIG BAD function
	//Calculates ALL THE THINGS (about the canidates)
	for(int i = 0; i < states; i++) {
		int a, b; // Some Classy Vote Holders
		string theState; // <-- Stores the current state name
		voterFile >> a; // get c1 votes
		voterFile >> b; // getc2 votes
		voterFile >> theState; // get the name
		c1_total_votes += a; //sum the votes
		c2_total_votes += b;// sum the other votes
		int electoralVotes = getStateElecVotes(statesInfo, states,theState);
    if(electoralVotes !=-1) { // Gotta make sure that state exists
			if( a> b) { // If canidate A wins
				double margin = (double)a/((double)a+b); //<--Check out that double cast
				if(margin > best_c1_percent) { // Check new max
					best_c1_percent = margin; // Set C1 new max
          best_c1_state = theState; // Sets the State Name
        }
				c1_electoral_votes+= electoralVotes; // Sum dat C1 pop vote
			}
			else{ // If canidate B wins / draws (but there is no draws)
				double margin = (double)b/((double)a+b); //<-- Even More Double casting
				if(margin > best_c2_percent) {// Check new max
					best_c2_percent = margin; // Set C2 new max
          best_c2_state = theState; // BOOM SET THAT STATE NAME

        }
				c2_electoral_votes+=electoralVotes; // Sum dat C2 pop vote
			}
		}
	}
	delete[] statesInfo; // Freeing up that memory, my code ain't got no memleaks
                                                            //*crosses fingers*


//Apologies for ridiculous comments. Had a couple extra minutes, and y'all
//wouldn't let us leave.






	//**************************************
	// You are DONE!  The code below this point
	//  will use the values in the variables
	//  declared at the top of main to output
	//  the desired statistics to the screen.
	//**************************************
	string winner;
	string loser;
	int w_electoral;
	int l_electoral;
	int w_total;
	int l_total;
	if(c1_electoral_votes > c2_electoral_votes)
	{
		winner = candidate1;
		loser = candidate2;
		w_electoral = c1_electoral_votes;
		l_electoral = c2_electoral_votes;
		w_total = c1_total_votes;
		l_total = c2_total_votes;
	}
	else
	{
		winner = candidate2;
		loser = candidate1;
		l_electoral = c1_electoral_votes;
		w_electoral = c2_electoral_votes;
		l_total = c1_total_votes;
		w_total = c2_total_votes;
	}

	cout << winner << " defeated " << loser
	     << " in the electoral college." << endl;

	cout << "The electoral vote count was " << w_electoral
	     << " votes to " << l_electoral << " votes." << endl;

	cout << "The popular vote total was " << w_total << " to " << l_total << endl;

	cout << winner << "'s best state was " << best_c1_state << " where they won ";
	cout << 100*best_c1_percent << " percent of the votes" << endl;

	cout << loser << "'s best state was " << best_c2_state << " where they won ";
	cout << 100*best_c2_percent << " percent of the votes" << endl;

	return 0;
}
//****************************************
// Do not change the following line
//****************************************
#endif

//****************************************
// You may add code after this if you like
//****************************************
