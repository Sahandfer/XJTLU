#ifndef _FRACTION
#define _FRACTION
using namespace std;

class Fraction {

	friend class iFraction;
	friend iFraction convertF(Fraction givenFraction);
private:
	int top; //An input to store the numerator
	int bottom; //An input to store the denominator

public:
	Fraction() {
		top = 0;
		bottom = 1;
	}


	int gcdfinder(int a, int b); //A method to find the greatest common divisor
	string showFraction(); //A method to show any given fraction object as a fraction in form of a string
	double convertToDecimal(Fraction givenFraction); //A method to convert any given fraction object into a decimal
	void comparedTo(Fraction givenFraction); //A method to compare any two given fractions

	Fraction(int topValue, int bottomValue = 1); //The constructor for fractions
	Fraction plus(Fraction givenFraction); //A method to find the sum of two given fractions
	Fraction minus(Fraction givenFraction); //A method to find the subtraction of two given fractions
	Fraction times(Fraction givenFraction);//A method to find the multiplacation of two given fractions
	Fraction dividedBy(Fraction givenFraction);//A method to find the division of two given fractions
	Fraction normalise(Fraction givenFraction); //A method to normalise each given fraction==> simplify the numerator and denominator as much as possible as well as only keeping negative sign in the numerator
	Fraction convertToFraction(string givenValue); //A method to convert any given decimal to a fraction object

};



#endif
