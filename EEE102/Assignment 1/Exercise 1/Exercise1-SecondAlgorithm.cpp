#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

vector<int> sortVector(vector<int> c){
	//This method would get a vector as an input, sort its entries from lowest to highest and then return it
	sort(c.begin(), c.end());
	return c;
}


vector<int> duplicateRemover(vector<int> d){
	
	//In this function, any duplicate entry (repeated entry) would be removed!

	int initial_Size = d.size(); //An integer value to hold the length of the vector before its duplicate entries are removed. This will be used for the following for loop
	
	for (int i = initial_Size - 1; i >= 0; i--){
		
		if (i > 0){
			if (d[i] == d[i - 1]){
				d.erase(d.begin() + i);
			}
		}
			
	}

	return d;
}



bool same_vec(vector<int> a, vector<int> b){
	bool result = false; //A boolean to evaluate whether the two vectors are equal to each other or not
	a = duplicateRemover(sortVector(a)); //Here, the first vector's entries will be sorted and the duplicates will be removed
	b = duplicateRemover(sortVector(b)); //Here, the second vector's entries will be sorted and the duplicates will be removed

	//Then the relationship between them (equal or not), would be evaluated
	if (a == b){
		cout << "They are equal vectors!" << endl;
		result = true;
	}
	else{
		cout << "They are not equal vectors!" << endl;
	}
	return result;
}



int main(){
	vector<int> vector1; //A vector to hold the entries for the first vector
	vector<int> vector2; //A vector to hold the entries for the second vector
	int num1; //An integer variable to hold each entry of the first vector one by one
	int num2; //An integer variable to hold each entry of the second vector one by one
	string line1; //A string variable to be used as a string stream in order to store input as a string (for the first vector)
	string line2; //A second string variable to be used as a string stream in order to store input as a string (for the second vector)

	
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

	//After getting both of the vectors, we will now send them to the same_vec function to evaluate them
	same_vec(vector1, vector2);

	//The following were for testing and therefore are commented out of the final code:
	//vector<int> test1 = { 5,5,4,3,2,1,5};
	//vector<int> test2 = { 1, 2, 3, 4, 5 };


		

	return 0;
}

