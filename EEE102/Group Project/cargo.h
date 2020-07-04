#ifndef _cargo
#define _cargo
#include "warehouse.h"
#include <string>
#include <iostream>

using namespace std;

class cargo
{
private:
	int size = 0; //1 if it's for standard cargo and 2 if it's for small cargo
	bool empty = true; //A boolean that shows whether the place is empty or not
	double price = 0; //The price of this place
	string owner = "NoName"; //The owner of this cargo

public:
	cargo(); //Normal constructor
	cargo(int size, int price); //Constructor with parameters
	int getSize(); //To get the size of the warehouse ==> Big or small
	int getPrice(); //To get the price of the place for the cargo
	string getOwner(); //To set an owner for that place


	void setSize(int givenSize); //To set the size ==> standard (1) or small(2)
	void setPrice(int givenPrice); //To set a price for that place
	void setOwner(string givenOwner); //To set an owner for the cargo 
	void setEmpty(bool isEmpty); //To set a place to empty or full


	bool isEmpty(); //To see whether the warehouse has empty places left or not
	void display(); //To display the cargo information
};

#endif