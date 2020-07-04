//=======================
//		container.cpp
//=======================
#include "container.h"
#include <iostream>

using namespace std;


// default constructor initialise the inventory as empty
container::container()
{
	set(0,0);
}

// set the item numbers
void container::set(int heal_n, int mw_n)
{
	numOfHeal=heal_n;
	numOfMW=mw_n;
}

// get the number of heal
int container::nOfHeal()
{
	return numOfHeal;
}

// get the number of magic water
int container::nOfMW()
{
	return numOfMW;
}

// display the items;
void container::display()
{
	cout<<"Your bag contains: "<<endl;
	cout<<"Heal(HP+100): "<<numOfHeal<<endl;
	cout<<"Magic Water (MP+80): "<<numOfMW<<endl;
}

//use heal
bool container::useHeal()
{
	numOfHeal--;
	return 1;		// use heal successfully
}

//use magic water
bool container::useMW()
{
	numOfMW--;
	return 1;		// use magic water successfully
}