#include "GridWorld.h"
#include <fstream>

const int LENGTH = 5;
const int WIDTH = 5;
const int SCAN_RADIUS = 1;
int realWorld[LENGTH][WIDTH] = {{0,0,0,0,0}, 
								{0,0,0,0,0},
								{0,0,1,1,0},
								{0,0,1,0,0},
								{0,0,0,0,0}};

GridWorld* world;

void scanMap(){
	int currentX = world->goal->x;
	int currentY = world->goal->y;

	for (int y = -SCAN_RADIUS; y < SCAN_RADIUS; y++){
		for (int x = -SCAN_RADIUS; x < SCAN_RADIUS; x++){
			if(world->withinWorld(currentX+x, currentY+y)){
				if(realWorld[currentY+y][currentX+x] == 1 && world->getTileAt(currentX+x, currentY+y)->cost != INFINITY){
					printf("\tInconistant Cost at %d %d\n", currentX+x, currentY+y);
				}
			}
		}
	}

	
}
void execute(){
	int counter = 0;
	world->computeShortestPath();
	//printWorld();
	while(world->start != world->goal){
		std::cout << "Iteration: "<< counter << std::endl;
		
		if(world->goal->rhs == INFINITY){
			std::cout << "\tNO PATH EXIST" << std::endl;
			break;
		}

		world->goal = world->goal->parent;
		
		if(world->goal != 0){
			printf("\tMoved to (%u, %u)\n", world->goal->x, world->goal->y);
		}else{
			printf("\tError null successor\n");
			return;
		}

		scanMap();
	}
}
void main(){
	world = new GridWorld(5,5);
	execute();
	system("PAUSE");
}


