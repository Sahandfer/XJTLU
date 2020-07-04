//===================================
// player.h
//===================================

// This is to present a player (either user or computer) ==> Player Object

#ifndef _PLAYER
#define _PLAYER
#include <string>

using namespace std;

class player{

private:
	string name; //The name of the player
	string gender; //The gender of the player
	int balance; //The avaiable balance of the player
	int location; //The location of the player on the board

public:
	player(); //Normal constructor
	player(string name, string gender, int balance); //Constructor with parameters

	void setName(string name); //To set a name as the player's name
	void setBalance(int moneyAmount); //Top set the player's balance to an amount
	void setLocation(int location); //To set the player's location to a location
	void setGender(int whichGender); //To set the player's gender

	string getName(); //To get the player's name
	string getGender(); //To get the player's gender
	int getBalance(); //To get the player's available balance
	int getLocation(); //To get the player's current location

	void giveMoney(int moneyAmount); //To allow transactions to happen in the game (purchase locations)
	void takeMoney(int moneyAmount); //To allow transactions to happen in the game (purchase locations)
	void move(int steps); //To allow the player to move on the board

};

#endif