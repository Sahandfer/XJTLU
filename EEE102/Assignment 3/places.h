

#ifndef _PLACES
#define _PLACES


class places{

private:
	int placeCost; //A variable to hold the price that a location on the boardgame costs.
	int owner; //A variable that takes 0, 1, 2 to show that there are no owners, owner is the user or owner is the computer respectively
	int invested; //A variable that shows whether a location on the boardgame is invested on and who has invested in it
		  
	//Note:
	//invested==0 means no one has invested in this location
	//invested==1 means the user has invested in this location
	//invested==2 means the computer has invested in this location


public:
	places(); //Normal constructor
	places(int placeCost); //Constructor with parameters
	void setPlaceCost(int cost); //A function to set a price for a location
	void setOwner(int playerNum); //A function to set an owner for a location (0: no owner, 1: player is owner, 2: computer is owner)
	void setInvested(int player); //A function to set an investor for a location

	int getPlaceCost(); //A function to get the price of a place
	int getOwner(); //A function to get the owner of a location (place)
	int getInvester();  //A function to get the investor of a location (place)

};
#endif