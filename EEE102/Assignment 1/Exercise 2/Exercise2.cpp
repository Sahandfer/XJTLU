#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class Fraction {

private:
	int top; //An input to store the numerator
	int bottom; //An input to store the denominator

public:
	Fraction(){
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

string Fraction::showFraction() {
	return to_string(top) + "/" + to_string(bottom);
}

double Fraction::convertToDecimal(Fraction givenFraction) {
	{
		double result;
		result = (double)givenFraction.top / givenFraction.bottom;
		return result;
	}
}


Fraction::Fraction(int topValue, int bottomValue){
		
		top = topValue;
		bottom = bottomValue;

}


Fraction Fraction::plus(Fraction secondFraction){
		
		Fraction result;
		//This is to find the numerator of the result
		result.top = (top*secondFraction.bottom) + (bottom*secondFraction.top);
		//This is to find the denominator of the result
		result.bottom = bottom*secondFraction.bottom;
		return result;

}

Fraction Fraction::minus(Fraction secondFraction){
		
		Fraction result;
		//This is to find the numerator of the result
		result.top = (top*secondFraction.bottom) - (bottom*secondFraction.top);
		//This is to find the denominator of the result
		result.bottom = bottom*secondFraction.bottom;
		return result;
}

Fraction Fraction::times(Fraction secondFraction){
	
		Fraction result;
		//This is to find the numerator of the result
		result.top = top*secondFraction.top;
		//This is to find the denominator of the result
		result.bottom = bottom*secondFraction.bottom;
		return result;
}

Fraction Fraction::dividedBy(Fraction secondFraction){
		
		Fraction result;
		//This is to find the numerator of the result
		result.top = top*secondFraction.bottom;
		//This is to find the denominator of the result
		result.bottom = bottom*secondFraction.top;
		return result;
}


void Fraction::comparedTo(Fraction secondFraction){
		
		//Here we compare the two fractions by the following rule
		//The fraction with the bigger numerator times the other fraction's denominator result is great! if the result is the same, then they are equal!
	
		if (top*secondFraction.bottom > bottom*secondFraction.top){
			cout<<"First fraction is greater than the second fraction!"<<endl;
			cout << "In other words " << top << "/" << bottom << " > " << secondFraction.top << "/" << secondFraction.bottom << endl;
		}

		else if (top*secondFraction.bottom == bottom*secondFraction.top){
			cout << "The two fractions are equal!" << endl;
			cout << "In other words " << top << "/" << bottom << " = " << secondFraction.top << "/" << secondFraction.bottom << endl;
		}

		else{
			cout << "First fraction is smaller than the second fraction!" << endl;
			cout << "In other words " << top << "/" << bottom << " < " << secondFraction.top << "/" << secondFraction.bottom << endl;
		}


}

Fraction Fraction::normalise(Fraction givenFraction){
		
		//This is to make sure that only the numerator can be negative
		if (givenFraction.bottom < 0){
			givenFraction.top *= -1;
			givenFraction.bottom *= -1;
		}

		int gcd = 1;

		//This is to make sure that the value is in the least common denominator form
		gcd = gcdfinder(abs(givenFraction.top), abs(givenFraction.bottom));
		givenFraction.top = givenFraction.top / gcd;
		givenFraction.bottom = givenFraction.bottom / gcd;

		return givenFraction;
}

Fraction Fraction::convertToFraction(string givenValue){
		
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

Fraction getfirstFraction(){
		
		int fractionNumerator = 0; //An int variable to hold the value of the first fraction's numerator
		int fractiondenominator = 0;//An int variable to hold the value of the first fraction's denominator
		cout << "Please put in the first fraction's numerator:" << endl;
		cin >> fractionNumerator;
		cout << "Please put in the first fraction's denominator:" << endl;
		cin >> fractiondenominator;

		if (fractiondenominator == 0){ //This is to make sure that the denominator is not 0
			cout << "Invalid denominator!\nThe denominator has been automatically set to 1 as a result!" << endl;
			fractiondenominator = 1;
		}
		Fraction result(fractionNumerator, fractiondenominator);
		return result;
}

Fraction getSecondFraction(int caseNum){
		
		int fractionNumerator = 0; //An int variable to hold the value of the second fraction's numerator
		int fractiondenominator = 0;//An int variable to hold the value of the second fraction's denominator
		cout << "Please put in the second fraction's numerator:" << endl;
		cin >> fractionNumerator;
		cout << "Please put in the second fraction's denominator:" << endl;
		cin >> fractiondenominator;

		if (caseNum == 4){ //We have added this condition because in division, the second fraction should not be 0
			if (fractionNumerator == 0){
				cout << "Invalid numerator for division!\nThe numerator has been automatically set to 1 as a result!" << endl;
				fractionNumerator = 1;
			}
		}
		if (fractiondenominator == 0){ //This is to make sure that the denominator is not 0
			cout << "Invalid denominator!\nThe denominator has been automatically set to 1 as a result!" << endl;
			fractiondenominator = 1;
		}
		Fraction result(fractionNumerator, fractiondenominator);
		return result;
}

Fraction getFraction(){
		
		int fractionNumerator = 0; //An int variable to hold the value of the given fraction's numerator
		int fractiondenominator = 0; //An int variable to hold the value of the second fraction's denominator
		cout << "Please put in the fraction numerator:" << endl;
		cin >> fractionNumerator;
		cout << "Please put in the fraction denominator:" << endl;
		cin >> fractiondenominator;

		if (fractiondenominator == 0){ //This is to make sure that the denominator is not 0
			cout << "Invalid denominator!\nThe denominator has been automatically set to 1 as a result!" << endl;
			fractiondenominator = 1;
		}
		Fraction result(fractionNumerator, fractiondenominator);
		return result;
}

string getDecimal(){
		string result; //A string to store the given decimal
		cout << "Please put in the decimal you would like to convert: " << endl;
		cin >> result;
		return result;
}


int main(){

		int choice; //An integer variable to store the choice that the user has input in order to find the necessary functions
		int continueLoop; //An integer loop to be used when the user asked if they want to continue using the program or not
		int loopHolder = 0; //An integer to repeat the switch statement, in case an invalid value has been input
	
		Fraction firstFraction; //A fraction object to act as the first fraction that the user inputs
		Fraction secondFraction; //A fraction object to act as the second fraction that the user inputs
	
	while (loopHolder == 0){

		cout << "Please Choose one of the following choices by entering its number :)" << endl;
		cout << "1.Find the Sum \n2.Find the Difference \n3.Find the multiplication \n4.Find the division" << endl;
		cout << "5.Convert Fraction to Decimal \n6.Convert Decimal to Fraction \n7.Compare two fractions\n" << endl;
		cin >> choice;

		switch (choice){
		case 1:
		{
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
			break;


		case 2:
		{
				  //This will get the first fraction from the user and display it
				  Fraction firstFraction = getfirstFraction();
				  cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;
				  //This will get the second fraction from the user and display it
				  Fraction secondFraction = getSecondFraction(2);
				  cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;
				  //Here we would get the results from the minus and then display it
				  Fraction result = firstFraction.minus(secondFraction);
				  cout << "The Subtraction of the two input fractions is: " << result.normalise(result).showFraction() << "\n" << endl;

		}
			break;


		case 3:

		{
				  //This will get the first fraction from the user and display it
				  Fraction firstFraction = getfirstFraction();
				  cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;
				  //This will get the second fraction from the user and display it
				  Fraction secondFraction = getSecondFraction(3);
				  cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;
				  //Here we would get the results from the times and then display it
				  Fraction result = firstFraction.times(secondFraction);
				  cout << "The Multiplication of the two input fractions is: " << result.normalise(result).showFraction() << "\n" << endl;


		}
			break;


		case 4:
		{
				  //This will get the first fraction from the user and display it
				  Fraction firstFraction = getfirstFraction();
				  cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;
				  //This will get the second fraction from the user and display it
				  Fraction secondFraction = getSecondFraction(4);
				  cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;
				  //Here we would get the results from the dividedBy and then display it
				  Fraction result = firstFraction.dividedBy(secondFraction);
				  cout << "The Division of the two input fractions is: " << result.normalise(result).showFraction() << "\n" << endl;


		}
			break;

		case 5:
		{
				  //This will get a fraction from the user and display both its fraction form and decimal form
				  Fraction inputFraction = getFraction();
				  cout << "The input fraction is: " << inputFraction.normalise(inputFraction).showFraction() << endl;
				  cout << "The decimal form of this fraction is: " << inputFraction.convertToDecimal(inputFraction) << "\n" << endl;

		}
			break;

		case 6:
		{
				  //Here we get a decimal as an input from the user and then display both itself and its' fraction form
				  string inputDecimal = getDecimal();
				  cout << "The input decimal is: " << inputDecimal << endl;
				  Fraction result = result.convertToFraction(inputDecimal);
				  cout << "The fraction equivalent to this decimal is: " << result.normalise(result).showFraction() << endl;
		}
			break;

		case 7:
		{
				  //Here we get two fractions, same as before, and compare them by using the comparedTo function
				  Fraction firstFraction = getfirstFraction();
				  cout << "The first input fraction is: " << firstFraction.normalise(firstFraction).showFraction() << endl;

				  Fraction secondFraction = getSecondFraction(7);
				  cout << "The second input fraction is: " << secondFraction.normalise(secondFraction).showFraction() << endl;

				  firstFraction.comparedTo(secondFraction);
		}
			break;

		default:
				  //In case the user input values other than 1-7, which are not acceptable, the following message would be prompted
				  cout << "Invalid Choice! Please Try Again!\n" << endl;
			break;
		}
		 
		//Here we ask the user whether they want to continue using the program or not
		cout << "Do you want to continue? 1.Yes 2.No" << endl;
		cin >> continueLoop;
		if (continueLoop == 2){
			cout << "Thank you for using my program!\n" << endl;
			loopHolder = 1;
		}
		else if (continueLoop == 1){
			cout << "Glad to hear that!\n" << endl;
		}
		else {
			cout << "Well, I'll take that as a YES!\n" << endl;
		}
	}

	//The Following were added for testing purposes and there are commented out from the final code:

	/*Fraction a;
	Fraction b(3, 4);
	Fraction c(5);
	Fraction d(4, 7);
	Fraction e(2, -3);
	Fraction f(15, 21);

	string testInt = "3.45";
	cout<<a.showFraction()<<endl;
	cout << b.showFraction() << endl;
	cout << c.showFraction() << endl;
	cout << b.plus(d).showFraction() << endl;
	cout << b.minus(d).showFraction() << endl;
	cout << b.times(d).showFraction() << endl;
	cout << b.dividedBy(d).showFraction() << endl;
	b.comparedTo(b);
	b.comparedTo(c);
	b.comparedTo(d);
	cout << e.normalise(e).showFraction() << endl;
	cout << f.normalise(f).showFraction() << endl;
	cout << b.convertToDecimal(b) << endl;
	cout<<a.convertToFraction(testInt).showFraction()<<endl;
	*/
	return 0;
}