#ifndef _WAREHOUSE
#define _WAREHOUSE
#include<iostream>


class warehouse
{
private:
	int size = 0; //1 if it's a big warehouse and 2 if it's a small warehouse
	int numEmpty; //Number of empty spaces left in a warehouse
	double price; //The price of each place

public:
	warehouse(); //Normal constructor
	warehouse(int size); //Constructor with parameters
	int getSize(); //To get the size of the warehouse ==> Big or small
	int getEmpty(); //To get the number of free spaces
	bool isEmpty(); //To see whether the warehouse is full or not
	void fill(int givenNum); //To fill in free spaces in the warehouse
	void empty(int givenNum); //To empty out a free space in the warehouse
};

#endif