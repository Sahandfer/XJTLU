#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;






bool same_vec(vector<int> a, vector<int> b){
	bool result = false; //a boolean variable to evaluate whether the two vectors are equal or not
	int sizeOfA = a.size(); //An int variable to hold to size of the first vector (How many entries inside it)
	int sizeOfB = b.size(); //An int variable to hold to size of the second vector (How many entries inside it)
	int sameValuesCounter1 = 0; //An int variable to count the number of entries in the first vector that have been found in the second vector
	int sameValuesCounter2 = 0; //An int variable to count the number of entries in the second vector that have been found in the first vector

	//Here, we use a foor loop to find the number of entries in the first vector that have been found in the second vector
	for (int i = 0; i < sizeOfA; i++){
		for (int m = 0; m < sizeOfB; m++){
			if (a[i] == b[m]){
				sameValuesCounter1++;
				break;
			}
		}
	}
	
	//Here, we use a foor loop to find the number of entries in the second vector that have been found in the first vector
	for (int i = 0; i < sizeOfB; i++){
		for (int m = 0; m < sizeOfA; m++){
			if (a[m] == b[i]){
				sameValuesCounter2++;
				break;
			}
		}
	}
	
	//Here we are basically saying if all the elements of the first vector was found in the second vector
	//AND
	//if all the elements of the first vector was found in the second vector, the vectors are equal!
	if (sizeOfA == sameValuesCounter1 && sizeOfB == sameValuesCounter2){
		cout << "They are equal vectors!" << endl;
		result = true;
	}
	
	else{
		cout << "They are not equal vectors!" << endl;
	}
	
	


	return result;
}




int main(){
	vector<int> vector1; //A vector to hold the entries for the first input vector
	vector<int> vector2; //A vector to hold the entries for the second input vector
	int num1; //An int variable to hold each of the entries of the first vector one by one
	int num2; //An int variable to hold each of the entries of the second vector one by one
	string line1; //A string to be used as storage for the input vector because the input vector will initially be stored as a string
	string line2; //A string to be used as storage for the input vector because the input vector will initially be stored as a string


	cout << "Please input the first vector: \n(Separate your entries by putting a space between them)" << endl;
	getline(cin, line1);
	istringstream stream1(line1);
	while (stream1 >> num1){
		vector1.push_back(num1);

	}

	cout << "Now Please input the second vector: \n(Separate your entries by putting a space between them" << endl;
	getline(cin, line2);
	istringstream stream2(line2);
	while (stream2 >> num2){
		vector2.push_back(num2);
	}


	//Now we send the two vectors to the same_vec function in order to evaluate them
	same_vec(vector1, vector2);

	//The following were used for testing purposes and therefore are commented out of the final code;
	//vector<int> test1 = { 5,5,4,3,2,1,5};
	//vector<int> test2 = { 1, 2, 3, 4, 5 };




	return 0;
}
