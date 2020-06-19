#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Fraction.h"
#include "iFraction.h"


using namespace std;


Fraction::Fraction(int topValue, int bottomValue) { //Constructor for the Fraction class

	top = topValue;
	bottom = bottomValue;

}


iFraction::iFraction(int decimalPartValue, int topValue, int bottomValue) { //Constructor for the iFraction sub-class
	decimalPart = decimalPartValue;
	top = topValue;
	bottom = bottomValue;
}


string Fraction::showFraction() { //To display an improper fraction
	return to_string(top) + "/" + to_string(bottom);
}


string iFraction::showFraction() { //To display a mixed fraction
	return to_string(decimalPart) + "(" + to_string(top) + "/" + to_string(bottom) + ")";
}


int Fraction::gcdfinder(int a, int b) {
	//Here we increase the value of i in a for loop until we find the greatest common divisor of the given numerator and denominator
	int gcd = 1;
	for (int i = 1; i <= a && i <= b; i++) {
		if (a%i == 0 && b%i == 0) {
			gcd = i;
		}
	}
	return gcd;
}


//The following method would convert a fraction object into an ifraction object (Algorithm explained in the wordfile)

iFraction convertF(Fraction givenFraction) { 
	iFraction result; //an iFraction object called result which is equivalent to its Fraction object
	givenFraction = givenFraction.normalise(givenFraction);


	//In the following, answer is an iFraction object that temporarily holds the values for result

	if (abs(givenFraction.top) < givenFraction.bottom) { //When the magnitude of the numerator is smaller than the denominator
		iFraction answer(0, givenFraction.top, givenFraction.bottom);
		result = answer;
	}

	else if (abs(givenFraction.top) == givenFraction.bottom) { //When the magnitude of the numerator is equal to the denominator
		iFraction answer(givenFraction.top / givenFraction.bottom, 0, 1);
		result = answer;
	}

	else { //When the magnitude of the numerator is greater than the denominator

		if (givenFraction.top < 0) { //when the numerator is smaller than zero
			iFraction answer(-(abs(givenFraction.top) / givenFraction.bottom), -(abs(givenFraction.top) % givenFraction.bottom), givenFraction.bottom);

			result = answer;
		}
		else if (givenFraction.top == 0) { //When the numerator is equal to zero
			iFraction answer(0, 0, 1);
			result = answer;
		}
		else { //When the numerator is greater than zero
			iFraction answer(givenFraction.top / givenFraction.bottom, givenFraction.top % givenFraction.bottom, givenFraction.bottom);
			result = answer;
		}
	}


	return result; 
}


Fraction iFraction::convertIF(iFraction givenFraction) { //This is to convert any iFraction object to an equivalent Fraction object
	Fraction result;//an iFraction object called result which is equivalent to its Fraction object

	if (givenFraction.decimalPart != 0) { //when the decimal part of the mixed fraction is not zero
		result.top = givenFraction.decimalPart * givenFraction.bottom + givenFraction.top;
		result.bottom = givenFraction.bottom;
	}
	else { //When the decimal part of the mixed fraction is zero
		result.top = givenFraction.top;
		result.bottom = givenFraction.bottom;
	}
	return result;
}


double Fraction::convertToDecimal(Fraction givenFraction) { //This is to convert any given Fraction object to a (double) decimal
	{
		double result;
		result = (double)givenFraction.top / givenFraction.bottom;
		return result;
	}
}


double iFraction::convertToDecimal(iFraction givenIFraction) { //This is to convert any given iFraction object to a (double) decimal
	Fraction givenFraction = convertIF(givenIFraction); //here, we convert our iFraction object to a fraction object
	double result;
	result = (double)givenFraction.top / givenFraction.bottom; //The decimal equal to our fraction object
	return result;
}


Fraction Fraction::plus(Fraction secondFraction) {

	Fraction result;
	
	result.top = (top*secondFraction.bottom) + (bottom*secondFraction.top); //This is to find the numerator of the result
	
	result.bottom = bottom * secondFraction.bottom; //This is to find the denominator of the result
	return result;

}


iFraction iFraction::plus(iFraction secondIFraction) {
	
	//We store the three variables of the first iFraction inside an iFraction object called firstIFraction
	iFraction firstIFraction(decimalPart, top, bottom); 

	iFraction result; //An object to store the results
	Fraction fractionalResult; //An object to store the improper fraction form of the results
	Fraction firstFraction = convertIF(firstIFraction);
	Fraction secondFraction = convertIF(secondIFraction);


	fractionalResult = firstFraction.plus(secondFraction); //We use the already created method to find the sum of two fraction objects
	result = convertF(fractionalResult); //Now we convert the result back to iFraction
	return result;
}


Fraction Fraction::minus(Fraction secondFraction) {

	Fraction result;
	//This is to find the numerator of the result
	result.top = (top*secondFraction.bottom) - (bottom*secondFraction.top);
	//This is to find the denominator of the result
	result.bottom = bottom * secondFraction.bottom;
	return result;
}


iFraction iFraction::minus(iFraction secondIFraction) {

	//We store the three variables of the first iFraction inside an iFraction object called firstIFraction
	iFraction firstIFraction(decimalPart, top, bottom);

	iFraction result; //An object to store the results
	Fraction fractionalResult; //An object to store the improper fraction form of the results
	Fraction firstFraction = convertIF(firstIFraction);
	Fraction secondFraction = convertIF(secondIFraction);


	fractionalResult = firstFraction.minus(secondFraction); //We use the already created method to find the sum of two fraction objects
	result = convertF(fractionalResult); //Now we convert the result back to iFraction
	return result;

}


Fraction Fraction::times(Fraction secondFraction) {

	Fraction result;
	//This is to find the numerator of the result
	result.top = top * secondFraction.top;
	//This is to find the denominator of the result
	result.bottom = bottom * secondFraction.bottom;
	return result;
}


iFraction iFraction::times(iFraction secondIFraction) {

	//We store the three variables of the first iFraction inside an iFraction object called firstIFraction
	iFraction firstIFraction(decimalPart, top, bottom);

	iFraction result; //An object to store the results
	Fraction fractionalResult; //An object to store the improper fraction form of the results
	Fraction firstFraction = convertIF(firstIFraction);
	Fraction secondFraction = convertIF(secondIFraction);


	fractionalResult = firstFraction.times(secondFraction); //We use the already created method to find the sum of two fraction objects
	result = convertF(fractionalResult); //Now we convert the result back to iFraction
	return result;
}


Fraction Fraction::dividedBy(Fraction secondFraction) {

	Fraction result;
	//This is to find the numerator of the result
	result.top = top * secondFraction.bottom;
	//This is to find the denominator of the result
	result.bottom = bottom * secondFraction.top;
	return result;
}


iFraction iFraction::dividedBy(iFraction secondIFraction) {

	//We store the three variables of the first iFraction inside an iFraction object called firstIFraction
	iFraction firstIFraction(decimalPart, top, bottom);

	iFraction result; //An object to store the results
	Fraction fractionalResult; //An object to store the improper fraction form of the results
	Fraction firstFraction = convertIF(firstIFraction);
	Fraction secondFraction = convertIF(secondIFraction);


	fractionalResult = firstFraction.dividedBy(secondFraction); //We use the already created method to find the sum of two fraction objects
	result = convertF(fractionalResult); //Now we convert the result back to iFraction
	return result;
}



void Fraction::comparedTo(Fraction secondFraction) {

	//Here we compare the two fractions by the following rule
	//The fraction with the bigger numerator times the other fraction's denominator result is great! if the result is the same, then they are equal!

	if (top*secondFraction.bottom > bottom*secondFraction.top) {
		cout << "First fraction is greater than the second fraction!" << endl;
		cout << "In other words " << top << "/" << bottom << " > " << secondFraction.top << "/" << secondFraction.bottom << endl;
	}

	else if (top*secondFraction.bottom == bottom * secondFraction.top) {
		cout << "The two fractions are equal!" << endl;
		cout << "In other words " << top << "/" << bottom << " = " << secondFraction.top << "/" << secondFraction.bottom << endl;
	}

	else {
		cout << "First fraction is smaller than the second fraction!" << endl;
		cout << "In other words " << top << "/" << bottom << " < " << secondFraction.top << "/" << secondFraction.bottom << endl;
	}


}


void iFraction::comparedTo(iFraction secondIFraction) {
	//Here we first convert our two iFraction objects into equivalent fraction objects
	//Then we compare them using the same rules as mentioned above (in the comparedTo method in the Fraction class)
	//The reason why we didn't use the same method here to compare the fraction objects,
	//Is due to change of sentencing as a result. Here we display mixed fractions instead of improper fractions.
	iFraction firstIFraction(decimalPart, top, bottom);
	Fraction firstFraction = convertIF(firstIFraction);
	Fraction secondFraction = convertIF(secondIFraction);

	if (firstFraction.top*secondFraction.bottom > firstFraction.bottom*secondFraction.top) {
		cout << "First fraction is greater than the second fraction!" << endl;
		cout << "In other words " << firstIFraction.normalise(firstIFraction).showFraction() << " > " << secondIFraction.normalise(secondIFraction).showFraction() << endl;
	}

	else if (firstFraction.top*secondFraction.bottom == firstFraction.bottom * secondFraction.top) {
		cout << "The two fractions are equal!" << endl;
		cout << "In other words " << firstIFraction.normalise(firstIFraction).showFraction() << " = " << secondIFraction.normalise(secondIFraction).showFraction() << endl;
	}

	else {
		cout << "First fraction is smaller than the second fraction!" << endl;
		cout << "In other words " << firstIFraction.normalise(firstIFraction).showFraction() << " < " << secondIFraction.normalise(secondIFraction).showFraction() << endl;
	}


}


Fraction Fraction::normalise(Fraction givenFraction) {

	//This is to make sure that only the numerator can be negative
	if (givenFraction.bottom < 0) {
		givenFraction.top *= -1;
		givenFraction.bottom *= -1;
	}

	int gcd = 1;

	//This is to make sure that the value is in the least common denominator form
	gcd = gcdfinder(abs(givenFraction.top), abs(givenFraction.bottom));
	givenFraction.top = givenFraction.top / gcd;
	givenFraction.bottom = givenFraction.bottom / gcd;

	if (givenFraction.top == 0) {
		givenFraction.bottom = 1;
	}
	return givenFraction;
}


iFraction iFraction::normalise(iFraction givenIFraction) {

	Fraction givenFraction = convertIF(givenIFraction); //We convert our ifraction into fraction form
	givenFraction = givenFraction.normalise(givenFraction); //Then we normalise the fraction
	givenIFraction = convertF(givenFraction); //Then convert it back to an ifraction

	return givenIFraction;
}


Fraction Fraction::convertToFraction(string givenValue) {

	Fraction result; //A fraction object to store the results
	string line; //A string to be written to the vector
	string numeratorString; //A string to store the numerator of the result
	int denominatorSize = 0; //This will show the amount of numbers that come after the dot in the decimal in order to indicate the result denominator
	int numeratorInt = 0; //An int to store the value of the numerator string as an integer
	int powerOfTen = 1; //This is to be used in a loop in order to indicate the power ten in the result denominator


	stringstream splitter(givenValue); //This would split the given decimal string into two parts: before and after the dot
	vector<string> subsets; //This is a vector to store the mentioned two parts

							//Now we write the two mentioned parts onto a vector
	while (getline(splitter, line, '.')) {
		subsets.push_back(line);
	}
	denominatorSize = subsets[1].length();

	//We append the two given parts to have the result numerator, this is simply identical to the initial given decimal only without the dot
	numeratorString = subsets[0].append(subsets[1]);
	//And now we convert the string into an integer so that it can be used to create a fraction
	stringstream numerator(numeratorString);
	numerator >> numeratorInt;
	//We set the numerator to numeratorInt variable as we explained earlier
	result.top = numeratorInt;

	//Here in a for loop, we would find the denominator required for the result
	for (int i = 0; i < denominatorSize; i++) {
		powerOfTen = powerOfTen * 10;
	}
	result.bottom = powerOfTen;

	//as the final part, we have to normalise the result to make sure that the result is in the least common denominator form
	result = result.normalise(result);


	return result;
}


iFraction iFraction::convertToFraction(string givenValue) {
	Fraction fractionalResult = fractionalResult.convertToFraction(givenValue); //We first convert the decimal into a Fraction object
	iFraction result = convertF(fractionalResult); //Then convert the obtained Fraction object into an iFraction object as a result
	return result;
}


Fraction getfirstFraction() { //This is for getting the first Fraction object

	int fractionNumerator = 0; //An int variable to hold the value of the first fraction's numerator
	int fractiondenominator = 0;//An int variable to hold the value of the first fraction's denominator
	cout << "Please put in the first fraction's numerator:" << endl;
	cin >> fractionNumerator;
	cout << "Please put in the first fraction's denominator:" << endl;
	cin >> fractiondenominator;

	if (fractiondenominator == 0) { //This is to make sure that the denominator is not 0
		cout << "Invalid denominator!\nThe denominator has been automatically set to 1 as a result!" << endl;
		fractiondenominator = 1;
	}
	Fraction result(fractionNumerator, fractiondenominator);
	return result;
}


iFraction getfirstIFraction() { //This is for getting the first iFraction object

	int decimalPart = 0; //An int variable to hold the value of the first fraction's decimal part
	int ifractionNumerator = 0; //An int variable to hold the value of the first fraction's numerator
	int ifractiondenominator = 1;//An int variable to hold the value of the first fraction's denominator

	cout << "Please put in the first fraction's decimal part:" << endl;
	cin >> decimalPart;
	cout << "Please put in the first fraction's numerator:" << endl;
	cin >> ifractionNumerator;
	cout << "Please put in the first fraction's denominator:" << endl;
	cin >> ifractiondenominator;

	if (ifractiondenominator == 0) { //This is to make sure that the denominator is not 0
		cout << "Invalid denominator!\nThe denominator has been automatically set to 1 as a result!" << endl;
		ifractiondenominator = 1;
	}
	iFraction result(decimalPart, ifractionNumerator, ifractiondenominator);
	return result;
}


Fraction getSecondFraction(int caseNum) { //This is for getting the second Fraction object

	int fractionNumerator = 0; //An int variable to hold the value of the second fraction's numerator
	int fractiondenominator = 0;//An int variable to hold the value of the second fraction's denominator
	cout << "Please put in the second fraction's numerator:" << endl;
	cin >> fractionNumerator;
	cout << "Please put in the second fraction's denominator:" << endl;
	cin >> fractiondenominator;

	if (caseNum == 4) { //We have added this condition because in division, the second fraction should not be 0
		if (fractionNumerator == 0) {
			cout << "Invalid numerator for division!\nThe numerator has been automatically set to 1 as a result!" << endl;
			fractionNumerator = 1;
		}
	}
	if (fractiondenominator == 0) { //This is to make sure that the denominator is not 0
		cout << "Invalid denominator!\nThe denominator has been automatically set to 1 as a result!" << endl;
		fractiondenominator = 1;
	}
	Fraction result(fractionNumerator, fractiondenominator);
	return result;
}


iFraction getSecondIFraction(int caseNum) { //This is for getting the second iFraction object

	int decimalPart = 0; //An int variable to hold the value of the first fraction's decimal part
	int ifractionNumerator = 0; //An int variable to hold the value of the first fraction's numerator
	int ifractiondenominator = 1;//An int variable to hold the value of the first fraction's denominator

	cout << "Please put in the second fraction's decimal part:" << endl;
	cin >> decimalPart;
	cout << "Please put in the second fraction's numerator:" << endl;
	cin >> ifractionNumerator;
	cout << "Please put in the second fraction's denominator:" << endl;
	cin >> ifractiondenominator;

	if (caseNum == 4) { //We have added this condition because in division, the second fraction should not be 0
		if (ifractionNumerator == 0) {
			cout << "Invalid numerator for division!\nThe numerator has been automatically set to 1 as a result!" << endl;
			ifractionNumerator = 1;
		}
	}

	if (ifractiondenominator == 0) { //This is to make sure that the denominator is not 0
		cout << "Invalid denominator!\nThe denominator has been automatically set to 1 as a result!" << endl;
		ifractiondenominator = 1;
	}
	iFraction result(decimalPart, ifractionNumerator, ifractiondenominator);
	return result;
}


Fraction getFraction() { //This is for getting only one Fraction object in general

	int fractionNumerator = 0; //An int variable to hold the value of the given fraction's numerator
	int fractiondenominator = 1; //An int variable to hold the value of the second fraction's denominator
	cout << "Please put in the fraction numerator:" << endl;
	cin >> fractionNumerator;
	cout << "Please put in the fraction denominator:" << endl;
	cin >> fractiondenominator;

	if (fractiondenominator == 0) { //This is to make sure that the denominator is not 0
		cout << "Invalid denominator!\nThe denominator has been automatically set to 1 as a result!" << endl;
		fractiondenominator = 1;
	}
	Fraction result(fractionNumerator, fractiondenominator);
	return result;
}


iFraction getIFraction() { //This is for getting only one iFraction object in general

	int decimalPart = 0;//An int variable to hold the value of the given fraction's decimal part
	int ifractionNumerator = 0; //An int variable to hold the value of the given fraction's numerator
	int ifractiondenominator = 1; //An int variable to hold the value of the second fraction's denominator

	cout << "Please put in the fraction decimal part:" << endl;
	cin >> decimalPart;
	cout << "Please put in the fraction numerator:" << endl;
	cin >> ifractionNumerator;
	cout << "Please put in the fraction denominator:" << endl;
	cin >> ifractiondenominator;

	if (ifractiondenominator == 0) { //This is to make sure that the denominator is not 0
		cout << "Invalid denominator!\nThe denominator has been automatically set to 1 as a result!" << endl;
		ifractiondenominator = 1;
	}
	iFraction result(decimalPart, ifractionNumerator, ifractiondenominator);
	return result;
}


string getDecimal() { //This is for getting a decimal as input
	string result; //A string to store the given decimal
	cout << "Please put in the decimal you would like to convert: " << endl;
	cin >> result;
	return result;
}


int whichTypeInput() { //This is to give the user a choice between entering an improper or a mixed function as input
	int whichType; //An integer that allows the user to choose between improper and mixed fractions as a type of input
	cout << "Which type of fractions do you want to input?" << endl;
	cout << "1. Improper Fraction \t 2. Mixed Fraction" << endl;
	cin >> whichType;
	return whichType;
}


int whichTypeOutput() { //This is to give the user a choice between entering an improper or a mixed function as output
	int whichType; //An integer that allows the user to choose between improper and mixed fractions as a type of output
	cout << "Which type of fractions do you want to output?" << endl;
	cout << "1. Improper Fraction \t 2. Mixed Fraction" << endl;
	cin >> whichType;
	return whichType;
}


int main() {

	int choice; //An integer variable to store the choice that the user has input in order to find the necessary functions
	int continueLoop; //An integer loop to be used when the user asked if they want to continue using the program or not
	int loopHolder = 0; //An integer to repeat the switch statement, in case an invalid value has been input
	int whichType = 0; //An integer that allows the user to choose between improper and mixed fractions as a type of input
	Fraction firstFraction; //A fraction object to act as the first fraction that the user inputs
	Fraction secondFraction; //A fraction object to act as the second fraction that the user inputs

	while (loopHolder == 0) {

		cout << "Please Choose one of the following choices by entering its number :)" << endl;
		cout << "1.Find the Sum \n2.Find the Difference \n3.Find the multiplication \n4.Find the division" << endl;
		cout << "5.Convert Fraction to Decimal \n6.Convert Decimal to Fraction \n7.Compare two fractions" << endl;
		cout << "8.Convert improper fraction to mixed fraction \n9.Convert mixed fraction to improper fraction\n" << endl;
		cin >> choice;

		switch (choice) {
		case 1:
		{
			whichType = whichTypeInput(); //To see whether the user wants to enter improper or mixed fractions.


			if (whichType == 1) {
				//This will get the first fraction from the user and display it
				Fraction firstFraction = getfirstFraction();
				cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;
				//This will get the second fraction from the user and display it
				Fraction secondFraction = getSecondFraction(1);
				cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;
				//Here we would get the results from the plus and then display it
				Fraction result = firstFraction.plus(secondFraction);
				cout << "The Sum of the two input fractions is: " << result.normalise(result).showFraction() << "\n" << endl;
			}

			else {
				//This will get the first fraction from the user and display it
				iFraction firstFraction = getfirstIFraction();
				cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;
				//This will get the second fraction from the user and display it
				iFraction secondFraction = getSecondIFraction(1);
				cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;
				//Here we would get the results from the plus and then display it
				iFraction result = firstFraction.plus(secondFraction);
				cout << "The Sum of the two input fractions is: " << result.normalise(result).showFraction() << "\n" << endl;
			}

		}
		break;


		case 2:
		{
			whichType = whichTypeInput(); //To see whether the user wants to enter improper or mixed fractions.


			if (whichType == 1) {
				//This will get the first fraction from the user and display it
				Fraction firstFraction = getfirstFraction();
				cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;
				//This will get the second fraction from the user and display it
				Fraction secondFraction = getSecondFraction(1);
				cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;
				//Here we would get the results from the minus and then display it
				Fraction result = firstFraction.minus(secondFraction);
				cout << "The subtraction of the two input fractions is: " << result.normalise(result).showFraction() << "\n" << endl;
			}

			else {
				//This will get the first fraction from the user and display it
				iFraction firstFraction = getfirstIFraction();
				cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;
				//This will get the second fraction from the user and display it
				iFraction secondFraction = getSecondIFraction(1);
				cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;
				//Here we would get the results from the minus and then display it
				iFraction result = firstFraction.minus(secondFraction);
				cout << "The subtraction of the two input fractions is: " << result.normalise(result).showFraction() << "\n" << endl;
			}

		}
		break;


		case 3:

		{
			whichType = whichTypeInput(); //To see whether the user wants to enter improper or mixed fractions.


			if (whichType == 1) {
				//This will get the first fraction from the user and display it
				Fraction firstFraction = getfirstFraction();
				cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;
				//This will get the second fraction from the user and display it
				Fraction secondFraction = getSecondFraction(1);
				cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;
				//Here we would get the results from the times and then display it
				Fraction result = firstFraction.times(secondFraction);
				cout << "The Multiplication of the two input fractions is: " << result.normalise(result).showFraction() << "\n" << endl;
			}

			else {
				//This will get the first fraction from the user and display it
				iFraction firstFraction = getfirstIFraction();
				cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;
				//This will get the second fraction from the user and display it
				iFraction secondFraction = getSecondIFraction(1);
				cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;
				//Here we would get the results from the times and then display it
				iFraction result = firstFraction.times(secondFraction);
				cout << "The Multiplication of the two input fractions is: " << result.normalise(result).showFraction() << "\n" << endl;
			}


		}
		break;


		case 4:
		{
			whichType = whichTypeInput(); //To see whether the user wants to enter improper or mixed fractions.


			if (whichType == 1) {
				//This will get the first fraction from the user and display it
				Fraction firstFraction = getfirstFraction();
				cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;
				//This will get the second fraction from the user and display it
				Fraction secondFraction = getSecondFraction(1);
				cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;
				//Here we would get the results from the dividedBy and then display it
				Fraction result = firstFraction.dividedBy(secondFraction);
				cout << "The division of the two input fractions is: " << result.normalise(result).showFraction() << "\n" << endl;
			}

			else {
				//This will get the first fraction from the user and display it
				iFraction firstFraction = getfirstIFraction();
				cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;
				//This will get the second fraction from the user and display it
				iFraction secondFraction = getSecondIFraction(1);
				cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;
				//Here we would get the results from the dividedBy and then display it
				iFraction result = firstFraction.dividedBy(secondFraction);
				cout << "The division of the two input fractions is: " << result.normalise(result).showFraction() << "\n" << endl;
			}


		}
		break;

		case 5:
		{

			whichType = whichTypeInput(); //To see whether the user wants to enter improper or mixed fractions.

			if (whichType == 1) {
				//This will get a fraction from the user and display both its fraction form and decimal form
				Fraction inputFraction = getFraction();
				cout << "The input fraction is: " << inputFraction.normalise(inputFraction).showFraction() << endl;
				cout << "The decimal form of this fraction is: " << inputFraction.convertToDecimal(inputFraction) << "\n" << endl;
			}
			else {
				//This will get an ifraction from the user and display both its mixed fraction form and decimal form
				iFraction inputIFraction = getIFraction();
				cout << "The input fraction is: " << inputIFraction.normalise(inputIFraction).showFraction() << endl;
				cout << "The decimal form of this fraction is: " << inputIFraction.convertToDecimal(inputIFraction) << "\n" << endl;
			}
		}
		break;

		case 6:
		{
			whichType = whichTypeOutput(); //To see whether the user wants to get improper or mixed fractions.

			if (whichType == 1) {
				//Here we get a decimal as an input from the user and then display both itself and its' improper fraction form
				string inputDecimal = getDecimal();
				cout << "The input decimal is: " << inputDecimal << endl;
				Fraction result = result.convertToFraction(inputDecimal);
				cout << "The fraction equivalent to this decimal is: " << result.normalise(result).showFraction() << endl;
			}

			else {
				//Here we get a decimal as an input from the user and then display both itself and its' mixed fraction form
				string inputDecimal = getDecimal();
				cout << "The input decimal is: " << inputDecimal << endl;
				iFraction result = result.convertToFraction(inputDecimal);
				cout << "The fraction equivalent to this decimal is: " << result.normalise(result).showFraction() << endl;
			}
		}
		break;



		case 7:
		{
			whichType = whichTypeInput(); //To see whether the user wants to enter improper or mixed fractions.

			if (whichType == 1) {

				//Here we get two fractions, same as before, and compare them by using the comparedTo function
				Fraction firstFraction = getfirstFraction();
				cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;

				Fraction secondFraction = getSecondFraction(7);
				cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;

				firstFraction.comparedTo(secondFraction);

			}

			else {
				//Here we get two fractions, same as before, and compare them by using the comparedTo function
				iFraction firstFraction = getfirstIFraction();
				cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;

				iFraction secondFraction = getSecondIFraction(7);
				cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;

				firstFraction.comparedTo(secondFraction);

			}


		}
		break;


		case 8:
		{
			Fraction inputFraction = getFraction(); //We first get an improper fraction from the user
			iFraction iFractionForm = convertF(inputFraction); //Then convert it into a mixed fraction using convertF
			cout << "The input improper fraction is: " << inputFraction.normalise(inputFraction).showFraction() << endl;
			cout << "The output mixed fraction is: " << iFractionForm.normalise(iFractionForm).showFraction() << endl;
		}
		break;



		case 9:
		{
			iFraction inputFraction = getIFraction(); //We first get a mixed fraction from the user
			Fraction fractionForm = inputFraction.convertIF(inputFraction); //Then convert it into an improper fraction using convertIF
			cout << "The input mixed fraction is: " << inputFraction.normalise(inputFraction).showFraction() << endl;
			cout << "The output improper fraction is: " << fractionForm.normalise(fractionForm).showFraction() << endl;

		}
		break;



		default:
			//In case the user input values other than 1-7, which are not acceptable, the following message would be prompted
			iFraction c = convertF(Fraction(-4, 3));
			cout << c.showFraction() << endl;
			cout << "Invalid Choice! Please Try Again!\n" << endl;
			break;
		}

		//Here we ask the user whether they want to continue using the program or not
		cout << "Do you want to continue? 1.Yes 2.No" << endl;
		cin >> continueLoop;
		if (continueLoop == 2) {
			cout << "Thank you for using my program!\n" << endl;
			loopHolder = 1;
		}
		else if (continueLoop == 1) {
			cout << "Glad to hear that!\n" << endl;
		}
		else {
			cout << "Well, I'll take that as a YES!\n" << endl;
		}
	}





	//The following were only for testing purposes and therefore, are commented out of the main code
	/*Fraction a(5, 3);
	Fraction b(2, 3);
	cout<<"a: "<<a.showFraction()<<endl;
	cout << "b: " << b.showFraction() << endl;
	iFraction c = convertF(a);
	iFraction d = convertF(b);
	iFraction e= c.plus(d);
	iFraction f = c.minus(d);
	iFraction g = c.times(d);
	iFraction h = c.dividedBy(d);
	cout << "c: " << c.showFraction() << endl;
	cout << "d: " << d.showFraction() << endl;
	cout << "result: " << e.showFraction()<< endl;
	cout << "result: " << f.showFraction() << endl;
	cout << "result: " << g.showFraction() << endl;
	cout << "result: " << h.showFraction() << endl;
	c.comparedTo(d);*/



	return 0;
}



