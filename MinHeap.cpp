#include <iostream>
#include <math.h>

using namespace std;


/******************** VARIABLES ********************/
// since these variables are global variables, you can just directly access them 
// in your functions

int map_width = 10;
int map_height = 10;
int map[10*10];		// the array that holds the map
int frontier_size = 0;		// the used size of the frontier min-heap (priority queue)

// this is the min-heap that sorts the current open set of map_location priorities
// by their estimated costs (which is in the estimated_costs array) 
int frontier[10*10];		// the current open set that we are searching
int cost_from_start[10*10];	// cost from the start location to the current location
int estimated_cost[10*10];	// estimated_cost[x] = cost_from_start[x] + Heuristic(x, goal) 


// assigns a probability of 0 occupancy in each map unit (to start)
void RandomMap()
{
	int x, y, index;
	
	for (y = 0; y < map_height; y++) {
		for (x = 0; x < map_width; x++) {
			index = y*map_width + x;
			map[index] = 0;
		}
	} 
}


/******************* PART ONE ************************/

// converts an (x, y) coordinate to a map index
int GetIndex(int x, int y) 
{
	return 0; 
}


// The heuristic function we will be using.
// Output: the direct distance from start_location to goal_location
int Heuristic(int start_location, int goal_location)
{
	return 0;
}


// This swaps the position of node 1 and node 2 in the heap
void Swap(int *position_1, int *position_2) 
{
	return;
} 



/******************* PART TWO ************************/

// This inserts a location into our min-heap and swaps it depending on it's priority
// The min-heap we will be prioritizing is the frontier.
// The priority is based on the estimated costs of the location in the estimated_costs array

void Insert(int location) 
{
	// Here are some resources
	// http://en.wikipedia.org/wiki/Min-max_heap
	// https://www.youtube.com/watch?v=-6-xKgLOZPM
	return;
}



/******************* PART THREE ************************/


// This removes the minimum value from a min-heap and recalculates the priorities
// of the heap
// This inserts a location into our min-heap and swaps it depending on it's priority
// The min-heap we will be prioritizing is the frontier.
// The priority is based on the estimated costs of the location in the estimated_costs array

void RemoveRoot()
{
	// Here are some resources
	// http://en.wikipedia.org/wiki/Min-max_heap
	// https://www.youtube.com/watch?v=-6-xKgLOZPM
	return;
}



// No need to change this. Only main actually runs the program though, so you
// can type in what you need to test your functions here.
int main()
{
	return 0;
}