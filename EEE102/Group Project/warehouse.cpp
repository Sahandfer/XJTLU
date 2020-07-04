#include "warehouse.h"


warehouse::warehouse() { //When no parameters are given
	size = 0;
	numEmpty = 0;
	price = 0;
}

warehouse::warehouse(int size) {
	if (size == 1) { //If a big warehouse is created
		size = 1;
		numEmpty = 500; //We have 500 free spaces at first
		price = double(10000 / numEmpty); //We set the price for each 100000/number of empty spaces; meaning that initially price is 20 for each
	}

	else if (size == 2) { //If a small warehouse is created
		size = 2;
		numEmpty = 400; //We have 400 free spaces at first
		price = double(4000 / numEmpty); //We set the price for each 4000/number of empty spaces; meaning that initially price is 10 for each
	}
}

int warehouse::getSize() { //To return the size of the warehouse
	return size;
}

int warehouse::getEmpty() { //To see how many free spaces are left in the warehouse
	return numEmpty;
}

bool warehouse::isEmpty() {
	if (numEmpty != 0) { //In case the warehouse has no empty spaces
		return true;
	}
	else { //In case there are free spaces left
		return false;
	}
}

void warehouse::fill(int givenNum) {
	numEmpty = numEmpty - givenNum;
}

void warehouse::empty(int givenNum) {
	numEmpty = numEmpty + givenNum;
}