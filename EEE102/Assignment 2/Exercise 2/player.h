//=======================
//		player.h
//=======================

// The base class of player
// including the general properties and methods related to a character

#ifndef _PLAYER
#define _PLAYER

#include <iomanip>		// use for setting field width
#include <time.h>		// use for generating random factor
#include "container.h"
#include <string>


using namespace std;

enum job {sw, ar, mg};	/* define 3 jobs by enumerate type
							   sword man, archer, mage */
class player
{
	friend void showinfo(player &p1, player &p2);
	friend class swordsman;
	friend class archer;
	friend class mage;

protected:
	int HP, HPmax, MP, MPmax, AP, DP, speed, EXP, LV;
	// General properties of all characters
	string name;	// character name
	job role;		/* character's job, one of swordman, archer and mage,
					   as defined by the enumerate type */
	container bag;	// character's inventory

public:
	virtual bool attack(player &p)=0;	// normal attack
	virtual bool specialatt(player &p)=0;	//special attack
	virtual void isLevelUp()=0;			// level up judgement
	virtual void AI(player &p)=0;
	/* Attention!
	These four methods are called "Pure virtual functions".
	They have only declaration, but no definition.
	The class with pure virtual functions are called "Abstract class", which can only be used to inherited, but not to constructor objects. 
	The detailed definition of these pure virtual functions will be given in subclasses. */

	void reFill();		// character's HP and MP resume
	bool death();		// report whether character is dead
	void isDead();		// check whether character is dead
	bool useHeal();		// consume heal, irrelevant to job
	bool useMW();		// consume magic water, irrelevant to job
	void transfer(player &p);	// possess opponent's items after victory
	void showRole();	// display character's job
	
private:
	bool playerdeath;			// whether character is dead, doesn't need to be accessed or inherited
};

#endif
