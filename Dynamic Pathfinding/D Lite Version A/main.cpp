#include "GridWorld.h"

const int SIZE = 20;
const int SCAN_RADIUS = 4;

int realWorld[SIZE*SIZE] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

GridWorld* world;


void scanMap(){
	int currentX = world->start->x;
	int currentY = world->start->y;

	for (int y = -SCAN_RADIUS; y <= SCAN_RADIUS; y++){
		for (int x = -SCAN_RADIUS; x <= SCAN_RADIUS; x++){
			if (world->withinWorld(currentX + x, currentY + y)){

				if (realWorld[(currentY + y)*SIZE + currentX + x] == 1 
					&& world->getTileAt(currentX + x, currentY + y)->cost != INFINITY){
					printf("\tInconistant Cost at %d %d\n", currentX+x, currentY+y);
					world->updateCost(currentX + x, currentY + y, INFINITY);
				}
			}
		}
	}


}

void execute(){
	int counter = 0;

	//Having a wall during normal search doesn't seem to cause any problems
	//getTileAt(3,3)->cost = INFINITY;

	world->computeShortestPath();

	while (world->start != world->goal){
		std::cout << "Iteration :" << counter << std::endl;

		if (world->start->rhs == INFINITY){
			std::cout << "\tNO PATH EXIST" << std::endl;
			break;
		}

		world->start = world->getMinSuccessor(world->start).first;
		if (world->start != 0){
			std::cout << "\tMoved to: (" << world->start->x << ", " << world->start->y << ")" << std::endl;
		} else{
			std::cout << "NULL SUCCESSOR" << std::endl;
		}

		scanMap();
		counter++;
	}
	
	//Uncomment the line below to print every info about gridworld
	//world->printWorld();
}

void main(){
		std::cout << "Generating Map" << std::endl;
		world = new GridWorld(SIZE, SIZE);
		std::cout << "Finished generation" << std::endl;
		execute();
		std::cout << "Path calculated!" << std::endl;

		system("PAUSE");
}
