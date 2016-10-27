// hangman.cpp
// Hangman game illustrates string library functions,
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype. we'll define this below.
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char* wordBank[] = {"computer", "president", "trojan", "program",
			  "coffee", "library", "football", "popcorn",
			  "science", "engineer"};

const int numWords = 10;

int main()
{
	srand(time(0));
	char guess;
	bool wordGuessed = false;
	int numTurns = 10;

	// Pick a random word from the wordBank
	const char* targetWord = wordBank[rand() % numWords];
	char print[20];
	// More initialization code as needed
	char word[80]; // a blank array to use to build up the answer
	fill_n(word,80,'*');          // It should be initialized with *'s and then
	//  change them to the actual letters when the
	//  user guesses the letter
	// for(int i = 0; i < strlen(targetWord);i++){
	//   word[i] = '*';
	// }
	strncpy(print,word, strlen(targetWord)); // Creates exact length
	while(!wordGuessed ) {
		// Solves printing error
		cout << "Current Word:" << print<< endl;
		cout << numTurns << ":remain... Enter letter to get" << endl;
		cin >> guess;
		if(processGuess(word,targetWord,guess) == 0) { // Woot pass by reference
			numTurns--;
		}
		if(numTurns == 0) {
			break;
		}
		strncpy(print,word, strlen(targetWord)); // Update exact length string
		if(strcmp(print,targetWord) == 0) {
			wordGuessed = true;
		}
	}

	if(wordGuessed) {
		cout << "You Win";
	}
	else {
		cout << "You Lose";
	}


	return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess)
{
	bool hasChar = false;
	for(int i = 0; i < strlen(targetWord); i++) {
		if(targetWord[i] == guess) {
			word[i] = guess;
			hasChar = true;
		}
	}
	if(hasChar)
		return 1;
	return 0;
}
