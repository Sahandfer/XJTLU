#pragma once
#include "cargo.h"
#include<string>
#include<fstream>
#include<vector>
using namespace std;

extern int ID;//0 for keeper, 1 for customer to spot the authority
extern int BC1counter;
extern int BC2counter;
extern int SC1counter;
extern int SC2counter;
extern int SC3counter;
extern int SC4counter;
class user
{
	friend class keeper;
	friend class customer;
protected:
	string name;       //Character's name
public:
	virtual double getDebt();
	virtual void increaseDebt(double amount);


	vector<int> BW1cargoOwned;//To note cargos rented
	vector<int> BW2cargoOwned;//To note cargos rented
	vector<int> SW1cargoOwned;//To note cargos rented
	vector<int> SW2cargoOwned;//To note cargos rented
	vector<int> SW3cargoOwned;//To note cargos rented
	vector<int> SW4cargoOwned;//To note cargos rented
	cargo BW1[500]; //An array to represent the first big warehouse
	cargo BW2[500]; //An array to represent the second big warehouse
	cargo SW1[400]; //An array to represent the first small warehouse
	cargo SW2[400]; //An array to represent the second small warehouse
	cargo SW3[400]; //An array to represent the third small warehouse
	cargo SW4[400]; //An array to represent the fourth small warehouse

	string getName(); //To get the name of the user
	void user_dataWrite();//Write data in the file
	bool user_dataLoad();//Load data from the file
	void cargo_dataWrite(int houseNo,int cargoNo,string owner_in,int price_in,int size_in);//Write data in the file
	void cargo_dataLoad(int houseNo);//Load data from the file
	int pass_Size(int size_in);
	void cargoCreater();
};