//===================================
// player.cpp
//===================================

// This is to present a player ==> Player Object

#include "player.h"

player::player(){ //The normal constructor
	name = "No name"; //The default name is set to "No name"
	gender = "No gender"; //The default gender is set to be "No gender"
	balance = 10000; //The default balance is set to be 10000 points
	location = 0; //And the player starts at the starting point (location=0)
}


player::player(string givenName, string givenGender, int givenBalance){ //Constructor with parameters
	name = givenName; //The default name is set to be the given name
	gender = givenGender; //The default gender is set to be the given value
	balance = givenBalance; //The default balance is set to be the given amount
	location = 0; //And the player starts at the starting point (location=0)
}


void player::setName(string givenName){ //This is to set a name for a player object
	name = givenName;
}


void player::setBalance(int givenBalance){ //This is to set a balance for the player object.
	balance = givenBalance;
}


void player::setLocation(int givenLocation){ //This is to set a location for the player
	location = givenLocation;
}


void player::setGender(int givenGender) { //This is to set a gender for the player
	if (givenGender == 1) {
		gender = "Male";
	}
	else {
		gender = "Female";
	}
}


string player::getName(){ //This is to get the player object's name
	return name;
}


string player::getGender(){ //This is to get the player object's gender
	return gender;
}


int player::getBalance(){ //This is to get the player object's balance
	return balance;
}


int player::getLocation(){ //This is to get the player object's location
	return location;
}


void player::giveMoney(int moneyAmount){ //This is to transfer money to the player's balance
	balance = balance + moneyAmount;
}


void player::takeMoney(int moneyAmount){ //This is for taking money from the player's balance
	balance = balance - moneyAmount;
}


void player::move(int steps){ //This is used to move the player on the gameboard
	location = location + steps;
}
