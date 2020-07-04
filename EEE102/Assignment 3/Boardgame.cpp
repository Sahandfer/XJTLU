#include "Boardgame.h"

boardgame::boardgame() {
	//The constructor is empty. Because this object has no attributes and is only used to access the function below.
}

void boardgame::showBoardgame(int location) {
	system("cls");
	int currentLocation; //A variable to temporarily hold the value of the given location
	currentLocation = location; 
	cout << "===============================================================================" << endl << endl;
	cout << "Note ==> This is the Gameboard! The place of the player on the gameboard is shown with XX." << endl << endl;
	cout << "===============================================================================" << endl << endl;
	
	//First, we print out the upper 20 squares

	//This for loop is to display the upper line
	//the reason we need 101 of these is 1 space(beginning line) + 20x4 spaces (for entries) + 20x1 spaces (for ending lines)= 101
	for (int i = 0; i < 101; i++) { 
		cout << "-";
	}
	cout << endl;

	cout << "|"; //This is the beginning line (previously mentioned)


	for (int column = 0; column < 20; column++) { //We have 20 columns 
		
	//The number of each column is 21+column number

		if (currentLocation == 21 + column) { //If this number is equal to the location of the player
			cout << " XX "; //We print this
		}
		else { //If the player is not in this column
			cout << "    "; //We print this 
		}
		cout << "|"; //This is the ending line (previously mentioned)
	}
	cout << endl;


	cout << "|"; //This is the beginning line for the second row of entries

	//This for loop is too display the number corresponding to each square
	for (int i = 0; i < 20; i++) {
		cout << " " << i + 21 << " ";
		cout << "|";
	}
	cout << endl;

	//This for loop is to display the lower line
	for (int i = 0; i < 101; i++) { //The reason for why here is 101 is previously explained
		cout << "-";
	}
	cout << endl;

	//The end of the upper 20 squares



	//Here is for printing the 20 squares in the middle (on each side)

		for (int row = 0; row < 20; row++) { //We have 20 rows 
			if (currentLocation==20-row) { //The number of the columns on the left is equal to 20 - the row number
				cout << "| XX |"; //In case the location equals the number of that column, we print this
			}
			else {
				cout << "|    |"; //In case the player is not in this location, we print this
			}
			
			//This is for printing out the empty space that exist in the middle 
			//We print 89 squares because two of the squares should be printed (2x6 spaces) and 
			//We previously used 101 spaces in total so 101-12=89

			for (int i = 0; i < 89; i++) {
					cout << " "; 
			}

			if (currentLocation == 41+row) { //The number for the columns on the right equals row number + 41
				cout << "| XX |"; //In case the location equals the number of that column, we print this
			}
			else {
				cout << "|    |"; //In case the player is not in this location, we print this
			}
			

			cout << endl;

			//This part is for displaying the number corresponding to each square

			if (20 - row >= 10) { //Since numbers less than take one less space, we need to add that space so that the table looks good
				cout << "| " << 20 - row << " |";
			}
			else {
				cout << "| 0" << 20 - row << " |";
			}

			//This is for printing out the empty space that exist in the middle 
			for (int i = 0; i < 89; i++) {
				cout << " ";
			}

			cout << "| " << 41+row << " |";
			cout << endl;
			
			//Without this part we would have an extra boundary between the middle squares and the lower squares
			if (20 - row != 1) { 
				cout << "------";
			}

			for (int i = 0; i < 89; i++) {
				if (20 - row != 1) {
					cout << " ";
				}
			}
			if (20 - row != 1) {
				cout << "------";
			}
			else { //In case we are printing the last row, we should print out a whole line instead of just a line under the two squares
				for (int i = 0; i < 101; i++) {
					cout << "-";
				}
			}
			cout << endl;

		}
	//This is the end of displaying the middle 20 squares



	//From here we start printing the lower 20 sqaures
		if (currentLocation == 0) { //This is because we want the lower squares to differ in 1 unit
			currentLocation = 80;
		}

		cout << "|"; //This is the beginning line (previously explained)

		for (int column = 0; column < 20; column++) { //We have 20 columns here

			if (currentLocation == 80 - column) { //If the player is in this column
				cout << " XX "; //We print this
			}
			else { //If the player is not in this column
				cout << "    "; //We print this
			}
			cout << "|"; //This is the ending line (previously explained)
		}
		cout << endl;


		cout << "| 00 "; //Since zero is different than the other numbers we first print it seperately
		cout << "|";

		//This for loop is for printing the number corresponding to each square
		for (int i = 1; i < 20; i++) {
			cout << " " << 80-i << " ";
			cout << "|";
		}
		cout << endl;

		//This is for displaying the lower line
	for (int i = 0; i < 101; i++) {
		cout << "-";
	}
	cout << endl;

	//This is the end of displaying the lower 20 squares



}