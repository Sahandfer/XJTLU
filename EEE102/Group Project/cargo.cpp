#include "cargo.h"

cargo::cargo() { //Normal constructor
	size = 0;
	empty = true;
	price = 0;
	owner = "NoName";
}

cargo::cargo(int givenSize, int givenPrice) { //Constructor for when a size an price is given
	size = givenSize;
	empty = true;
	price = givenPrice;
	owner = "NoName";
}

int cargo::getSize() { //To get the size of the cargo ==> standard or small
	return size;
}

int cargo::getPrice() { //To get the price of the place/cargo
	return price;
}

string cargo::getOwner() { //To get the owner of the cargo
	return owner;
}

bool cargo::isEmpty() { //To see whether the cargo's place is empty or not
	return empty;
}


void cargo::setSize(int givenSize) { //To set the size for a cargo
	size = givenSize;
}

void cargo::setPrice(int givenPrice) { //To set the price for a cargo
	price = givenPrice;
}

void cargo::setOwner(string givenOwner) { //To set an owner for the cargo
	owner = givenOwner;
}

void cargo::setEmpty(bool isEmpty) { //To set whether the cargo's place is empty or not
	empty = isEmpty;
}

void cargo::display() {
	if (size == 1) {
		cout << "+Cargo size ==> Standard" << endl;
	}
	else {
		cout << "+Cargo size ==> Small" << endl;
	}

	cout << "+Cargo Price ==> " << price << endl;
	cout << "+Cargo Owner ==> " << owner << endl;
	cout << "+Cargo status ==> ";
	if (empty == true) {
		cout << "Empty" << endl;
	}
	else {
		cout << "Full" << endl;
	}

}