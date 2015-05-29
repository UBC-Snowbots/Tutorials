#include "GridWorld.h"
#include <fstream>

const int LENGTH = 10;
const int WIDTH = 10;
const int SCAN_RADIUS = 1;

//TODO: TRY TO RESOLVE CRITICAL ERROR FOR MAP WITH RESOLUTION THAT'S NOT 1x1
int realWorld[LENGTH*WIDTH] = { 
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

GridWorld* world;


void scanMap(){
	int currentX = world->goal->x;
	int currentY = world->goal->y;

	for (int y = -SCAN_RADIUS; y <= SCAN_RADIUS; y++){
		for (int x = -SCAN_RADIUS; x <= SCAN_RADIUS; x++){
			if(world->withinWorld(currentX+x, currentY+y)){
				if(realWorld[(currentY+y)*LENGTH + currentX+x] == 1 && world->getTileAt(currentX+x, currentY+y)->cost != INFINITY){
					//printf("\tX: %d, Y:%d I:%d\n", currentX, currentY, (currentY+y)*LENGTH + currentX + x);
					//printf("\tInconistant Cost at %d %d\n", currentX+x+1, currentY+y);
					world->updateCost(currentX+x, currentY+y, INFINITY);
				}
			}
		}
	}

	
}

void execute(){
	int counter = 0;
	world->computeShortestPath();
	//world->printWorld();
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

		counter++;
		scanMap();
	}
}
void main(){
	std::cout << "Generating Map" << std::endl;
	world = new GridWorld(10);

	std::cout << "Finished generation" << std::endl;
	execute();
	//world->printWorld();
	std::cout << "Path calculated!" << std::endl;
	system("PAUSE");
}


