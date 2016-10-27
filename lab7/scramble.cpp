// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

// Define an array of strings (an array of char pointers, like argv)




int main(int argc, char *argv[]) {
  srand(time(NULL));
  char guess[80];
  if(argc != 2){
    cout << "Invalid input";
    return 0;
  }
  int length;
  ifstream wordFile (argv[1]);
  if(wordFile.fail()){
    cout << "Failed, Unable to open file";
    return 0;
  }

  wordFile >> length;
  if(length == 0){
    cout << "Not an int";
    return 0;
  }

  length = (int)length;

  char* wordBank[length];

  for(int i = 0; i < length; i++){
    char buffer[41];
    wordFile >> buffer;
    wordBank[i] = new char[strlen(buffer)+1];
    strcpy(wordBank[i],buffer);
  }
  bool wordGuessed = false;
  int numTurns = 10;
  // Pick a random word from the wordBank
  int target = rand() % length;
  int targetLen = strlen(wordBank[target]);


  // Make a dynamically-allocated copy of the word and scramble it
  char* word = new char[targetLen+1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);

  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (!wordGuessed && numTurns > 0) {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? ";
    cin >> guess;
    wordGuessed = (strcmp(guess, wordBank[target]) == 0);
    numTurns--;
  }
  if (wordGuessed) {
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
  }
  delete [] word;
  for(int i =0 ; i < length; i++){
    delete [] wordBank[i];
  }
  return 0;
}

// Scramble the letters. See "Knuth shuffle" on Wikipedia.
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}
