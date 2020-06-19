#ifndef _IFRACTION
#define _IFRACTION
using namespace std;

class iFraction : public Fraction {

private:
	int decimalPart; //To show the decimal part of the mixed fraction
	int top; //To show the numerator part of the mixed fraction
	int bottom; //To show the denomerator part of the mixed fraction

public:
	iFraction() {
		decimalPart = 0;
		top = 0;
		bottom = 1;
	}


	string showFraction();
	void comparedTo(iFraction givenFraction); //A method to compare any two given iFractions
	double convertToDecimal(iFraction givenFraction); //A method to convert any given fraction object into a decimal


	iFraction(int decimalPartValue, int topValue = 0, int bottomValue = 1);
	iFraction plus(iFraction givenFraction); //A method to find the sum of two given mixed fractions
	iFraction minus(iFraction givenFraction); //A method to find the subtraction of two given mixed fractions
	iFraction times(iFraction givenFraction);//A method to find the multiplacation of two given mixed fractions
	iFraction dividedBy(iFraction givenFraction);//A method to find the division of two given moxed fractions
	Fraction convertIF(iFraction givenFraction);
	iFraction convertToFraction(string givenValue); //A method to convert any given decimal to a iFraction object
	iFraction normalise(iFraction givenFraction); //simplify the numerator and denominator as much as possible as well as only keeping negative sign in the numerator
};



#endif
