#include "keeper.h"
#include "customer.h"
#include <iostream>
#include <array>
#include <sstream>
#include <vector>
#include <algorithm>

void display(user *User) { //A method to show user's information
	cout << endl << "===================================================================" << endl;
	cout << "+ Number of goods in the Big Warehouse #1: " << User->BW1cargoOwned.size() << endl;
	cout << "+ Number of goods in the Big Warehouse #2: " << User->BW2cargoOwned.size() << endl;
	cout << "+ Number of goods in the Small Warehouse #1: " << User->SW1cargoOwned.size() << endl;
	cout << "+ Number of goods in the Small Warehouse #2: " << User->SW2cargoOwned.size() << endl;
	cout << "+ Number of goods in the Small Warehouse #3: " << User->SW3cargoOwned.size() << endl;
	cout << "+ Number of goods in the Small Warehouse #4: " << User->SW4cargoOwned.size() << endl << endl;
	cout << "- The debt for this user to be paid is ==>" << User->getDebt() << endl;
	cout << "===================================================================" << endl << endl;
}

int warehouseSelector() { //A method to ask the user about which warehouse they want to work with
	cout << endl << "===================================================================" << endl;
	cout << "Select a warehouse (enter a number from 1-6)" << endl;
	cout << "1. Big Warehouse #1			2. Big Warehouse #2" << endl;
	cout << "3. Small Warehouse #1			4. Small Warehouse #2" << endl;
	cout << "5. Small Warehouse #3			6. Small Warehouse #4" << endl;
	int errorLoopHolder = 0;
	int option;

	while (errorLoopHolder == 0) {
		cin >> option;
		if (option == 1 || option == 2 || option == 3 || option == 4 || option == 5 || option == 6) {
			errorLoopHolder = 1;
			return option;
		}


		else {
			cout << "Invalid input! Please try again!" << endl;
		}
	}
}

int cargoSelector(int warehouseSize) {

	int errorLoopHolder = 0;
	int option;

	if (warehouseSize == 1) {
		cout << endl << "===================================================================" << endl;
		cout << "Select a cargo (enter a number from 1-500)" << endl;
		while (errorLoopHolder == 0) {
			cin >> option;
			if (option <= 500 && option >= 1) {
				return option - 1;
			}
			else {
				cout << "Invalid input! Try again!" << endl;
			}
		}
		cout << "===================================================================" << endl;
	}
	else {
		cout << endl << "===================================================================" << endl;
		cout << "Select a cargo (enter a number from 1-400)" << endl;
		while (errorLoopHolder == 0) {
			cin >> option;
			if (option <= 400 && option >= 1) {
				return option - 1;
			}
			else {
				cout << "Invalid input! Try again!" << endl;
			}
		}
		cout << "===================================================================" << endl;
	}


}


int changeSelector() {
	int errorLoopHolder = 0;
	int option;

	while (errorLoopHolder == 0) {
		cout << "What do you want to modify?" << endl;
		cout << "1. The Owner's name" << endl;
		cout << "2. The price for this cargo" << endl;
		cout << "3. The cargo's size" << endl;
		cout << "4. Delete this cargo" << endl;

		cin >> option;

		if (option == 1 || option == 2 || option == 3 || option == 4) {
			errorLoopHolder = 1;
			return option;
		}

		else {
			cout << "Invalid input! Please try again!" << endl;
		}
	}
}


int main()
{
	string tempName; //To store a value for the username
	double tempNum; //To temporarily hold the numbers
	bool isCInput = false; //To check whether the input for the menu is valid or invalid
	bool isSaved = false; //To check whether the user's info is saved or not
	char option; //To be used as the user's choice in the menu
	char choice; //To give a user a choice in some menus
	char choiceInt=0; //To give a user a choice in some menus
	user *User; //We create an instance of the user object to represent the user
	int menuLoopHolder = 0; //A variable to keep the loop for the menu going
	int errorLoopHolder = 0; //A variable to keep the loop for checking errors going (the loop will go as long as there is invalid input)
	int warehouseNum = 0; //An integer variable that shows which warehouse the user has chosen to work with
	int cargoNum = 0; //An integer variable that shows which cargo the user has chosen to work with
	int changeNum = 0; //An integer variable that shows which change the user has chosen to apply
	int ownedNum = 0;
	int deletedNum = 0;
	vector <int> tempVec; //A temporary vector to store the indexex for each warehouse
	vector <int> resetVec; //A vector to reset the tempVec into empty state



						   //The following six variables are to show the index of the cargo until which the warehouse is full 
	int BW1num = 0;
	int BW2num = 0;
	int SW1num = 0;
	int SW2num = 0;
	int SW3num = 0;
	int SW4num = 0;

	warehouse BWO1(1); //An object to represent the first big warehouse
	warehouse BWO2(1); //An object to represent the second big warehouse
	warehouse SWO1(2); //An object to represent the first small warehouse
	warehouse SWO2(2); //An object to represent the second small warehouse
	warehouse SWO3(2); //An object to represent the third small warehouse
	warehouse SWO4(2); //An object to represent the fourth small warehouse

	while (menuLoopHolder == 0) {

		cout << "Please enter your name: " << endl;

		getline(cin >> ws, tempName);

		User = new keeper(tempName);
		User->cargoCreater();
		for (int i = 1; i < 7; i++) 
		{
			User->cargo_dataLoad(i);
		}
		isSaved = User->user_dataLoad();
		/*cout << "isSaved: "<<isSaved<<endl;
		cout << "ID: " << ID << endl;*/

		if (isSaved && ID==0) 
		{ //In case the user is a keeper
			User->cargoCreater();
			cout << "Warehouse and cargos has been created successfully" << endl;
			User->user_dataLoad();
			cout << "Users data has been loaded successfully" << endl;
			for (int i = 1; i < 7; i++)
			{
				User->cargo_dataLoad(i);
				cout << "Warehouses data has been loaded " << i << "/6" << endl;
			}
			cout << "Warehouses data has been loaded successfully" << endl;
			cout << tempName << " has been logged in as a keeper successfully!" << endl;
			cout << endl << "===================================================================" << endl;
			system("pause");
			system("cls");
			do
			{
				User->user_dataLoad();
				for(int i=1;i<7;i++)
					User->cargo_dataLoad(i);
				cout << endl << "===================================================================" << endl;
				cout << "Please choose the option below:" << endl;
				cout << "1. Edit Information" << endl;
				cout << "2. Log out" << endl;

				cin >> option;
				cout << "===================================================================" << endl;
				switch (option)
				{
				case '1':
					warehouseNum = warehouseSelector();

					switch (warehouseNum) 
					{
					case 1:

						cargoNum = cargoSelector(1);
						system("pause");
						system("cls");
						cout << "===================================================================" << endl;
						cout << "+ SELECTED CARGO ===> " << cargoNum + 1 << endl;
						User->BW1[cargoNum].display();
						cout << "===================================================================" << endl;
						changeNum = changeSelector();
						switch(changeNum) 
						{
						case 1:
							cout << "What do you want to change the owner's name to: " << endl;
							cin >> tempName;
							User->BW1[cargoNum].setOwner(tempName);
							User->cargo_dataWrite(1,cargoNum+1,tempName,20,1);
							User->user_dataWrite();
							break;
						case 2:
							cout << "What price do you want to change the cargo's price to: " << endl;
							cin >> tempNum;
							User->BW1[cargoNum].setPrice(tempNum);
							User->cargo_dataWrite(1, cargoNum + 1, tempName, tempNum,1);
							User->user_dataWrite();
							break;
						case 3:
							cout << "What size do you want to change the cargo's size to: " << endl;
							cout << "1. Standard			2.Small " << endl;
							errorLoopHolder = 0;
							while (errorLoopHolder == 0) 
							{
								cin >> choiceInt;
								if (choice != 1 && choice != 2) {
									cout << "Invalid option! try again" << endl;
								}
								else {
									errorLoopHolder = 1;
								}

							}
							User->BW1[cargoNum].setSize(choiceInt);
							User->cargo_dataWrite(1, cargoNum + 1, tempName, 20,choiceInt);
							User->user_dataWrite();
							break;
						case 4:
							cout << "You have chosen to delete this cargo!" << endl;
							User->BW1[cargoNum].setOwner("NoName");
							User->BW1[cargoNum].setPrice(20);
							User->BW1[cargoNum].setEmpty(true);
							User->BW1[cargoNum].setSize(1);
							BWO1.empty(1);
							User->cargo_dataWrite(1, cargoNum + 1, "NoNAME", 20, 1);
							User->user_dataWrite();
							break;
						default:
							cout << "Something went wrong!" << endl;
						}
						break;



					case 2:
						cargoNum = cargoSelector(1);
						system("pause");
						system("cls");
						cout << "===================================================================" << endl;
						cout << "+ SELECTED CARGO ===> " << cargoNum;
						User->BW2[cargoNum].display();
						cout << "===================================================================" << endl;
						changeNum = changeSelector();
						switch (changeNum) {
						case 1:
							cout << "What do you want to change the owner's name to: " << endl;
							getline(cin >> ws, tempName);
							User->BW2[cargoNum].setOwner(tempName);
							User->cargo_dataWrite(2, cargoNum + 1, tempName, 20, 1);
							User->user_dataWrite();
							break;
						case 2:
							cout << "What price do you want to change the cargo's price to: " << endl;
							cin >> tempNum;
							User->BW2[cargoNum].setPrice(tempNum);
							User->cargo_dataWrite(2, cargoNum + 1, tempName, tempNum, 1);
							User->user_dataWrite();
							break;
						case 3:
							cout << "What size do you want to change the cargo's size to: " << endl;
							cout << "1. Standard			2.Small " << endl;
							errorLoopHolder = 0;
							while (errorLoopHolder == 0) {
								cin >> choice;
								if (choiceInt != 1 && choiceInt != 2) {
									cout << "Invalid option! try again" << endl;
								}
								else {
									errorLoopHolder = 1;
								}

							}

							User->BW2[cargoNum].setSize(choiceInt);
							User->cargo_dataWrite(2, cargoNum + 1, tempName, 20, choiceInt);
							User->user_dataWrite();
							break;
						case 4:
							cout << "You have chosen to delete this cargo!" << endl;
							User->BW2[cargoNum].setOwner("NoName");
							User->BW2[cargoNum].setPrice(20);
							User->BW2[cargoNum].setEmpty(true);
							User->BW2[cargoNum].setSize(1);
							BWO2.empty(1);
							User->cargo_dataWrite(2, cargoNum + 1, "NoNAME", 20, 1);
							User->user_dataWrite();
							break;
						default:
							cout << "Something went wrong!" << endl;
						}
						break;


					case 3:
						cargoNum = cargoSelector(2);
						system("pause");
						system("cls");
						cout << "===================================================================" << endl;
						cout << "+ SELECTED CARGO ===> " << cargoNum;
						User->SW1[cargoNum].display();
						cout << "===================================================================" << endl;

						changeNum = changeSelector();

						switch (changeNum) {
						case 1:
							cout << "What do you want to change the owner's name to: " << endl;
							getline(cin >> ws, tempName);
							User->SW1[cargoNum].setOwner(tempName);
							User->cargo_dataWrite(3, cargoNum + 1, tempName, 10, 2);
							User->user_dataWrite();
							break;
						case 2:
							cout << "What price do you want to change the cargo's price to: " << endl;
							cin >> tempNum;
							User->SW1[cargoNum].setPrice(tempNum);
							User->cargo_dataWrite(3, cargoNum + 1, tempName, tempNum, 2);
							User->user_dataWrite();
							break;
						case 3:
							cout << "What size do you want to change the cargo's size to: " << endl;
							cout << "1. Standard			2.Small " << endl;
							errorLoopHolder = 0;
							while (errorLoopHolder == 0) {
								cin >> choiceInt;
								if (choiceInt != 1 && choiceInt != 2) {
									cout << "Invalid option! try again" << endl;
								}
								else {
									errorLoopHolder = 1;
								}

							}

							User->BW1[cargoNum].setSize(choiceInt);
							User->cargo_dataWrite(3, cargoNum + 1, tempName, 10, choiceInt);
							User->user_dataWrite();
							break;

						case 4:
							cout << "You have chosen to delete this cargo!" << endl;
							User->SW1[cargoNum].setOwner("NoName");
							User->SW1[cargoNum].setPrice(20);
							User->SW1[cargoNum].setEmpty(true);
							User->SW1[cargoNum].setSize(1);
							User->cargo_dataWrite(3, cargoNum + 1, "NoNAME", 10, 2);
							User->user_dataWrite();
							SWO1.empty(1);
							break;
						default:
							cout << "Something went wrong!" << endl;
						}

						break;




					case 4:
						cargoNum = cargoSelector(2);
						system("pause");
						system("cls");
						cout << "===================================================================" << endl;
						cout << "+ SELECTED CARGO ===> " << cargoNum;
						User->SW2[cargoNum].display();
						cout << "===================================================================" << endl;
						changeNum = changeSelector();
						switch (changeNum) {
						case 1:
							cout << "What do you want to change the owner's name to: " << endl;
							getline(cin >> ws, tempName);
							User->SW2[cargoNum].setOwner(tempName);
							User->cargo_dataWrite(4, cargoNum + 1, tempName, 10, 2);
							User->user_dataWrite();
							break;
						case 2:
							cout << "What price do you want to change the cargo's price to: " << endl;
							cin >> tempNum;
							User->SW2[cargoNum].setPrice(tempNum);
							User->cargo_dataWrite(4, cargoNum + 1, tempName, tempNum, 2);
							User->user_dataWrite();
							break;
						case 3:
							cout << "What size do you want to change the cargo's size to: " << endl;
							cout << "1. Standard			2.Small " << endl;
							errorLoopHolder = 0;
							while (errorLoopHolder == 0) {
								cin >> choiceInt;
								if (choiceInt != 1 && choiceInt != 2) {
									cout << "Invalid option! try again" << endl;
								}
								else {
									errorLoopHolder = 1;
								}

							}

							User->BW1[cargoNum].setSize(choiceInt);
							User->cargo_dataWrite(4, cargoNum + 1, tempName, 10, choiceInt);
							User->user_dataWrite();
							break;
						case 4:
							cout << "You have chosen to delete this cargo!" << endl;
							User->SW2[cargoNum].setOwner("NoName");
							User->SW2[cargoNum].setPrice(20);
							User->SW2[cargoNum].setEmpty(true);
							User->SW2[cargoNum].setSize(1);
							SWO2.empty(1);
							User->cargo_dataWrite(4, cargoNum + 1, "NoNAME", 10, 2);
							User->user_dataWrite();
							break;
						default:
							cout << "Something went wrong!" << endl;
						}
						break;



					case 5:
						cargoNum = cargoSelector(2);
						system("pause");
						system("cls");
						cout << "===================================================================" << endl;
						cout << "+ SELECTED CARGO ===> " << cargoNum;
						User->SW3[cargoNum].display();
						cout << "===================================================================" << endl;
						changeNum = changeSelector();
						switch (changeNum) {
						case 1:
							cout << "What do you want to change the owner's name to: " << endl;
							getline(cin >> ws, tempName);
							User->SW3[cargoNum].setOwner(tempName);
							User->cargo_dataWrite(5, cargoNum + 1, tempName, 10, 2);
							User->user_dataWrite();
							break;
						case 2:
							cout << "What price do you want to change the cargo's price to: " << endl;
							cin >> tempNum;
							User->SW3[cargoNum].setPrice(tempNum);
							User->cargo_dataWrite(5, cargoNum + 1, tempName, tempNum, 2);
							User->user_dataWrite();
							break;
						case 3:
							cout << "What size do you want to change the cargo's size to: " << endl;
							cout << "1. Standard			2.Small " << endl;
							errorLoopHolder = 0;
							while (errorLoopHolder == 0) {
								cin >> choiceInt;
								if (choiceInt != 1 && choiceInt != 2) {
									cout << "Invalid option! try again" << endl;
								}
								else {
									errorLoopHolder = 1;
								}

							}

							User->SW3[cargoNum].setSize(choiceInt);
							User->cargo_dataWrite(5, cargoNum + 1, tempName, 10, choiceInt);
							User->user_dataWrite();
							break;
						case 4:
							cout << "You have chosen to delete this cargo!" << endl;
							User->SW3[cargoNum].setOwner("NoName");
							User->SW3[cargoNum].setPrice(20);
							User->SW3[cargoNum].setEmpty(true);
							User->SW3[cargoNum].setSize(1);
							User->cargo_dataWrite(5, cargoNum + 1, "NoNAME", 10, 2);
							User->user_dataWrite();
							SWO3.empty(1);
							break;
						default:
							cout << "Something went wrong!" << endl;
						}
						break;



					case 6:
						cargoNum = cargoSelector(2);
						system("pause");
						system("cls");
						cout << "===================================================================" << endl;
						cout << "+ SELECTED CARGO ===> " << cargoNum;
						User->SW4[cargoNum].display();
						cout << "===================================================================" << endl;
						changeNum = changeSelector();
						switch (changeNum) {
						case 1:
							cout << "What do you want to change the owner's name to: " << endl;
							getline(cin >> ws, tempName);
							User->SW4[cargoNum].setOwner(tempName);
							User->cargo_dataWrite(6, cargoNum + 1, tempName, 10, 2);
							User->user_dataWrite();
							break;
						case 2:
							cout << "What price do you want to change the cargo's price to: " << endl;
							cin >> tempNum;
							User->SW4[cargoNum].setPrice(tempNum);
							User->cargo_dataWrite(6, cargoNum + 1, tempName, tempNum, 2);
							User->user_dataWrite();
							break;
						case 3:
							cout << "What size do you want to change the cargo's size to: " << endl;
							cout << "1. Standard			2.Small " << endl;
							errorLoopHolder = 0;
							while (errorLoopHolder == 0) {
								cin >> choice;
								if (choiceInt != 1 && choiceInt != 2) {
									cout << "Invalid option! try again" << endl;
								}
								else {
									errorLoopHolder = 1;
								}

							}

							User->SW4[cargoNum].setSize(choiceInt);
							User->cargo_dataWrite(6, cargoNum + 1, tempName, 10, choiceInt);
							User->user_dataWrite();
							break;
						case 4:
							cout << "You have chosen to delete this cargo!" << endl;
							User->SW4[cargoNum].setOwner("NoName");
							User->SW4[cargoNum].setPrice(20);
							User->SW4[cargoNum].setEmpty(true);
							User->SW4[cargoNum].setSize(1);
							User->cargo_dataWrite(6, cargoNum + 1, "NoNAME", 10, 2);
							User->user_dataWrite();
							SWO4.empty(1);
							break;
						default:
							cout << "Something went wrong!" << endl;
						}

						break;

					default:
						cout << "Something went wrong!" << endl;
					}

					errorLoopHolder = 0;
					cout << endl << "Do you want to continue? 1.Yes 2.No" << endl;
					while (errorLoopHolder == 0) {
						cin >> choice;
						if (choice == '1') {
							cout << "You have chosen to continue!" << endl << endl;
							system("pause");
							system("cls");
							errorLoopHolder = 1;
						}

						else if (choice == '2') {
							cout << "You have chosen to quit the program!" << endl << endl;
							isCInput = true;
							menuLoopHolder = 1;
							errorLoopHolder = 1;
							cout << "Thank you for using our program!" << endl;
						}

						else {
							cout << "Invalid input! Please try again!" << endl;
						}
					}

					break;
				case '2':


					errorLoopHolder = 0;
					cout << endl << "Are you sure you want to continue? 1.Yes 2.No" << endl;
					while (errorLoopHolder == 0) {
						cin >> choice;
						if (choice == '1') {
							cout << "You have logged out!" << endl << endl;
							errorLoopHolder = 1;
							isCInput = true;
						}

						else if (choice == '2') {
							cout << "You have chosen to continue!" << endl << endl;
							system("pause");
							system("cls");
							errorLoopHolder = 1;
							menuLoopHolder = 1;
						}

						else {
							cout << "Invalid input! Please try again!" << endl;
						}
					}
					break;
				default:
					cout << "Invalid input and please try again:" << endl;
					break;
				}
			} while (!isCInput);
			
		}

		if ((!isSaved)||(isSaved && ID==1)) //In case the user is a customer
		{
			User = new customer(tempName);
			User->cargoCreater();
			cout << "Warehouse and cargos has been created successfully" << endl;
			User->user_dataLoad();
			cout << "Users data has been loaded successfully" << endl;
			for (int i = 1; i < 7; i++)
			{
				User->cargo_dataLoad(i);
				cout << "Warehouses data has been loaded "<<i<<"/6" << endl;
			}
			cout << "Warehouses data has been loaded successfully" << endl;
			cout << tempName << " has been logged in as a customer successfully!" << endl;
			cout << endl << "===================================================================" << endl;
			system("pause");
			system("cls");
			do
			{
				User->user_dataLoad();
				for (int i = 1; i < 7; i++)
				{
					User->cargo_dataLoad(i);
				}
				cout << endl << "*****************************************************" << endl;
				cout << endl << "*       Welcome to use Warehouse Lease System       *" << endl;
				cout << endl << "*****************************************************" << endl;
				cout << endl << "===================================================================" << endl;
				cout << "Please choose the option below:" << endl;
				cout << "1. Search for goods stored already" << endl;
				cout << "2. Store goods" << endl;
				cout << "3. Take out goods" << endl;
				cout << "4. Log Out" << endl;
				cin >> option;
				cout << endl << "===================================================================" << endl;
				switch (option)
				{
				case '1':
					display(User);
					warehouseNum = warehouseSelector();

					switch (warehouseNum) {
						ownedNum = 0;
					case 1:
						cout << "Your cargos in this warehouse: " << endl;
						User->user_dataLoad();
						for (int i = 0; i < User->BW1cargoOwned.size(); i++)
						{
							cout << User->BW1cargoOwned[i]<<" ";
							ownedNum++;
						}
						cout << endl << "Total number of owned Cargos in this warehouse: " << User->BW1cargoOwned.size() << endl;
						cargoNum = cargoSelector(1);
						User->BW1[cargoNum].display();
						break;
					case 2:
						cout << "Your cargos in this warehouse: " << endl;
						for (int i = 0; i < User->BW2cargoOwned.size(); i++)
						{
							cout << User->BW2cargoOwned[i] << " ";
							ownedNum++;
						}
						cout << endl << "Total number of owned Cargos in this warehouse: " << User->BW2cargoOwned.size() << endl;
						cargoNum = cargoSelector(1);
						User->BW2[cargoNum].display();
						break;

					case 3:
						cout << "Your cargos in this warehouse: " << endl;
						for (int i = 0; i < User->SW1cargoOwned.size(); i++)
						{
							cout << User->SW1cargoOwned[i] << " ";
							ownedNum++;
						}
						cout << endl << "Total number of owned Cargos in this warehouse: " << User->SW1cargoOwned.size() << endl;
						cargoNum = cargoSelector(2);
						User->SW1[cargoNum].display();
						break;
					case 4:
						cout << "Your cargos in this warehouse: " << endl;
						for (int i = 0; i < User->SW2cargoOwned.size(); i++)
						{
							cout << User->SW2cargoOwned[i] << " ";
							ownedNum++;
						}
						cout << endl << "Total number of owned Cargos in this warehouse: " << User->SW2cargoOwned.size() << endl;
						cargoNum = cargoSelector(2);
						User->SW2[cargoNum].display();
						break;
					case 5:
						cout << "Your cargos in this warehouse: " << endl;
						for (int i = 0; i < User->SW3cargoOwned.size(); i++)
						{
							cout << User->SW3cargoOwned[i] << " ";
							ownedNum++;
						}
						cout << endl << "Total number of owned Cargos in this warehouse: " << User->SW3cargoOwned.size() << endl;
						cargoNum = cargoSelector(2);
						User->SW3[cargoNum].display();
						break;

					case 6:
						cout << "Your cargos in this warehouse: " << endl;
						for (int i = 0; i < User->SW4cargoOwned.size(); i++)
						{
							cout << User->SW4cargoOwned[i] << " ";
							ownedNum++;
						}
						cout << endl << "Total number of owned Cargos in this warehouse: " << User->SW4cargoOwned.size() << endl;
						cargoNum = cargoSelector(2);
						User->SW4[cargoNum].display();
						break;

					default:
						cout << "Something went wrong!" << endl;
					}
					errorLoopHolder = 0;
					while (errorLoopHolder == 0) 
					{
						cout << endl << "Do you want to continue? 1.Yes 2.No" << endl;
						cin >> choice;
						if (choice == '1') {
							cout << "You have chosen to continue!" << endl << endl;
							errorLoopHolder = 1;
							system("pause");
							system("cls");
							break;
						}

						else if (choice == '2') {
							cout << "You have chosen to quit the program!" << endl << endl;
							isCInput = true;
							errorLoopHolder = 1;
							menuLoopHolder = 1;
							cout << "Thank you for using our program!" << endl;
							break;
						}
						cout << "Invalid input! Please try again!" << endl;
					}
					break;

				case '2':
					display(User);
					{
						int numOfGoods = 0; //How many goods do they want to add
						int size = 0; //whether it's standard or small cargo
						errorLoopHolder = 0; //Reset the loop holder

						cout << "Please enter in the number of goods that you want to store: ";
						cin >> numOfGoods;

						cout << endl;

						cout << "What is the size of the goods?" << endl << "1.Standard" << endl << "2.Small" << endl;

						while (errorLoopHolder == 0) 
						{
							cin >> choice;
							if (choice == '1') 
							{
								for (int i = 0; i < numOfGoods; i++) 
								{
									if (BWO1.isEmpty() == true)
									{
										if (User->BW1[BW1num].isEmpty()) 
										{
											BWO1.fill(1);
											User->BW1[BW1num].setOwner(tempName);
											User->BW1[BW1num].setEmpty(false);
											User->BW1cargoOwned.push_back(BW1num + 1);
											User->increaseDebt(User->BW1[BW1num + 1].getPrice());
											User->cargo_dataWrite(1, BW1num + 1, tempName, User->BW1[BW1num + 1].getPrice(),1);
										}
										BW1num++;
									}
									else if (BWO1.isEmpty() == false && BWO2.isEmpty() == true) {
										if (User->BW2[BW2num].isEmpty()) 
										{
											BWO2.fill(1);
											User->BW2[BW2num].setOwner(tempName);
											User->BW2[BW2num].setEmpty(false);
											User->BW2cargoOwned.push_back(BW2num + 1);
											User->increaseDebt(User->BW2[BW2num + 1].getPrice());
											User->cargo_dataWrite(2, BW2num + 1, tempName, User->BW2[BW2num + 1].getPrice(),1);
										}
										BW2num++;
									}
									else if (BWO1.isEmpty() == false && BWO2.isEmpty() == false) {
										cout << "Sorry! We have run out of storage!" << endl;
										break;
									}

								}
								errorLoopHolder = 1;
							}

							else if (choice == '2') 
							{

								if (SWO1.isEmpty() == true) {
									if (User->SW1[SW1num].isEmpty()) 
									{
										SWO1.fill(1);
										User->SW1[SW1num].setOwner(tempName);
										User->SW1[SW1num].setEmpty(false);
										User->SW1cargoOwned.push_back(SW1num);
										User->increaseDebt(User->SW1[SW1num].getPrice());
										User->cargo_dataWrite(3, SW1num + 1, tempName, User->SW1[SW1num + 1].getPrice(),2);
									}
									SW1num++;
								}
								else if (SWO1.isEmpty() == false && SWO2.isEmpty() == true) 
								{
									if (User->SW2[SW2num].isEmpty()) 
									{
										SWO2.fill(1);
										User->SW2[SW2num].setOwner(tempName);
										User->SW2[SW2num].setEmpty(false);
										User->SW2cargoOwned.push_back(SW2num);
										User->increaseDebt(User->SW2[SW2num].getPrice());
										User->cargo_dataWrite(4, SW2num + 1, tempName, User->SW2[SW2num + 1].getPrice(),2);
									}
									SW2num++;
								}

								else if (SWO1.isEmpty() == false && SWO2.isEmpty() == false && SWO3.isEmpty() == true) {
									if (User->SW3[SW3num].isEmpty()) 
									{
										SWO3.fill(1);
										User->SW3[SW3num].setOwner(tempName);
										User->SW3[SW3num].setEmpty(false);
										User->SW3cargoOwned.push_back(SW3num);
										User->increaseDebt(User->SW3[SW3num].getPrice());
										User->cargo_dataWrite(5, SW3num + 1, tempName, User->SW3[SW1num + 1].getPrice(),2);
									}
									SW3num++;
								}

								else if (BWO1.isEmpty() == false && BWO2.isEmpty() == false && SWO3.isEmpty() == false && SWO4.isEmpty() == true) {
									if (User->SW4[SW4num].isEmpty())
									{
										SWO4.fill(1);
										User->SW4[SW4num].setOwner(tempName);
										User->SW4[SW4num].setEmpty(false);
										User->SW4cargoOwned.push_back(SW4num);
										User->increaseDebt(User->SW4[SW4num].getPrice());
										User->cargo_dataWrite(6, SW4num + 1, tempName, User->SW4[SW4num + 1].getPrice(),2);
										SW4num++;
									}
								}


								else if (BWO1.isEmpty() == false && BWO2.isEmpty() == false && SWO1.isEmpty() == false && SWO2.isEmpty() == false && SWO3.isEmpty() == false && SWO4.isEmpty() == false) {
									cout << "Sorry! We have run out of storage!" << endl;
									break;
								}

								errorLoopHolder = 1;
							}


							else {
								cout << "Invalid input! Please try again!" << endl;
							}
						}
						User->user_dataWrite();
						errorLoopHolder = 0;
						cout << endl << "Do you want to continue? 1.Yes 2.No" << endl;
						while (errorLoopHolder == 0) 
						{
							cin >> choice;
							if (choice == '1') 
							{
								cout << "You have chosen to continue!" << endl << endl;
								errorLoopHolder = 1;
								system("pause");
								system("cls");
								break;
							}

							else if (choice == '2') 
							{
								cout << "You have chosen to quit the program!" << endl << endl;
								isCInput = true;
								errorLoopHolder = 1;
								menuLoopHolder = 1;
								cout << "Thank you for using our program!" << endl;
								break;
							}

							else {
								cout << "Invalid input! Please try again!" << endl;
							}
						}
					}
					break;



				case '3':
					display(User);

					errorLoopHolder = 0;

					while (errorLoopHolder == 0) 
					{
						cout << "Please select one of the options" << endl;
						cout << "1. Take out a single cargo of goods" << endl;
						cout << "2. Take out a number of cargo of goods" << endl;
						cin >> choice;
						if (choice == '1') {
							errorLoopHolder = 1;
							warehouseNum = warehouseSelector();
							switch (warehouseNum) {
								//tempVec = resetVec;
							case 1:
								cargoNum = cargoSelector(1);
								User->BW1cargoOwned.clear();
								for (int i = 0; i < 500; i++) 
								{
									if (i == cargoNum && User->BW1[i].getOwner() == User->getName()) 
									{
										User->BW1[i].setEmpty(true);
										User->BW1[i].setOwner("NoNAME");
										User->BW1[i].setPrice(20);
										User->BW1[i].setSize(1);
										BWO1.empty(1);
										User->cargo_dataWrite(1,cargoNum+1,"NoNAME",20,1);
									}
									else if (i != cargoNum && User->BW1[i].getOwner() == User->getName()) {
										
										User->BW1cargoOwned.push_back(i+1);
									}
								}
								cout << "Cargo number " << cargoNum+1 << " of your cargos was taken out!" << endl;
								break;
							case 2:
								cargoNum = cargoSelector(1);
								User->BW2cargoOwned.clear();
								for (int i = 0; i < 500; i++) {

									if (i == cargoNum && User->BW2[i].getOwner() == User->getName()) {
										User->BW2[i].setEmpty(true);
										User->BW2[i].setOwner("NoNAME");
										User->BW2[i].setPrice(20);
										User->BW2[i].setSize(1);
										BWO2.empty(1);
										User->cargo_dataWrite(2, cargoNum+1, "NoName", 20,1);
									}
									else if (i != cargoNum && User->BW2[i].getOwner() == User->getName()) {
										User->BW2cargoOwned.push_back(i + 1);
									}

								}
								cout << "Cargo number " << cargoNum+1 << " of your cargos was taken out!" << endl;

								break;
							case 3:
								cargoNum = cargoSelector(2);
								User->SW1cargoOwned.clear();
								for (int i = 0; i < 500; i++) {

									if (i == cargoNum && User->SW1[i].getOwner() == User->getName()) {
										User->SW1[i].setEmpty(true);
										User->SW1[i].setOwner("NoName");
										User->SW1[i].setPrice(10);
										User->SW1[i].setSize(2);
										SWO1.empty(1);
										User->cargo_dataWrite(3, cargoNum+1, "NoName", 10,2);
									}
									else if (i != cargoNum && User->SW1[i].getOwner() == User->getName()) {
										User->SW1cargoOwned.push_back(i+1);
									}

								}
								cout << "Cargo number " << cargoNum+1 << " of your cargos was taken out!" << endl;
								break;
							case 4:
								cargoNum = cargoSelector(2);
								User->SW2cargoOwned.clear();
								for (int i = 0; i < 500; i++) {

									if (i == cargoNum && User->SW2[i].getOwner() == User->getName()) {
										User->SW2[i].setEmpty(true);
										User->SW2[i].setOwner("NoName");
										User->SW2[i].setPrice(10);
										User->SW2[i].setSize(2);
										SWO2.empty(1);
										User->cargo_dataWrite(4, cargoNum+1, "NoName", 10,2);
									}
									else if (i != cargoNum && User->SW2[i].getOwner() == User->getName()) {
										User->SW2cargoOwned.push_back(i+1);
									}

								}
								cout << "Cargo number " << cargoNum+1 << " of your cargos was taken out!" << endl;
								break;
							case 5:
								cargoNum = cargoSelector(2);
								User->SW3cargoOwned.clear();
								for (int i = 0; i < 500; i++) {

									if (i == cargoNum && User->SW3[i].getOwner() == User->getName()) {
										User->SW3[i].setEmpty(true);
										User->SW3[i].setOwner("NoName");
										User->SW3[i].setPrice(10);
										User->SW3[i].setSize(2);
										SWO3.empty(1);
										User->cargo_dataWrite(5, cargoNum+1, "NoName", 10,2);
									}
									else if (i != cargoNum && User->SW3[i].getOwner() == User->getName()) {
										User->SW3cargoOwned.push_back(i + 1);
									}

								}
								cout << "Cargo number " << cargoNum+1 << " of your cargos was taken out!" << endl;
								break;
							case 6:
								cargoNum = cargoSelector(2);
								User->SW4cargoOwned.clear();
								for (int i = 0; i < 500; i++) {

									if (i == cargoNum && User->SW4[i].getOwner() == User->getName()) {
										User->SW4[i].setEmpty(true);
										User->SW4[i].setOwner("NoName");
										User->SW4[i].setPrice(10);
										User->SW4[i].setSize(2);
										SWO4.empty(1);
										User->cargo_dataWrite(6, cargoNum+1, "NoName", 10,2);
									}
									else if (i != cargoNum && User->SW4[i].getOwner() == User->getName()) {tempVec.push_back(i+1);
									User->SW4cargoOwned.push_back(i+1);
									}

								}
								cout << "Cargo number " << cargoNum+1 << " of your cargos was taken out!" << endl;
								break;
							default:
								cout << "something went wrong!" << endl;
							}
						}

						else if (choice == '2') {
							errorLoopHolder = 1;
							warehouseNum = warehouseSelector();

							switch (warehouseNum) {
								ownedNum = 0;
							case 1:
								for (int i = 0; i < 500; i++) {
									if (User->BW1[i].getOwner() == User->getName()) 
									{
										ownedNum++;
									}
								}
								cout << endl << "Total number of owned Cargos in this warehouse: " << ownedNum << endl;

								//tempVec = resetVec;
								cout << "How many cargos do you wish to take out?" << endl;
								cin >> tempNum;
								if (tempNum >= ownedNum) 
								{
									cout << "The number you have chosen is more than the number of the cargos you own!" << endl;
									cout << "As a result we have taken out all of your owned cargos" << endl;
									for (int i = 0; i < 500; i++) 
									{
										if (User->BW1[i].getOwner() == User->getName()) 
										{
											User->BW1[i].setEmpty(true);
											User->BW1[i].setOwner("NoNAME");
											User->BW1[i].setPrice(20);
											User->BW1[i].setSize(1);
											BWO1.empty(1);
											User->cargo_dataWrite(1,i+1,"NoNAME",20,1);
										}
									}
									User->BW1cargoOwned.clear();
								}


								else {
									cout << tempNum << " of your cargos were taken out!" << endl;
									deletedNum = 0;
									User->BW1cargoOwned.clear();
									for (int i = 0; i < 500; i++) 
									{
										if (User->BW1[i].getOwner() == User->getName()) {
											if (deletedNum < tempNum) 
											{
												User->BW1[i].setEmpty(true);
												User->BW1[i].setOwner("NoNAME");
												User->BW1[i].setPrice(20);
												User->BW1[i].setSize(1);
												User->cargo_dataWrite(1,i+1,"NoNAME",20,1);
												deletedNum++;
												BWO1.empty(1);
											}
											else
											{
												User->BW1cargoOwned.push_back(i + 1);
											}
										}



									}

									system("pause");
									system("cls");
									display(User);
								}
								break;
							case 2:
								for (int i = 0; i < 500; i++) {
									if (User->BW2[i].getOwner() == User->getName())
									{
										ownedNum++;
									}
								}
								cout << endl << "Total number of owned Cargos in this warehouse: " << ownedNum << endl;

								//tempVec = resetVec;
								cout << "How many cargos do you wish to take out?" << endl;
								cin >> tempNum;
								if (tempNum > ownedNum)
								{
									cout << "The number you have chosen is more than the number of the cargos you own!" << endl;
									cout << "As a result we have taken out all of your owned cargos" << endl;
									for (int i = 0; i < 500; i++) {
										if (User->BW2[i].getOwner() == User->getName()) {

											User->BW2[i].setEmpty(true);
											User->BW2[i].setOwner("NoNAME");
											User->BW2[i].setPrice(20);
											User->BW2[i].setSize(1);
											BWO2.empty(1);
											
											User->cargo_dataWrite(2, i + 1, "NoNAME", 20,1);
										}

									}
									User->BW2cargoOwned.clear();
								}


								else {
									cout << tempNum << " of your cargos were taken out!" << endl;
									deletedNum = 0;
									User->BW2cargoOwned.clear();
									for (int i = 0; i < 500; i++)
									{
										if (User->BW2[i].getOwner() == User->getName()) {
											if (deletedNum < tempNum)
											{
												User->BW2[i].setEmpty(true);
												User->BW2[i].setOwner("NoNAME");
												User->BW2[i].setPrice(20);
												User->BW2[i].setSize(1);
												User->cargo_dataWrite(2, i + 1, "NoNAME", 20,1);
												deletedNum++;
												BWO2.empty(1);
											}
											else
											{
												User->BW2cargoOwned.push_back(i+1);
											}
										}



									}

									system("pause");
									system("cls");
									display(User);
								}



								break;

							case 3:

								for (int i = 0; i < 400; i++) {
									if (User->SW1[i].getOwner() == User->getName()) {

										ownedNum++;
									}
								}
								cout << endl << "Total number of owned Cargos in this warehouse: " << User->SW1cargoOwned.size() << endl;
								//tempVec = resetVec;
								cout << "How many cargos do you wish to take out?" << endl;
								cin >> tempNum;
								if (tempNum > ownedNum) {
									cout << "The number you have chosen is more than the number of the cargos you own!" << endl;
									cout << "As a result we have taken out all of your owned cargos" << endl;
									for (int i = 0; i < 400; i++) {
										if (User->SW1[i].getOwner() == User->getName()) 
										{
											User->SW1[i].setEmpty(true);
											User->SW1[i].setOwner("NoNAME");
											User->SW1[i].setPrice(10);
											User->SW1[i].setSize(2);
											SWO1.empty(1);
											User->cargo_dataWrite(3, i + 1, "NoNAME", 10,2);
										}

									}
									User->SW1cargoOwned.clear();
								}

								else {
									cout << tempNum << " of your cargos were taken out!" << endl;
									deletedNum = 0;
									User->SW1cargoOwned.clear();
									for (int i = 0; i < 400; i++) {
										if (User->SW1[i].getOwner() == User->getName()) {
											if (deletedNum < tempNum) {
												User->SW1[i].setEmpty(true);
												User->SW1[i].setOwner("NoNAME");
												User->SW1[i].setPrice(10);
												User->SW1[i].setSize(2);
												User->cargo_dataWrite(3, i + 1, "NoNAME", 10,2);
												deletedNum++;
												SWO1.empty(1);
											}

											else 
											{
												User->SW1cargoOwned.push_back(i+1);
											}
										}

									}

									system("pause");
									system("cls");
									display(User);
								}

								break;
							case 4:

								for (int i = 0; i < 400; i++) {
									if (User->SW2[i].getOwner() == User->getName()) {

										ownedNum++;
									}
								}
								cout << endl << "Total number of owned Cargos in this warehouse: " << User->SW2cargoOwned.size() << endl;
								//tempVec = resetVec;
								cout << "How many cargos do you wish to take out?" << endl;
								cin >> tempNum;
								if (tempNum > ownedNum) {
									cout << "The number you have chosen is more than the number of the cargos you own!" << endl;
									cout << "As a result we have taken out all of your owned cargos" << endl;
									for (int i = 0; i < 400; i++) {
										if (User->SW2[i].getOwner() == User->getName()) {

											User->SW2[i].setEmpty(true);
											User->SW2[i].setOwner("NoNAME");
											User->SW2[i].setPrice(10);
											User->SW2[i].setSize(2);
											SWO2.empty(1);
											User->cargo_dataWrite(4, i + 1, "NoNAME", 10,2);
										}

									}
									User->SW2cargoOwned.clear();
								}

								else {
									cout << tempNum << " of your cargos were taken out!" << endl;
									deletedNum = 0;
									User->SW2cargoOwned.clear();
									for (int i = 0; i < 400; i++) {
										if (User->SW2[i].getOwner() == User->getName()) {
											if (deletedNum < tempNum) {
												User->SW2[i].setEmpty(true);
												User->SW2[i].setOwner("NoNAME");
												User->SW2[i].setPrice(10);
												User->SW2[i].setSize(2);
												User->cargo_dataWrite(4, i + 1, "NoNAME", 10,2);
												deletedNum++;
												SWO2.empty(1);
											}
											else 
											{
												User->SW2cargoOwned.push_back(i+1);
											}
										}

									}

									system("pause");
									system("cls");
									display(User);
								}

								break;
							case 5:

								for (int i = 0; i < 400; i++) {
									if (User->SW3[i].getOwner() == User->getName()) {

										ownedNum++;
									}
								}
								cout << endl << "Total number of owned Cargos in this warehouse: " << User->SW3cargoOwned.size() << endl;
								//tempVec = resetVec;
								cout << "How many cargos do you wish to take out?" << endl;
								cin >> tempNum;
								if (tempNum > ownedNum) {
									cout << "The number you have chosen is more than the number of the cargos you own!" << endl;
									cout << "As a result we have taken out all of your owned cargos" << endl;
									for (int i = 0; i < 400; i++) {
										if (User->SW3[i].getOwner() == User->getName()) {

											User->SW3[i].setEmpty(true);
											User->SW3[i].setOwner("NoNAME");
											User->SW3[i].setPrice(10);
											User->SW3[i].setSize(2);
											User->cargo_dataWrite(5, i + 1, "NoNAME", 10,2);
											SWO3.empty(1);
										}

									}
									User->SW3cargoOwned.clear();
								}

								else {
									cout << tempNum << " of your cargos were taken out!" << endl;
									deletedNum = 0;
									User->SW3cargoOwned.clear();
									for (int i = 0; i < 400; i++) {
										if (User->SW3[i].getOwner() == User->getName()) {
											if (deletedNum < tempNum) {
												User->SW3[i].setEmpty(true);
												User->SW3[i].setOwner("NoNAME");
												User->SW3[i].setPrice(10);
												User->SW3[i].setSize(2);
												User->cargo_dataWrite(5, i + 1, "NoNAME", 10,2);
												deletedNum++;
												SWO3.empty(1);
											}
											else {
												User->SW3cargoOwned.push_back(i+1);
											}
										}

									}

									system("pause");
									system("cls");
									display(User);
								}
								break;

							case 6:

								for (int i = 0; i < 400; i++) {
									if (User->SW4[i].getOwner() == User->getName()) {

										ownedNum++;
									}
								}
								cout << endl << "Total number of owned Cargos in this warehouse: " << User->SW4cargoOwned.size() << endl;
								//tempVec = resetVec;
								cout << "How many cargos do you wish to take out?" << endl;
								cin >> tempNum;
								if (tempNum > ownedNum) {
									cout << "The number you have chosen is more than the number of the cargos you own!" << endl;
									cout << "As a result we have taken out all of your owned cargos" << endl;
									for (int i = 0; i < 400; i++) {
										if (User->SW4[i].getOwner() == User->getName()) {

											User->SW4[i].setEmpty(true);
											User->SW4[i].setOwner("NoNAME");
											User->SW4[i].setPrice(10);
											User->SW4[i].setSize(2);
											User->cargo_dataWrite(6, i + 1, "NoNAME", 10,2);
											SWO4.empty(1);
										}

									}
									User->SW4cargoOwned.clear();
								}

								else {
									cout << tempNum << " of your cargos were taken out!" << endl;
									deletedNum = 0;
									User->SW4cargoOwned.clear();
									for (int i = 0; i < 400; i++) {
										if (User->SW4[i].getOwner() == User->getName()) {
											if (deletedNum < tempNum) {
												User->SW4[i].setEmpty(true);
												User->SW4[i].setOwner("NoNAME");
												User->SW4[i].setPrice(10);
												User->SW4[i].setSize(2);
												User->cargo_dataWrite(6, i + 1, "NoNAME", 10,2);
												deletedNum++;
												SWO4.empty(1);
											}

											else {
												User->SW1cargoOwned.push_back(i+1);
											}
										}

									}

									system("pause");
									system("cls");
									display(User);
								}
								break;

							default:
								cout << "Something went wrong!" << endl;
							}

						}
						else {
							cout << "Invalid input! Please try again!" << endl;
						}
					}
					User->user_dataWrite();
					errorLoopHolder = 0;
					cout << endl << "Do you want to continue? 1.Yes 2.No" << endl;
					while (errorLoopHolder == 0) {
						cin >> choice;
						if (choice == '1') {
							cout << "You have chosen to continue!" << endl << endl;
							errorLoopHolder = 1;
							system("pause");
							system("cls");
						}

						else if (choice == '2') {
							cout << "You have chosen to quit the program!" << endl << endl;
							isCInput = true;
							errorLoopHolder = 1;
							menuLoopHolder = 1;
							cout << "Thank you for using our program!" << endl;
							break;
						}


						else {
							cout << "Invalid input! Please try again!" << endl;
						}
					}
					break;

				case '4':
					errorLoopHolder = 0;
					cout << "Are you sure you want to continue? 1.Yes 2.No" << endl;
					while (errorLoopHolder == 0) {
						cin >> choice;
						if (choice == '1') {
							cout << "You have logged out!" << endl << endl;
							errorLoopHolder = 1;
							isCInput = true;
						}

						else if (choice == '2') {
							cout << "You have chosen to continue!" << endl << endl;
							system("pause");
							system("cls");
							errorLoopHolder = 1;
							menuLoopHolder = 1;
						}

						else {
							cout << "Invalid input! Please try again!" << endl;
							system("pause");
							system("cls");
						}
					}
					break;

				default:
					cout << "Invalid input and please try again:" << endl;
					break;
				}
			} while (!isCInput);
		}
		isCInput = false;
		system("pause");
		system("cls");
	}
	return 0;
}