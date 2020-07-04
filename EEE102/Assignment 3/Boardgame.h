//=========================================
//Boargame.h
//=========================================

//This class is used to represent and show the boardgame of the monopoly game


#include <iostream>
using namespace std;

#ifndef _BOARDGAME
#define _BOARDGAME

class boardgame {
public:
	boardgame(); //Normal constructor
	void showBoardgame(int location); //A function to print out the boardgame inside the console
};

#endif