#include <vector>
#include "user.h"

class customer :public user
{
	friend class user;

private:
	double debt; //The amount of money that the user has to pay
public:
	customer(); //Normal constructor
	customer(string Name_in);//Constructor with a parameter
	void showinfo();//To show the information of situation,includeing warehouses rented and fees
	void add(vector <int> givenWarehouse, int amountofGoods_in);//To add goods in the empty warehouse automatically
	void take();//To take out goods stored
	void increaseDebt(double amount);
	void decreaseDebt(double amount);
	double getDebt();
};