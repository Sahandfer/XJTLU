//=======================
//		archer.cpp
//=======================

#include "archer.h"
#include <iostream>
using namespace std;
// constructor. default values don't need to be repeated here
archer::archer(int lv_in, string name_in)
{
	role = ar;	// enumerate type of job
	LV = lv_in;
	name = name_in;

	// Initialising the character's properties, based on his level
	HPmax = 150 + 8 * (LV - 1);		// HP increases 8 point2 per level
	HP = HPmax;
	MPmax = 75 + 2 * (LV - 1);		// MP increases 2 points per level
	MP = MPmax;
	AP = 25 + 4 * (LV - 1);			// AP increases 4 points per level
	DP = 25 + 4 * (LV - 1);			// DP increases 4 points per level
	speed = 25 + 2 * (LV - 1);		// speed increases 2 points per level

	playerdeath = 0;
	EXP = LV * LV * 75;
	bag.set(lv_in, lv_in);
}

void archer::isLevelUp()
{
	if (EXP >= LV * LV * 75)
	{
		LV++;
		AP += 4;
		DP += 4;
		HPmax += 8;
		MPmax += 2;
		speed += 2;
		cout << name << " Level UP!" << endl;
		cout << "HP improved 8 points to " << HPmax << endl;
		cout << "MP improved 2 points to " << MPmax << endl;
		cout << "Speed improved 2 points to " << speed << endl;
		cout << "AP improved 4 points to " << AP << endl;
		cout << "DP improved 5 points to " << DP << endl;
		system("pause");
		isLevelUp();	// recursively call this function, so the character can level up multiple times if got enough exp
	}
}

bool archer::attack(player &p)
{
	double HPtemp = 0;		// opponent's HP decrement
	double EXPtemp = 0;		// player obtained exp
	double hit = 1;			// attach factor, probably give critical attack
	srand((unsigned)time(NULL));		// generating random seed based on system time

										// If speed greater than opponent, you have some possibility to do double attack
	if ((speed>p.speed) && (rand() % 100<(speed - p.speed)))		// rand()%100 means generates a number no greater than 100
	{
		HPtemp = (int)((1.0*AP / p.DP)*AP * 5 / (rand() % 4 + 10));		// opponent's HP decrement calculated based their AP/DP, and uncertain chance
		cout << name << "'s quick strike hit " << p.name << ", " << p.name << "'s HP decreased " << HPtemp << endl;
		p.HP = int(p.HP - HPtemp);
		EXPtemp = (int)(HPtemp*1.2);
	}

	// If speed smaller than opponent, the opponent has possibility to evade
	if ((speed<p.speed) && (rand() % 50<1))
	{
		cout << name << "'s attack has been evaded by " << p.name << endl;
		system("pause");
		return 1;
	}

	// 10% chance give critical attack
	if (rand() % 100 <= 10)
	{
		hit = 1.5;
		cout << "Critical attack: ";
	}

	// Normal attack
	HPtemp = (int)((1.0*AP / p.DP)*AP * 5 / (rand() % 4 + 10));
	cout << name << " uses bash, " << p.name << "'s HP decreases " << HPtemp << endl;
	EXPtemp = (int)(EXPtemp + HPtemp * 1.2);
	p.HP = (int)(p.HP - HPtemp);
	cout << name << " obtained " << EXPtemp << " experience." << endl;
	EXP = (int)(EXP + EXPtemp);
	system("pause");
	return 1;		// Attack success
}

bool archer::specialatt(player &p)
{
	if (MP<40)
	{
		cout << "You don't have enough magic points!" << endl;
		system("pause");
		return 0;		// Attack failed
	}
	else
	{
		MP -= 40;			// consume 40 MP to do special attack

							//10% chance opponent evades
		if (rand() % 100 <= 10)
		{
			cout << name << "'s leap attack has been evaded by " << p.name << endl;
			system("pause");
			return 1;
		}

		double HPtemp = 0;
		double EXPtemp = 0;
		//double hit=1;			
		//srand(time(NULL));		
		HPtemp = (int)(AP*1.2 + 20);		// not related to opponent's DP
		EXPtemp = (int)(HPtemp*1.5);		// special attack provides more experience
		cout << name << " uses leap attack, " << p.name << "'s HP decreases " << HPtemp << endl;
		cout << name << " obtained " << EXPtemp << " experience." << endl;
		p.HP = (int)(p.HP - HPtemp);
		EXP = (int)(EXP + EXPtemp);
		system("pause");
	}
	return 1;	// special attack succeed
}

// Computer opponent
void archer::AI(player &p)
{
	if ((HP<(int)((1.0*p.AP / DP)*p.AP*1.5)) && (HP + 100 <= 1.1*HPmax) && (bag.nOfHeal()>0) && (HP>(int)((1.0*p.AP / DP)*p.AP*0.5)))
		// AI's HP cannot sustain 3 rounds && not too lavish && still has heal && won't be killed in next round
	{
		useHeal();
	}
	else
	{
		if (MP >= 40 && HP>0.5*HPmax && rand() % 100 <= 30)
			// AI has enough MP, it has 30% to make special attack
		{
			specialatt(p);
			p.isDead();		// check whether player is dead
		}
		else
		{
			if (MP<40 && HP>0.5*HPmax && bag.nOfMW())
				// Not enough MP && HP is safe && still has magic water
			{
				useMW();
			}
			else
			{
				attack(p);	// normal attack
				p.isDead();
			}
		}
	}
}