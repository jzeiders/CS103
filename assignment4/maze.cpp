/*
   maze.cpp

   Author: John Zeiders

   Short description of this file:
 */

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main() {
	int rows, cols, result;
	char** mymaze;

	mymaze = read_maze(&rows,&cols); // Primary Function

	if (mymaze == NULL) {
		cout << "Error, input format incorrect" << endl;
    for(int i = 0; i < rows;i++){
      delete[] mymaze[i];
    }
    delete[] mymaze;
		return 1;
	}

	// when working on Checkpoint 3, you will call maze_search here.
	// here. but for Checkpoint 1, just assume we found the path.
	result = maze_search(mymaze, rows, cols);

	// examine value returned by maze_search and print appropriate output
	if (result == 1) { // path found!
		print_maze(mymaze, rows, cols);
	}
	else if (result == 0) { // no path :(
		cout << "No path could be found!" << endl;
	}
	else { // result == -1 // Broken Maze
		cout << "Invalid maze." << endl;
	}

	// ADD CODE HERE to delete all memory
	// that read_maze allocated
  for(int i = 0; i < rows;i++){
    delete[] mymaze[i];
  }
  delete[] mymaze;
	return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) {
	//Creates pred array
	Location** pred = new Location*[rows];
	for(int i = 0; i < rows; i++)
		pred[i] = new Location[cols];
	for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
			pred[i][j].row = -1; //Row value of -1 -> not visited
	Location start, end, cur;
	start.row = -1;
	end.row = -1;
	Queue q(rows*cols);
	//Finds start and finish
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			if(maze[i][j] == 'S') {
				start.row = i;
				start.col = j;
			}
			if(maze[i][j] == 'F') {
				end.row = i;
				end.col = j;
			}
		}
	}
	//Terminates if start or end not found
	if(start.row == -1 || end.row == -1) {
    for(int i = 0; i < rows;i++){
      delete[] pred[i];
    }
    delete[] pred;
    return -1;
  }
	q.add_to_back(start);

	while(!q.is_empty()) {
		cur = q.remove_from_front();
		if(maze[cur.row][cur.col] == 'F') { // Terminates on finish
			while(cur.row != -1) {
				cur = pred[cur.row][cur.col];
				if(cur.row == start.row && cur.col == start.col ){ // Current == end
          for(int i = 0; i < rows;i++){
            delete[] pred[i];
          }
          delete[] pred;
          return 1;
        }
				maze[cur.row][cur.col] = '*';
			}
		}
		//Check Down
		if(cur.row+1 < rows && (maze[cur.row+1][cur.col] == '.' || // is empty
		  maze[cur.row+1][cur.col] == 'F') && // is finish
		   pred[cur.row+1][cur.col].row == -1) { // is unvisited
			Location loc=  {
				cur.row+1,
				cur.col
			};
			q.add_to_back(loc);
			pred[loc.row][loc.col] = cur;
		}
		//Check right
		if(cur.col+1 < cols && (maze[cur.row][cur.col+1] == '.' ||
		  maze[cur.row][cur.col+1] == 'F')&&
		    pred[cur.row][cur.col+1].row == -1) {
			Location loc = {
				cur.row,
				cur.col+1
			};
			q.add_to_back(loc);
			pred[loc.row][loc.col] = cur;
		}
		//Check up
		if(cur.row > 0 && (maze[cur.row-1][cur.col] == '.'||
		  maze[cur.row-1][cur.col] == 'F') &&
		    pred[cur.row-1][cur.col].row == -1) {
			Location loc = {
				cur.row-1,
				cur.col
			};
			q.add_to_back(loc);
			pred[loc.row][loc.col] = cur;
		}
		//Check left
		if(cur.col > 0 && (maze[cur.row][cur.col-1] == '.' ||
		  maze[cur.row][cur.col-1] == 'F')&&
        pred[cur.row][cur.col-1].row == -1) {
			Location loc = {
				cur.row,
				cur.col-1
			};
			q.add_to_back(loc);
			pred[loc.row][loc.col] = cur;
		}
	}
  for(int i = 0; i < rows;i++){
    delete[] pred[i];
  }
  delete[] pred;
	return 0;
}
