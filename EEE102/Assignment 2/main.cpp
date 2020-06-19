//=======================
//		main.cpp
//=======================

// main function for the RPG style game
#include <cstdlib>
#include <iostream>
#include <string>
#include "player.h"
#include "swordsman.h"
#include "archer.h"
#include "mage.h"

using namespace std;

int main()
{
	string tempName;	//a variable to hold the user's choosen name
	bool success=0;		//flag for storing whether operation is successful
	cout <<"Please input player's name: ";
	cin >>tempName;		// get player's name from keyboard input
	player *human;		// use pointer of base class, convenience for polymorphism
	player *enemy;
	human = new swordsman(1, "Sahand"); //We only initialise an instance of human for the program to run
	enemy = new swordsman(1, "Sam"); //We only initialise an instance of human for the program to run
	int tempJob;		// temp choice for job selection
	do
	{
		cout <<"Please choose a job: 1 Swordsman, 2 Archer, 3 Mage"<<endl;
		cin>>tempJob;
		system("cls");		// clear the screen
		switch(tempJob)
		{
		case 1:
			human=new swordsman(1,tempName);	// create the character with user inputted name and job
			success=1;		// operation succeed
			break;
		case 2:
			human = new archer(1, tempName);	// create the character with user inputted name and job
			success = 1;		// operation succeed
			break;
		case 3:
			human = new mage(1, tempName);	// create the character with user inputted name and job
			success = 1;		// operation succeed
			break;
		default:
			break;				// In this case, success=0, character creation failed
		}
	}
	
	while(success!=1);		// so the loop will ask user to re-create a character
	int tempCom;			// temp command inputted by user
	int nOpp=0;				// the Nth opponent
	for(int i=1;nOpp<5;i+=2)	// i is opponent's level
	{
		nOpp++;
		system("cls");
		cout<<"STAGE " <<nOpp<<endl;
		swordsman enemy(i, "Warrior");	// Initialise an opponent, level i, name "Warrior"
		int random = 1 + rand() % 3; //Here we declare a random variable that chooses our opponent's type

		if (random == 1) {
			swordsman enemy(i, "Swords warrior");
			cout << "Your opponent, a Level " << i << " Swordsman." << endl; //Initialise a swordsman as the opponent
		}
		else if (random == 2) {
			archer enemy(i, "Archer warrior"); //Initialise an archer as the opponent
			cout << "Your opponent, a Level " << i << " Archer." << endl;
		}
		else if (random == 3) {
			mage enemy(i, "Mage warrior"); //Initialise a mage as the opponent
			cout << "Your opponent, a Level " << i << " Mage." << endl;
		}
		
		system("pause");
		
		
		

		human->reFill();				// get HP/MP refill before start fight
		
		while(!human->death() && !enemy.death())	// no died
		{
			success=0;
			while (success!=1)
			{
				showinfo(*human,enemy);				// show fighter's information
				cout<<"Please give command: "<<endl;
				cout<<"1 Attack; 2 Special Attack; 3 Use Heal; 4 Use Magic Water; 0 Exit Game"<<endl;
				cin>>tempCom;
				switch(tempCom)
				{
				case 0:
					cout<<"Are you sure to exit? Y/N"<<endl;
					char temp;
					cin>>temp;
					if(temp=='Y'||temp=='y')
						return 0;
					else
						break;
				case 1:
					success=human->attack(enemy);
					human->isLevelUp();
					enemy.isDead();
					break;
				case 2:
					success=human->specialatt(enemy);
					human->isLevelUp();
					enemy.isDead();
					break;
				case 3:
					success=human->useHeal();
					break;
				case 4:
					success=human->useMW();
					break;
				default:
					break;
				}
			}
			if(!enemy.death())		// If AI still alive
				enemy.AI(*human);
			else							// AI died
			{
				cout<<"YOU WIN"<<endl;
				human->transfer(enemy);		// player got all AI's items
			}
			if (human->death())
			{
				system("cls");
				cout<<endl<<setw(50)<<"GAME OVER"<<endl;
				human->isDead();		// player is dead, program is getting to its end, what should we do here?
				system("pause");
				return 0;
			}
		}
	}
	showinfo(*human, *enemy);			// You win, program is getting to its end, what should we do here?
	system("cls");
	cout<<"Congratulations! You defeated all opponents!!"<<endl;
	system("pause");
	return 0;
}
		

