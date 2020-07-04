#pragma once
#include "user.h"
class keeper :public user
{
	friend class user;
public:
	keeper(string Name_in);//Constructor with a parameter
	void editWhouse();//Edit the infomation of warehouse
	void editCustomer(int numofWhouse_in, int numofCargo_in, int, string Owner_in);//Edit the infomation of customer
};