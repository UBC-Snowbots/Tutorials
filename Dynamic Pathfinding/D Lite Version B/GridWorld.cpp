#include "GridWorld.h"

GridWorld::GridWorld(unsigned int xSize, unsigned int ySize){
	for (unsigned int y = 0; y < ySize; y++){
		std::vector<Tile* const> row;
		for (unsigned int x = 0; x < xSize; x++){
			row.push_back(new Tile(x, y, 10));
		}
		world.push_back(row);
	}

	goal = getTileAt(0,0);
	start = getTileAt(xSize - 1, ySize - 1);

	//INIT
	km = 0;
	
	start->rhs = 0;
	
	start->isOpen = true;
	start->h = calculateH(start);
	start->key = std::pair<double,double>(start->h, 0);
	open.push_back(start);
}

void GridWorld::replan(){
	int counter = 0;
	oldGoal = goal;
	computeShortestPath();

	while(start != goal){
		std::cout << "Iteration: "<< counter << std::endl;
		if(counter == 0){
			//updateCost(3,3,INFINITY);
		}
		if(counter == 1){
			//updateCost(3,3,10);
			//Uncomment the 3 lines below to completely block the start
			//updateCost(3,3,INFINITY);
			//updateCost(3,4,INFINITY);
			//updateCost(4,3,INFINITY);
		}

		if(goal->rhs == INFINITY){
			std::cout << "\tNO PATH EXIST" << std::endl;
			break;
		}

		goal = goal->parent;
		if(goal != 0){
			printf("\tMoved to (%u, %u)\n", goal->x, goal->y);
		}else{
			printf("\tError\n");
			return;
		}
		
		counter++;
	}
	
	//Uncomment the line below to print every info about gridworld
	//printWorld(false);
}


void GridWorld::updateCost(unsigned int x, unsigned int y, double cost){
	Tile* tile = getTileAt(x,y);
	
	km += calculateH(oldGoal);
	oldGoal = goal;

	//std::cout << "Tile at (" << x << ", " << y << ") is undergoing a COST change" << std::endl;

	double oldCost, newCost;

	for (Tile* neighbour : getNeighbours(tile)){
		oldCost = calculateC(tile, neighbour);

		tile->cost = cost;
		newCost = calculateC(tile, neighbour);

		if (oldCost > newCost){
			if(neighbour != start && neighbour->rhs > tile->g + newCost){
				neighbour->parent = tile;
				neighbour->rhs = tile->g + newCost;
				updateVertex(neighbour);
			}

		} else if (neighbour != start && neighbour->parent == tile){
			TilePair minSucc(getMinSuccessor(neighbour));
			neighbour->rhs = minSucc.second;
			neighbour->parent = (neighbour->rhs == INFINITY ? 0 : minSucc.first);

			updateVertex(neighbour);
		}
	}
	
	computeShortestPath();
}

bool GridWorld::computeShortestPath(){
	if(open.empty()){
		std::cout << "ERROR: No tiles to expand on... can't do anything" << std::endl;
		return false;
	}


	while(!open.empty() && (compareKeys(open.front()->key, goal->key = calculateKey(goal)) || goal->rhs != goal->g)){
		Tile* current = open.front();
		//Notice that CURRENT wasn't pop/removed yet

		//std::cout << "Expanding:";
		//current->info();
		//std::cout << std::endl;
		KeyPair k_new = calculateKey(current);
		
		if(compareKeys(current->key, k_new)){
			//Tiles under this branch will have to be updated as incremental search has happened
			current->key = k_new;
			make_heap(open.begin(), open.end(), GridWorld::compareTiles);

		} else if (current->g > current->rhs){
			//Majority of the tiles will fall under this conditional branch as
			//it undergoes normal A* pathfinding

			current->g = current->rhs;

			open.erase(open.begin());
			make_heap(open.begin(), open.end(), GridWorld::compareTiles);
			current->isOpen = false;

			for (Tile* neighbour : getNeighbours(current)){
				if(neighbour != start && neighbour->rhs > current->g + calculateC(current, neighbour)){
					neighbour->parent = current;
					neighbour->rhs = current->g + calculateC(current, neighbour);
					updateVertex(neighbour);
				}
			}

		} else {
			//Tiles under this branch will need to be updated during incremental search
			current->g = INFINITY;

			//Update CURRENT
			if(current != start && current->parent == current){
				TilePair minSucc(getMinSuccessor(current));
				current->rhs = minSucc.second;
				current->parent = current->rhs == INFINITY ? 0 : minSucc.first;
			}
			updateVertex(current);

			//Update NEIGHBOURS
			for (Tile* neighbour : getNeighbours(current)){
				if(neighbour != start && neighbour->parent == current){
					TilePair minSucc(getMinSuccessor(neighbour));
					neighbour->rhs = minSucc.second;
					neighbour->parent = neighbour->rhs == INFINITY ? 0 : minSucc.first;
				}
				updateVertex(neighbour);
			}

		}
		//Uncomment this to see CURRENT'S new values
		//std::cout << "Expanded:";
		//current->info();
		//std::cout << std::endl;
	}
	return true;
}

void GridWorld::updateVertex(GridWorld::Tile*& tile){
	bool isIncosistent = tile->rhs != tile->g; //potential problem with floating point comparison?

	if(isIncosistent && tile->isOpen){
		make_heap(open.begin(), open.end(), GridWorld::compareTiles);
	
	}else if(isIncosistent && !tile->isOpen){
		tile->h = calculateH(tile);
		tile->key = calculateKey(tile);
		tile->isOpen = true;
		
		open.push_back(tile);
		push_heap(open.begin(), open.end(), GridWorld::compareTiles);
		
	}else if (!isIncosistent && tile->isOpen){
		open.erase(std::find(open.begin(), open.end(), tile));
		make_heap(open.begin(), open.end(), GridWorld::compareTiles);
		tile->isOpen = false;
	}

}


bool GridWorld::withinWorld(unsigned int x, unsigned int y) const{
	return y >= 0 && y < world.size() && x >= 0 && x < world.at(0).size();
}

GridWorld::Tile* GridWorld::getTileAt(unsigned int x, unsigned int y) const{
	return withinWorld(x,y) ? (world.at(y).at(x)) : NULL;
}

std::vector<GridWorld::Tile*> GridWorld::getNeighbours(Tile*& tile){
	//It should be impossible to return a null neighbour, therefore I didn't bother
	//with null pointer checks whenever I use this method
	std::vector<GridWorld::Tile*> neighbours;
	for (int dy = -1; dy <= 1; dy++){
		for (int dx = -1; dx <= 1; dx++){
			if(abs(dy) + abs(dx) != 0){
				Tile* neighbour = getTileAt(tile->x + dx, tile->y + dy);
				if (neighbour != 0){
					neighbours.push_back(neighbour);
				}
			}
		}
	}

	return neighbours;
}

bool GridWorld::compareTiles(Tile*& left, Tile*& right){
	/* 
		The heap functions from <algorithm> operates as a MAX heap,
		by making sure that left < right. In order to operate as a MIN heap
		we'll reverse the order by comparing right < left
	 */
	return compareKeys(right->key, left->key);
}

bool GridWorld::compareKeys(const KeyPair& left, const KeyPair& right){
	if(left.first < right.first){
		return true;
	} else if(left.first == right.first && left.second < right.second){
		return true;
	} else {
		return false;
	}
}

GridWorld::TilePair GridWorld::getMinSuccessor(GridWorld::Tile*& tile){
	Tile* minTile = 0;
	double minCost = INFINITY;

	for (Tile* neighbour : getNeighbours(tile)){
		double cost = calculateC(tile, neighbour);
		double g = neighbour->g;
			
		if(cost == INFINITY || g == INFINITY){
			continue;
		}
			
		if(cost + g < minCost){ //potential overflow?
			minTile = neighbour;
			minCost = cost + g;
		}
	}
	
	return TilePair(minTile, minCost);
}

double GridWorld::calculateH(GridWorld::Tile*& tile){
	unsigned int dx = labs(tile->x - goal->x);
	unsigned int dy = labs(tile->y - goal->y);

	if(dx > dy){
		std::swap(dx,dy);
	}

	return ((SQRT2-1) * dx + dy) * 10;
}

double GridWorld::calculateC(GridWorld::Tile*& tileA, GridWorld::Tile*& tileB){
	if(tileA->cost == INFINITY || tileB->cost == INFINITY){
		return INFINITY;
	}

	if(labs(tileA->x - tileB->x) + labs(tileA->y - tileB->y) == 2){
		//These two tiles are diagonally adjacent to each other
		return SQRT2 * (tileA->cost + tileB->cost) / 2;
	}
	return (tileA->cost + tileB->cost) / 2;
}

GridWorld::KeyPair GridWorld::calculateKey(GridWorld::Tile*& tile){
	double key2 = std::min(tile->g, tile->rhs);
	double key1 = key2 + tile->h + km;		//Potential overflow in addition?

	return KeyPair(key1, key2);
}


GridWorld::Tile::Tile(unsigned int x, unsigned int y, double cost) : x(x), y(y){
	this->cost = cost;

	this->rhs = INFINITY;
	this->g = INFINITY;
	this->h = 0;

	this->isOpen = false;
	this->parent = 0;
}

GridWorld::Tile::Tile(Tile& other) : x(other.x), y(other.y){
	this->cost = other.cost;

	this->rhs = other.rhs;
	this->g = other.g;
	this->h = other.h;

	this->isOpen = other.isOpen;
	this->parent = other.parent;
}

void GridWorld::Tile::info() const{

	printf("[(%d, %d)  H: %.2lf, G: %.2lf, RHS: %.2lf, K:<%.2lf, %.2lf>]", this->x, this->y,
		this->h == INFINITY ? -1 : this->h, 
		this->g == INFINITY ? -1 : this->g,
		this->rhs == INFINITY ? -1 : this->rhs, 
		this->key.first == INFINITY ? -1 : this->key.first,
		this->key.second == INFINITY ? -1 : this->key.second);

	if(this->parent != 0){
		printf("[P: (%u, %u)]", this->parent->x, this->parent->y);
	}
}

void GridWorld::printWorld(bool parentTrace) const{
	for (unsigned int y = 0; y < world.size(); y++){
		for (unsigned int x = 0; x < world.at(0).size(); x++){
			Tile* t = getTileAt(x, y);
			if(parentTrace){
				if(t->parent != 0){
					printf("Tile (%u, %u) has parent (%u, %u)\n", t->x, t->y, t->parent->x, t->parent->y);
				}
			}else{
				t->info();
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;
	}
}