#include "places.h"


places::places(){
	placeCost = 0; //The default cost is set to 0
	owner = 0; //The default is set to have no owner
	invested = 0; //The default is set to have no investor
}

places::places(int givenPlaceCost){
	placeCost = givenPlaceCost; //The cost is set to the given value
	owner = 0; //The default is set to have no owner
	invested = 0; //The default is set to have no investor
}

void places::setPlaceCost(int cost){
	placeCost = cost; //Here, we set the price of the place to the given value
}


void places::setOwner(int playerNum){
	owner = playerNum; //Here, we set the owner of a location (whether 0, 1 or 2)
}

void places::setInvested(int playerNum) {
	invested = playerNum; //Here, we set the investor of a location (whether 0, 1 or 2)
}


int places::getPlaceCost(){
	return placeCost; //To get the price of a location (place)
}


int places::getOwner(){
	return owner; //To get the owner of a location (place)
}

int places::getInvester() {
	return invested; //To get the investor of a location (place)
}