#include "customer.h"

customer::customer() {
	name = "No Name";
	debt = 0;
}

customer::customer(string Name_in)//Constructor with a parameter
{
	name = Name_in;
	debt = 0;
}

void customer::showinfo() //To show the information of situation,includeing warehouses rented and fees
{
	cout << "You have rented " << endl;
	cout << "You need to pay " << endl;
}


void customer::increaseDebt(double amount) {
	debt += amount;
}

void customer::decreaseDebt(double amount) {
	debt -= amount;
}

double customer::getDebt() {
	return debt;
}