#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include "player.h"
#include "places.h"
#include "Boardgame.h"

using namespace std;

int rollDice() { //A function that returns a random number from 1-6
	int diceNum = rand() % 6 + 1; //This gives a random number from 1-6
	return diceNum;
}


void showinfo(player *user, player *computer){ //A function to print out both of the players' info on the screen
	
	system("cls"); //Clear everything that was printed before

	cout << "===============================================================================" << endl << endl;
	cout << "+Your Name: " << user->getName() << endl;
	cout << "+Your Gender: " << user->getGender() << endl;
	cout << "+Your balance: " << user->getBalance() << endl;
	cout << "+Your location: " << user->getLocation() << endl << endl;
	cout << "===============================================================================" << endl << endl;
	cout << "-Opponent's Name: " << computer->getName() << endl;
	cout << "-Opponent's Gender: " << computer->getGender() << endl;
	cout << "-Opponent's balance: " << computer->getBalance() << endl;
	cout << "-Oppononent's location: " << computer->getLocation() << endl << endl;
	cout << "===============================================================================" << endl << endl;
}

void showDice(int diceNum){ //A function to show the number that was randomly chosen (to inform the user)
	cout << "===============================================================================" << endl << endl;
	cout << setw(50) << "The dice shows ==> "<< diceNum<< endl << endl;
	cout << "===============================================================================" << endl << endl;
}

void passedStart(player *p) { //A function that checks whether a player has passed the start point.
	p->setLocation(p->getLocation() - 80);
	cout << "You have passed the starting point! 200 points have been added to your balance!" << endl << endl;
	p->giveMoney(200); //As the rules say, we have to award the player with 200 points at this point
}

bool saveExists(const string userSave) {
	ifstream savefile(userSave.c_str());
	return (bool)savefile;
}

int main(){
	int diceNum; //An integer variable to hold the generated dice number
	int rounds=0; //An integer that indicates how many rounds the game has been played
	fstream userSave; //A file to store user's information
	fstream computerSave; //A file to store the computer's information
	bool userSaveExist= false; //A boolean that checks whether user's save files exist or not
	bool computerSaveExist = false; //A boolean that checks whether computer's save files exist or not
	player *user; //A player object representing the user
	player *computer; //A player object representing the computer (AI)
	boardgame ourBoardGame; //A boardgame object used to represent the monopoly game board.
	string name = " "; //A variable to temporarily hold the name of the user
	string gender =" "; //A variable to temporarily hold the gender of the user
	int genderChoice; //A variable to temporarily hold the value of the user's gender (1 for male and 2 for female)
	int userBalance = 10000; //A variable to temporarily hold the balance of the user
	int computerBalance = 10000; //A variable to temporarily hold the balance of the computer
	int menuChoice; //A variable that allows the user to surf around the menu
	int saveChoice; //A variable that allows the user to choose whether they want to load their save or not
	int choiceNum; //A variable that allows the user to make choices in the gameplay
	int currentLocation; //A variable to temporarily hold the current location of each player
	int mustPay; //A variable to temporarily hold the cost of the current location
	char line[250]; //A variable named to get the user's information from the file
	places placeList[80]; //An array to store all of the places on the boardgame
	string temp; //A variable to temporarily hold string data
	string beforeComma; //A variable to hold every data that comes before the comma( when reading from file)
	string afterComma;  //A variable to hold every data that comes after the comma( when reading from file)
	vector <string> userInformation; //A vector to hold user's data coming before and after the comma
	vector <string> firstUserInfo; //A vector to hold each of the information (name, balance, location and bought places) of the user 
	vector <string> secondUserInfo; //A vector to hold each of the invested places numbers for the user
	vector <string> computerInformation; //A vector to hold computer's data coming before and after the comma
	vector <string> firstComputerInfo; //A vector to hold each of the information (location, balance and bought places) of the computer 
	vector <string> secondComputerInfo; ////A vector to hold each of the invested places numbers for the computer

	placeList[0] = places(0); //The starting point is set to have a cost of 0

	for (int i = 1; i < 80; i++){ //Then the cost of the rest of the places would be randomly determined (between 10-500)
		placeList[i] = places((rand()%491)+10);
	}

	int menuLoopHolder = 0; //A variable to keep the loop for the menu going
	int errorLoopHolder = 0; //A variable to keep the loop for checking errors going (the loop will go as long as there is invalid input)
	
	

	
	cout << "===============================================================================" << endl<<endl;
	cout << setw(50) << "< Welcome To Monopoly >" << endl<<endl;
	cout << "===============================================================================" <<endl<<endl;
	
	user = new player(name, gender, userBalance); //We first initiate a new player to represent the user
	computer = new player("Computer", "No gender", computerBalance); //And then a player to represent the computer
	userSaveExist= saveExists("userSave.txt"); //We create a file for the user's data to be written to (or save to be read from)
	computerSaveExist = saveExists("computerSave.txt"); //We create a file for the computer's data to be written to (or save to be read from)

	if (userSaveExist==true && computerSaveExist == true) { //This checks whether there exists a save file
		
		
		while (errorLoopHolder == 0) {
			cout << "Save File Found! Would you like your previous play?" << endl;
			cout << "1. Yes" << setw(30) << "2. No" << endl;
			cin >> saveChoice;
			if (saveChoice != 1 && saveChoice != 2) { //In case the user enters an invalid input
				cout << "Unacceptable input! please try again! (Only input 1 or 2)" << endl;
			}
			
			else { //In case the user enters a valid input
				errorLoopHolder = 1;
			}
		}


		if (saveChoice == 1) { //In case the user chooses to load the save file and resume previous progress
			system("cls"); //This clears the screen so that the console doesn't look messy with everything displayed at the same time
			cout << "===============================================================================" << endl << endl;
			cout << "Loading save file..." << endl<<endl;
			userSave.open("userSave.txt"); //We open the file we want to read from
			userSave.getline(line,250); //We read everything from the file into a line
			istringstream stream1(line); //Then we convert the line to a string stream so that it can be split

			while (getline(stream1, temp, ',')) { //Here we split the line by ',' and enter the substrings in a vector
				userInformation.push_back(temp);
			}

			//Since there is only one comma in the file, we get to substrings ==> before and after the comma
			beforeComma = userInformation[0]; //Includes the user's name, balance, location and number of purchased locations
			afterComma = userInformation[1]; //Includes number of user's invested locations with a 0 at the end
			
			//Note ==> zero exists in the case that there are no invested locations in the save.
			 //The point of this zero is to prevent an index out of bounds error

			//Here we use two different string streams in order for the data before and after the comma to be split
			istringstream stream2(beforeComma); 
			istringstream stream3(afterComma);


			while (stream2 >> temp) { //We split the data by the space between them
				firstUserInfo.push_back(temp); //And enter each individual piece of info inside a vector
			}

			while (stream3 >> temp) { //We split the data by the space between them
				secondUserInfo.push_back(temp); //And enter each individual piece of info inside a vector
			}

			//The following are the data that are read from the file. The order depends on the way we wrote data to the file in the first place.
			user->setName(firstUserInfo[0]); //The first index points to the user's name
			user->setGender(stoi(firstUserInfo[1])); //The second index points to the user's gender
			user->setBalance(stoi(firstUserInfo[2])); //The third index points to the user's balance
			user->move(stoi(firstUserInfo[3])); //The fourth index points to the user's location

			//After that everything else in this vector points to the purchased locations' numbers.
			for (int i = 4; i < firstUserInfo.size(); i++) {
				placeList[stoi(firstUserInfo[i])].setOwner(1);
			}

			//Everything in this vector, except the last index which points to 0, points to the number of invested locations.
			for (int i = 0; i < secondUserInfo.size() - 1; i++) {
				placeList[stoi(secondUserInfo[i])].setInvested(1);
			}
			userSave.close(); //We close the file after we are done with reading.

			computerSave.open("computerSave.txt"); //We open the file we want to read from
			computerSave.getline(line, 250); //Read everything from the file into a line
			istringstream stream4(line); //Then use a string stream to make the line splittable

			while (getline(stream4, temp, ',')) { //Now we get a vector for storing the two obtained substrings
				computerInformation.push_back(temp);
			}

			beforeComma = computerInformation[0]; //includes the computer's balance, location and purchased locations' numbers
			afterComma = computerInformation[1]; //Includes the invested locations' numbers and a 0 at the end

			//Note ==> zero exists in the case that there are no invested locations in the save.
			//The point of this zero is to prevent an index out of bounds error

			istringstream stream5(beforeComma);
			while (stream5 >> temp) {
				firstComputerInfo.push_back(temp); //Here we split the data by a space
			}

			istringstream stream6(afterComma);
			while (stream6 >> temp) {
				secondComputerInfo.push_back(temp); //Here we split the data by a space
			}

			computer->setBalance(stoi(firstComputerInfo[0])); //The first index in this vector points to the computer's balance
			computer->move(stoi(firstComputerInfo[1])); //The second index in this vector points to the computer's location


			//The rest of the entries in this vector point to the purchased locations' numbers
			for (int i = 2; i < firstComputerInfo.size(); i++) {
				placeList[stoi(firstComputerInfo[i])].setOwner(2);
			}

			//In this vector, all the indexes except the last one which is 0, point to the invested locations' numbers
			for (int i = 0; i < secondComputerInfo.size() - 1; i++) {
				placeList[stoi(secondComputerInfo[i])].setInvested(2);
			}

			cout << "Save successfully loaded!" << endl << endl;
			cout << "===============================================================================" << endl << endl;
			computerSave.close(); //We close the file after we are done with reading.
			system("pause");
			
			//Now we remove the already loaded save files, so that new save files can replace these
			remove("userSave.txt");
			remove("computerSave.txt");

		}


		else { //In case the user does not wish to continue previous progress
			  
			//We remove the already found save files, so that new save files can replace these
			remove("userSave.txt");
			remove("computerSave.txt");


			errorLoopHolder = 0; //We set the value back to 0 so that it can be used again
			system("cls");

			//To get the user's information
			cout << endl<<"Please choose a name for your character ==> ";
			cin >> name;
			cout << endl;
			while (errorLoopHolder == 0) {
				cout << "Please choose a gender for your character: " << endl;
				cout << "1. Male" << setw(30) << "2. Female" << endl;
				cin >> genderChoice;
				if (genderChoice != 1 && genderChoice != 2) {
					cout << "Unacceptable input! please try again! (Only input 1 or 2)" << endl;
				}
				else {
					errorLoopHolder = 1; //To break the loop
				}
			}

			user->setName(name); //To set the player's name to the input name
			user->setGender(genderChoice); //The set the player's gender to the input gender
			
		}
	}

	else {
		//To get the user's information
		cout << "Please choose a name for your character ==> ";
		cin >> name;
		cout << endl;
		while (errorLoopHolder == 0) {
			cout << "Please choose a gender for your character: " << endl;
			cout << "1. Male" << setw(30) << "2. Female" << endl;
			cin >> genderChoice;
			if (genderChoice != 1 && genderChoice != 2) {
				cout << "Unacceptable input! please try again! (Only input 1 or 2)" << endl;
			}
			else {
				errorLoopHolder = 1; //To break the loop
			}
		}

		user->setName(name); //To set the player's name to the input name
		user->setGender(genderChoice); //The set the player's gender to the input gender
	}

	

	while (menuLoopHolder == 0) {


		showinfo(user, computer);
		errorLoopHolder = 0; //We set the value back to 0 so that it can be used again


		//To ask the user whether they want to play and roll the dice, or quit the game 
		while (errorLoopHolder == 0) {
			cout << "It's your turn!" << endl;
			cout << "Please choose one of the following options: " << endl << endl;
			cout << "1. Roll the Dice" << endl << "2. Quit and save the game" << endl << endl;
			cin >> menuChoice;
			if (menuChoice != 1 && menuChoice != 2) {
				cout << "Invalid input! please try again! (Only input 1 or 2" << endl << endl;
			}
			else {
				errorLoopHolder = 1;
			}
		}

		if (menuChoice == 2) {
			cout << "Thank you for playing my game!" << endl;
			if (rounds != 0) { //We would only save if we aren't in the first round
			//Since the game is about to be closed, we need to save the progress
			userSave.open("userSave.txt", ios::out); //We open the file in writing mode
			userSave << user->getName() << " "; //We first write the user's name into the file with a space after it

			//Since we use a number to define the user's gender we write the number the corresponds the user's gender
			if (user->getGender() == "Male") {
				userSave << "1 ";
			}
			else {
				userSave << "2 ";
			}

			userSave << user->getBalance() << " "; //Then we write the user's balance with a space after it
			userSave << user->getLocation() << " "; //Then we write the user's current location with a space after it

			//Here, we are using a for loop to check whether a location is owned by the user, and 
			//if it is, its number will be written to the file with a space after it

			for (int i = 1; i < 80; i++) {
				if (placeList[i].getOwner() == 1) {
					userSave << i << " ";
				}
			}

			userSave << ", "; //Now we add a comma to separate the purchased and invested locations' numbers

			//Here, we are using a for loop to check whether a location is invested in by the user, and 
			//if it is, its number will be written to the file with a space after it

			
			for (int i = 1; i < 80; i++) {
				if (placeList[i].getInvester() == 1) {
					userSave << i << " ";
				}
			}
			userSave << " 0";
			//We write a 0 to the file in case there is no invested locations for the user, to prevent index out of bounds when reading

			userSave.close(); //Then we close the file to save the progress


			computerSave.open("computerSave.txt", ios::out); //We open the file in writing mode

			computerSave << computer->getBalance() << " "; //First we write the computer's balance to the file with a space after it
			userSave << computer->getLocation() << " ";//Then we write the computer's location to the file with a space after it

			//Here, we are using a for loop to check whether a location is owned by the computer, and 
			//if it is, its number will be written to the file with a space after it
			for (int i = 1; i < 80; i++) {
				if (placeList[i].getOwner() == 2) {
					computerSave << i << " ";
				}
			}

			computerSave << ", "; //Now we add a comma to separate the purchased and invested locations' numbers


			//Here, we are using a for loop to check whether a location is invested in by the computer, and 
			//if it is, its number will be written to the file with a space after it
			for (int i = 1; i < 80; i++) {
				if (placeList[i].getInvester() == 2) {
					computerSave << i << " ";
				}
			}

			//We write a 0 to the file in case there is no invested locations for the user, to prevent index out of bounds when reading
			computerSave << " 0";
			computerSave.close(); //Then we close the file to save the progress

			cout << "Your progress has been successfully saved!" << endl;
		}
			menuLoopHolder = 1; //In order to break the loop and finish the program
			break;
		}

		else {
			system("cls");
			errorLoopHolder = 0; //We set the value back to 0 so it can be used again
			diceNum = rollDice(); //This rolls the dice
			showDice(diceNum); //This showed the number that the dice shows
			user->move(diceNum); //The user moves on the map according to the number of dice
			currentLocation = user->getLocation(); //We store user's current location in the variable currentLocation

			//We check whether the user has passed the starting point or not
			
			if (currentLocation > 79) { //If they have, 
				currentLocation = currentLocation - 80; //Their location will be decreased by 80 (to stay between 0-79)
				passedStart(user); //We use this function to display the required messages
			}

			system("pause");
			system("cls");

			cout << "===============================================================================" << endl << endl;
			cout << setw(50) << "Your current location ==> " << currentLocation << endl;

			if (currentLocation != 0) { //If the user is not at the starting point
				mustPay = placeList[currentLocation].getPlaceCost(); //The price to pay is the price of that location


				//If the place doesn't have an owner (neither user or computer owns this place)
				if (placeList[currentLocation].getOwner() != 1 && placeList[currentLocation].getOwner() != 2) {
					cout << setw(50) << "This square is not owned! " << endl;
					cout << setw(50) << "The price of this location ==> " << mustPay << endl << endl;
					cout << "===============================================================================" << endl << endl;

					//The user would be given a choice to purchase the location or skip their turn
					while (errorLoopHolder == 0) {
						cout << "Please choose one of the following options: " << endl;
						cout << "1. Buy the property" << endl << "2. Skip my turn" << endl;
						cin >> choiceNum;

						switch (choiceNum) {
						case 1: //If the user chooses to buy the location
							errorLoopHolder = 1;
							cout << endl << "You have choosen to buy the property and pay " << mustPay << endl << endl;
							user->takeMoney(mustPay); //We decrease the required amount from the user's balance
							placeList[currentLocation].setOwner(1); //We set the user as the owner of this location
							system("pause");
							showinfo(user, computer);
							break;
						case 2:
							errorLoopHolder = 1;
							cout << endl << "You have choosen to skip your turn! " << endl << endl;
							//No actions need to be taken here. just break the loop and continue
							break;

						default: //Invalid input
							cout << "Sorry this option is unavailable! Please try again!" << endl << endl;
						}
					}
				}

				//If the place is already purchased by the user
				else if (placeList[currentLocation].getOwner() == 1) {
					cout << setw(50) << "You own this square" << endl;
					cout << setw(50) << "The price of this location ==> " << mustPay << endl << endl;
					cout << "===============================================================================" << endl << endl;

					//The user would be given a choice to invest in the location or skip their turn
					while (errorLoopHolder == 0) {
						cout << "Please choose one of the following options: " << endl;
						cout << "1. Invest in the property" << endl << "2. Skip my turn" << endl;
						cin >> choiceNum;

						switch (choiceNum) {
						case 1:
							errorLoopHolder = 1;
							cout << endl << "You have choosen to Invest and pay " << (double)mustPay / 2 << endl << endl;
							user->takeMoney((double)mustPay / 2); //To invest, the user has to pay half of the price of that square
							placeList[currentLocation].setInvested(1); //And then that place is to be invested by the user
							system("pause");
							showinfo(user, computer);
							break;
						case 2:
							errorLoopHolder = 1;
							cout << endl << "You have choosen to skip your turn! " << endl << endl;
							//No actions need to be taken here. just break the loop and continue
							break;

						default: //Invalid input
							cout << "Sorry this option is unavailable! Please try again!" << endl << endl;
						}
					}
				}

				//In case the user is in a place purchased by the computer AND none of the adjacent squares are purchased by the computer

				else if (placeList[currentLocation - 1].getOwner() != 2 && placeList[currentLocation + 1].getOwner() != 2) {
					cout << setw(50) << "Your opponent doesn't own any of the adjacent squares! " << endl;
					if (placeList[currentLocation].getInvester() == 2) { //In case the computer has invested in this location
						cout << setw(50) << "Your opponent has invested in this square! " << endl;
						cout << setw(50) << "You are fined with 15% of this square's price! " << endl;
						user->takeMoney((double)placeList[currentLocation].getPlaceCost() * 15 / 100); //The fine is 15%
					}
					else { //In case the computer hasn't invested in this location
						cout << setw(50) << "You are fined with 10% of this square's price! " << endl;
						user->takeMoney((double)placeList[currentLocation].getPlaceCost() / 10); //The fine is 10%
					}
					cout << "===============================================================================" << endl << endl;

				}



				//In case the user is in a place purchased by the computer AND one of the adjacent squares are purchased by the computer

				else if (placeList[currentLocation - 1].getOwner() != 2 && placeList[currentLocation + 1].getOwner() == 2) {

					cout << setw(50) << "Your opponent owns one of the adjacent squares! " << endl;
					if (placeList[currentLocation].getInvester() == 2) { //In case the computer has invested in this location
						cout << setw(50) << "Your opponent has invested in this square! " << endl;
						cout << setw(50) << "You are fined with 20% of this square's price! " << endl;
						user->takeMoney((double)placeList[currentLocation].getPlaceCost() / 5); //The fine is 20%
					}
					else { //In case the computer hasn't invested in this location
						cout << setw(50) << "You are fined with 15% of this square's price! " << endl;
						user->takeMoney((double)placeList[currentLocation].getPlaceCost() * 15 / 100); //The fine is 15%
					}
					cout << "===============================================================================" << endl << endl;

				}


				//In case the user is in a place purchased by the computer AND one of the adjacent squares are purchased by the computer

				else if (placeList[currentLocation - 1].getOwner() == 2 && placeList[currentLocation + 1].getOwner() != 2) {
					cout << setw(50) << "Your opponent owns one of the adjacent squares! " << endl;
					if (placeList[currentLocation].getInvester() == 2) { //In case the computer has invested in this location
						cout << setw(50) << "Your opponent has invested in this square! " << endl;
						cout << setw(50) << "You are fined with 20% of this square's price! " << endl;
						user->takeMoney((double)placeList[currentLocation].getPlaceCost() / 5); //The fine is 20%
					}
					else { //In case the computer hasn't invested in this location
						cout << setw(50) << "You are fined with 15% of this square's price! " << endl;
						user->takeMoney((double)placeList[currentLocation].getPlaceCost() * 15 / 100); //The fine is 15%
					}
					cout << "===============================================================================" << endl << endl;
				}



				//In case the user is in a place purchased by the computer AND both of the adjacent squares are purchased by the computer

				else if (placeList[currentLocation - 1].getOwner() == 2 && placeList[currentLocation + 1].getOwner() == 2) {
					cout << setw(50) << "Your opponent owns both of the adjacent squares! " << endl;
					if (placeList[currentLocation].getInvester() == 2) { //In case the computer has invested in this location
						cout << setw(50) << "Your opponent has invested in this square! " << endl;
						cout << setw(50) << "You are fined with 25% of this square's price! " << endl;
						user->takeMoney((double)placeList[currentLocation].getPlaceCost() / 4); //The fine is 25%
					}
					else { //In case the computer hasn't invested in this location
						cout << setw(50) << "You are fined with 20% of this square's price! " << endl;
						user->takeMoney((double)placeList[currentLocation].getPlaceCost() / 5); //The fine is 20%
					}
					cout << "===============================================================================" << endl << endl;

				}
			}

			//If none of the above cases apply to the user, the user must be at the starting point
			else { 
				cout << endl << "you are at the starting point! " << endl << endl;
				cout << "===============================================================================" << endl << endl;
			}

		}
		system("pause");
		
		//We check whether the user's balance has passed 0.
		if (user->getBalance() <= 0) { //In case the user's balance is 0 or less
			cout << endl << "You have lost the game!" << endl;
			cout << "Thank you for playing my game!" << endl;
			menuLoopHolder = 1; //We finish the game
			break;
			system("pause");
		}
		
		//If the user's balance is still higher than 0
		ourBoardGame.showBoardgame(user->getLocation()); //To show the user's location on the map
		system("pause");
		system("cls");
		showinfo(user, computer);
		cout << "It's your opponent's turn!" << endl;
		system("pause");


		system("cls");
		diceNum = rollDice(); //This rolls the dice
		showDice(diceNum); //This showed the number that the dice shows
		computer->move(diceNum); //The computer moves on the map according to the number of dice
		currentLocation = computer->getLocation(); //We store computer's current location in the variable currentLocation

		//We check whether the computer has passed the starting point or not
		if (currentLocation > 79) { //If they have,
			currentLocation = currentLocation - 80; //Their location would be decreased by 80 (to keep it between 0-79)
			passedStart(computer);
		}

		system("pause");


		system("cls");
		mustPay = placeList[currentLocation].getPlaceCost(); //The price to pay is the price of that location
		cout << "===============================================================================" << endl << endl;
		cout << setw(50) << "Your opponent's current location ==> " << currentLocation << endl;
		cout << setw(50) << "The price of this location ==> " << mustPay << endl << endl;
		cout << "===============================================================================" << endl << endl;
		if (currentLocation != 0) { //If the computer is not at the starting point

			//If the location is not owned by either user or computer
			if (placeList[currentLocation].getOwner() != 1 && placeList[currentLocation].getOwner() != 2) {
				//The computer would purchase the location
				cout << endl << "The computer has choosen to buy the property and pay " << mustPay << endl << endl;
				computer->takeMoney(mustPay); //Decrease the required amount from the balance
				placeList[currentLocation].setOwner(2); //Set computer as the owner of this location
				system("pause");
				ourBoardGame.showBoardgame(computer->getLocation()); //Show computer's place on the map
				system("pause");
				showinfo(user, computer);

			}


			//In case the computer already owns this location

			else if (placeList[currentLocation].getOwner() == 2) {
				cout << setw(50) << "The computer owns this square" << endl;
				cout << setw(50) << "The price of this location ==> " << mustPay << endl << endl;
				cout << "===============================================================================" << endl << endl;
				cout << endl << "The computer has choosen to Invest and pay " << (double)mustPay / 2 << endl << endl;
				computer->takeMoney((double)mustPay / 2); //The computer would invest in this location
				placeList[currentLocation].setInvested(2);
				system("pause");
				ourBoardGame.showBoardgame(computer->getLocation());
				system("pause");
				showinfo(user, computer);
				
			}

			//In case the location is owned by the user and none of the adjacent squares are purchased by the user

			else if (placeList[currentLocation - 1].getOwner() != 1 && placeList[currentLocation + 1].getOwner() != 1) {
				cout << setw(50) << "You don't own any of the adjacent squares! " << endl;
				if (placeList[currentLocation].getInvester() == 1) { //If the user has invested in this location
					cout << setw(50) << "You had invested in this square! " << endl;
					cout << setw(50) << "The computer is fined with 15% of this square's price! " << endl;
					computer->takeMoney((double)placeList[currentLocation].getPlaceCost() * 15 / 100); //The fine would be 15%
				}
				else {	//In case the user hadn't invested in this location
					cout << "Attention ==> The computer is fined with 10% of this square's price! " << endl;
					computer->takeMoney((double)placeList[currentLocation].getPlaceCost() / 10); //The fine would be 10%
				}
				cout << "===============================================================================" << endl << endl;

			}

			//In case the location is owned by the user and one of the adjacent squares are purchased by the user

			else if (placeList[currentLocation - 1].getOwner() != 1 && placeList[currentLocation + 1].getOwner() == 1) {

				cout << setw(50) << "You own one of the adjacent squares! " << endl;
				if (placeList[currentLocation].getInvester() == 1) { //If the user has invested in this location
					cout << setw(50) << "You have invested in this square! " << endl;
					cout << setw(50) << "The computer fined with 20% of this square's price! " << endl;
					computer->takeMoney((double)placeList[currentLocation].getPlaceCost() / 5); //The fine would be 20%
				}
				else { //In case the user hadn't invested in this location
					cout << setw(50) << "The computer is fined with 15% of this square's price! " << endl;
					computer->takeMoney((double)placeList[currentLocation].getPlaceCost() * 15 / 100); //The fine would be 15%
				}
				cout << "===============================================================================" << endl << endl;

			}

			//In case the location is owned by the user and one of the adjacent squares are purchased by the user

			else if (placeList[currentLocation - 1].getOwner() == 1 && placeList[currentLocation + 1].getOwner() != 1) {
				cout << setw(50) << "You own one of the adjacent squares! " << endl;
				if (placeList[currentLocation].getInvester() == 1) { //If the user has invested in this location
					cout << setw(50) << "You have invested in this square! " << endl;
					cout << setw(50) << "The computer fined with 20% of this square's price! " << endl;
					computer->takeMoney((double)placeList[currentLocation].getPlaceCost() / 5); //The fine would be 20%
				}
				else { //In case the user hadn't invested in this location
					cout << setw(50) << "The computer is fined with 15% of this square's price! " << endl;
					computer->takeMoney((double)placeList[currentLocation].getPlaceCost() * 15 / 100); //The fine would be 15%
				}
				cout << "===============================================================================" << endl << endl;
			}

			//In case the location is owned by the user and both of the adjacent squares are purchased by the user

			else if (placeList[currentLocation - 1].getOwner() == 1 && placeList[currentLocation + 1].getOwner() == 1) {
				cout << setw(50) << "You own both of the adjacent squares! " << endl;
				if (placeList[currentLocation].getInvester() == 1) { //If the user has invested in this location
					cout << setw(50) << "You had invested in this square! " << endl;
					cout << setw(50) << "The computer is fined with 25% of this square's price! " << endl;
					computer->takeMoney((double)placeList[currentLocation].getPlaceCost() / 4); //The fine would be 25%
				}
				else { //In case the user hadn't invested in this location
					cout << setw(50) << "The computer is  fined with 20% of this square's price! " << endl;
					computer->takeMoney((double)placeList[currentLocation].getPlaceCost() / 5); //The fine would be 20%
				}
				cout << "===============================================================================" << endl << endl;

			}
		}
		
		//If none of the above cases apply to the user, the computer must be at the starting point
		else { 
			cout << endl << "The computer is at the starting point! " << endl << endl;
			cout << "===============================================================================" << endl << endl;
		}

		system("pause");

		//Before finishing the computer's turn
		//We should check whether the computer can still continue playing (balance>0)
		computer->takeMoney(10000);
		if (computer->getBalance() <= 0) { //In case the balance is equal or less than zero
			cout << endl << "You have won the game!" << endl;
			cout << "Thank you for playing my game!" << endl;
			menuLoopHolder = 1; //We finish the game!
			break;
			system("pause");
		}

		rounds++; //A round has finished
		

	}
	
	

	return 0;
}