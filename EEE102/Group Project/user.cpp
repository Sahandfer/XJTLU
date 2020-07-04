#include "user.h"

int ID = 1;
int BC1counter = 0;
int BC2counter = 0;
int SC1counter = 0;
int SC2counter = 0;
int SC3counter = 0;
int SC4counter = 0;

vector<string> split(const string &s, const string &separator) {
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()) {
		//find the fist character which is saperator
		int flag = 0;
		while (i != s.size() && flag == 0) {
			flag = 1;
			for (string_size x = 0; x < separator.size(); ++x)
				if (s[i] == separator[x]) {
					++i;
					flag = 0;
					break;
				}
		}

		//find another seperator and put the middle info
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0) {
			for (string_size x = 0; x < separator.size(); ++x)
				if (s[j] == separator[x]) {
					flag = 1;
					break;
				}
			if (flag == 0)
				++j;
		}
		if (i != j) {
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}

double user::getDebt() {
	return 1;
}

void user::increaseDebt(double amount) {

}


void user::cargoCreater() 
{
	for (int i = 0; i < 499; i++) { //To initiate the 500 standard cargo objects for the two big warehouses
		BW1[i] = cargo(1, 20);
		BW2[i] = cargo(1, 20);
	}

	for (int i = 0; i < 399; i++) { //To initiate the 400 small cargo objects for the four small warehouses
		SW1[i] = cargo(2, 10);
		SW2[i] = cargo(2, 10);
		SW3[i] = cargo(2, 10);
		SW4[i] = cargo(2, 10);
	}
}

void user::user_dataWrite()
{
	ofstream DataFileW;
	DataFileW.open("UserDataFile.txt", std::ios::out | std::ios::app);  //Write the content in the .txt File and create a new one if it is not exit
	if (!DataFileW.is_open())
		return;
	if (ID == 1) 
	{
		DataFileW << endl;
		DataFileW << "Name: " << name << endl;
		DataFileW << "Authority: customer" << endl << endl;

		DataFileW << "BW1Cargo: ";
		for (int i = 0; i < BW1cargoOwned.size(); i++)
			DataFileW << BW1cargoOwned.at(i) << " ";
		DataFileW << endl;

		DataFileW << "BW2Cargo: ";
		for (int i = 0; i < BW2cargoOwned.size(); i++)
			DataFileW << BW2cargoOwned.at(i) << " ";
		DataFileW << endl;

		DataFileW << "SW1Cargo: ";
		for (int i = 0; i < SW1cargoOwned.size(); i++)
			DataFileW << SW1cargoOwned.at(i) << " ";
		DataFileW << endl;

		DataFileW << "SW2Cargo: ";
		for (int i = 0; i < SW2cargoOwned.size(); i++)
			DataFileW << SW2cargoOwned.at(i) << " ";
		DataFileW << endl;

		DataFileW << "SW3Cargo: ";
		for (int i = 0; i < SW3cargoOwned.size(); i++)
			DataFileW << SW3cargoOwned.at(i) << " ";
		DataFileW << endl;

		DataFileW << "SW4Cargo: ";
		for (int i = 0; i < SW4cargoOwned.size(); i++)
			DataFileW << SW4cargoOwned.at(i) << " ";
		DataFileW << endl;
	}
	DataFileW.close();
}


bool user::user_dataLoad()
{
	char buffer[256];
	bool isLoad = false;
	bool isExtName = false;
	ifstream DataFileR("UserDataFile.txt");
	if (!DataFileR.is_open())
	{
		cout << "Error opening file";
		exit(1);
	}
	while (!DataFileR.eof())
	{
		DataFileR.getline(buffer, 1000);
		vector<string> res = split(buffer, " ");
		res.resize(500);
		if (res[0] == "Name:")
		{
			isLoad = false;
			if (res[1] == name)
			{
				isLoad = true;
				isExtName = true;
			}
		}
		else if ((res[0] == "Authority:")&&(isLoad))
		{
			if (res[1] == "keeper")
			{
				ID = 0;
			}
			else if(res[1] == "customer")
			{
				ID = 1;
			}
		}
		else if (res[0] == "BW1Cargo:" && isLoad &&(ID==1))
		{
			BC1counter = 0;
			vector<int> cargoOwnedtemp;
			for (int i = 0; i < res.size(); i++)
			{
				int resInt = atoi(res[i].c_str());
				if (resInt != 0)
				{
					BW1cargoOwned.push_back(resInt);
					BC1counter++;
					//cout << resInt << endl;
				}
			}
			reverse(BW1cargoOwned.begin(), BW1cargoOwned.end());
			for (int i = 0; i < BW1cargoOwned.size(); i++)
			{
				cargoOwnedtemp.push_back(BW1cargoOwned[i]);
			}
			BW1cargoOwned.clear();
			for (int i = 0; i < BC1counter; i++) 
			{
				if (cargoOwnedtemp[i] != 0) 
				{
					BW1cargoOwned.push_back(cargoOwnedtemp[i]);
					//cout << cargoOwnedtemp[i] << " ";
				}
			}
			reverse(BW1cargoOwned.begin(), BW1cargoOwned.end());
		}
		else if (res[0] == "BW2Cargo:" && isLoad && (ID == 1))
		{
			BC2counter = 0;
			vector<int> cargoOwnedtemp;
			for (int i = 0; i < res.size(); i++)
			{
				int resInt = atoi(res[i].c_str());
				if (resInt != 0)
				{
					BW2cargoOwned.push_back(resInt);
					BC2counter++;
					//cout << BC2counter << endl;
				}
			}
			reverse(BW2cargoOwned.begin(), BW2cargoOwned.end());
			for (int i = 0; i < BW2cargoOwned.size(); i++)
			{
				cargoOwnedtemp.push_back(BW2cargoOwned[i]);
			}
			BW2cargoOwned.clear();
			for (int i = 0; i < BC2counter; i++)
			{
				if (cargoOwnedtemp[i] != 0)
					BW2cargoOwned.push_back(cargoOwnedtemp[i]);
			}
			reverse(BW2cargoOwned.begin(), BW2cargoOwned.end());
		}
		else if (res[0] == "SW1Cargo:" && isLoad && (ID==1))
		{
			SC1counter = 0;
			vector<int> cargoOwnedtemp;
			for (int i = 0; i < res.size(); i++)
			{
				int resInt = atoi(res[i].c_str());
				if (resInt != 0)
				{
					SW1cargoOwned.push_back(resInt);
					SC1counter++;
					//cout << SC1counter << endl;
				}
			}
			reverse(SW1cargoOwned.begin(), SW1cargoOwned.end());
			for (int i = 0; i < SW1cargoOwned.size(); i++)
			{
				cargoOwnedtemp.push_back(SW1cargoOwned[i]);
			}
			SW1cargoOwned.clear();
			for (int i = 0; i < SC1counter; i++)
			{
				if (cargoOwnedtemp[i] != 0)
					SW1cargoOwned.push_back(cargoOwnedtemp[i]);
			}
			reverse(SW1cargoOwned.begin(), SW1cargoOwned.end());
		}
		else if (res[0] == "SW2Cargo:" && isLoad && (ID == 1))
		{
			SC2counter = 0;
			vector<int> cargoOwnedtemp;
			for (int i = 0; i < res.size(); i++)
			{
				int resInt = atoi(res[i].c_str());
				if (resInt != 0)
				{
					SW2cargoOwned.push_back(resInt);
					SC2counter++;
					//cout << SC2counter << endl;
				}
			}
			reverse(SW2cargoOwned.begin(), SW2cargoOwned.end());
			for (int i = 0; i < SW2cargoOwned.size(); i++)
			{
				cargoOwnedtemp.push_back(SW2cargoOwned[i]);
			}
			SW2cargoOwned.clear();
			for (int i = 0; i < SC2counter; i++)
			{
				if (cargoOwnedtemp[i] != 0)
					SW2cargoOwned.push_back(cargoOwnedtemp[i]);
			}
			reverse(SW2cargoOwned.begin(), SW2cargoOwned.end());
		}
		else if (res[0] == "SW3Cargo:" && isLoad && (ID == 1))
		{
			SC3counter = 0;
			vector<int> cargoOwnedtemp;
			for (int i = 0; i < res.size(); i++)
			{
				int resInt = atoi(res[i].c_str());
				if (resInt != 0)
				{
					SW3cargoOwned.push_back(resInt);
					SC3counter++;
					//cout << SC3counter << endl;
				}
			}
			reverse(SW3cargoOwned.begin(), SW3cargoOwned.end());
			for (int i = 0; i < SW3cargoOwned.size(); i++)
			{
				cargoOwnedtemp.push_back(SW3cargoOwned[i]);
			}
			SW3cargoOwned.clear();
			for (int i = 0; i < SC3counter; i++)
			{
				if (cargoOwnedtemp[i] != 0)
					SW3cargoOwned.push_back(cargoOwnedtemp[i]);
			}
			reverse(SW3cargoOwned.begin(), SW3cargoOwned.end());
		}
		else if (res[0] == "SW4Cargo:" && isLoad && (ID == 1))
		{
			SC4counter = 0;
			vector<int> cargoOwnedtemp;
			for (int i = 0; i < res.size(); i++)
			{
				int resInt = atoi(res[i].c_str());
				if (resInt != 0)
				{
					SW4cargoOwned.push_back(resInt);
					SC4counter++;
					//cout << SC4counter << endl;
				}
			}
			reverse(SW4cargoOwned.begin(), SW4cargoOwned.end());
			for (int i = 0; i < SW4cargoOwned.size(); i++)
			{
				cargoOwnedtemp.push_back(SW4cargoOwned[i]);
			}
			SW4cargoOwned.clear();
			for (int i = 0; i < SC4counter; i++)
			{
				if (cargoOwnedtemp[i] != 0)
					SW4cargoOwned.push_back(cargoOwnedtemp[i]);
			}
			reverse(SW4cargoOwned.begin(), SW4cargoOwned.end());
		}
	}

	if (isExtName)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void user::cargo_dataWrite(int houseNo,int cargoNo,string owner_in,int price_in,int size_in) 
{
	if (houseNo == 1)
	{
		ofstream DataFileW;
		DataFileW.open("BW1DataFile.txt", std::ios::out | std::ios::app);  //Write the content in the .txt File and create a new one if it is not exit
		if (!DataFileW.is_open())
			return;
		DataFileW << endl;
		DataFileW << "Cargo: " << cargoNo << endl;
		DataFileW << "Owner: " << owner_in << endl;
		DataFileW << "Price: " << price_in << endl;
		DataFileW << "Size: " << size_in << endl;
		DataFileW.close();
	}
	if (houseNo == 2)
	{
		ofstream DataFileW;
		DataFileW.open("BW2DataFile.txt", std::ios::out | std::ios::app);  //Write the content in the .txt File and create a new one if it is not exit
		if (!DataFileW.is_open())
			return;
		DataFileW << endl;
		DataFileW << "Cargo: " << cargoNo << endl;
		DataFileW << "Owner: " << owner_in << endl;
		DataFileW << "Price: " << price_in << endl;
		DataFileW << "Size: " << size_in << endl;
		DataFileW.close();
	}
	if (houseNo == 3)
	{
		ofstream DataFileW;
		DataFileW.open("SW1DataFile.txt", std::ios::out | std::ios::app);  //Write the content in the .txt File and create a new one if it is not exit
		if (!DataFileW.is_open())
			return;
		DataFileW << endl;
		DataFileW << "Cargo: " << cargoNo << endl;
		DataFileW << "Owner: " << owner_in << endl;
		DataFileW << "Price: " << price_in << endl;
		DataFileW << "Size: " << size_in << endl;
		DataFileW.close();
	}
	if (houseNo == 4)
	{
		ofstream DataFileW;
		DataFileW.open("SW2DataFile.txt", std::ios::out | std::ios::app);  //Write the content in the .txt File and create a new one if it is not exit
		if (!DataFileW.is_open())
			return;
		DataFileW << endl;
		DataFileW << "Cargo: " << cargoNo << endl;
		DataFileW << "Owner: " << owner_in << endl;
		DataFileW << "Price: " << price_in << endl;
		DataFileW << "Size: " << size_in << endl;
		DataFileW.close();
	}
	if (houseNo == 5)
	{
		ofstream DataFileW;
		DataFileW.open("SW3DataFile.txt", std::ios::out | std::ios::app);  //Write the content in the .txt File and create a new one if it is not exit
		if (!DataFileW.is_open())
			return;
		DataFileW << endl;
		DataFileW << "Cargo: " << cargoNo << endl;
		DataFileW << "Owner: " << owner_in << endl;
		DataFileW << "Price: " << price_in << endl;
		DataFileW << "Size: " << size_in << endl;
		DataFileW.close();
	}
	if (houseNo == 6)
	{
		ofstream DataFileW;
		DataFileW.open("SW4DataFile.txt", std::ios::out | std::ios::app);  //Write the content in the .txt File and create a new one if it is not exit
		if (!DataFileW.is_open())
			return;
		DataFileW << endl;
		DataFileW << "Cargo: " << cargoNo << endl;
		DataFileW << "Owner: " << owner_in << endl;
		DataFileW << "Price: " << price_in << endl;
		DataFileW << "Size: " << size_in << endl;
		DataFileW.close();
	}
}

int user::pass_Size(int size) 
{
	return size;
}

void user::cargo_dataLoad(int houseNo)
{
	int resInt;
	if (houseNo == 1)
	{
		char buffer[256];
		ifstream DataFileR("BW1DataFile.txt");
		if (!DataFileR.is_open())
		{
			cout << "Error opening file";
			exit(1);
		}
		int N = 0;
		while (!DataFileR.eof())
		{
			DataFileR.getline(buffer, 1000);
			vector<string> res = split(buffer, " ");
			res.resize(25);
			if (res[0] == "Cargo:")
			{
				resInt = atoi(res[1].c_str())-1;
				//cout<<"cargo: "<<res[1]<<endl;
				BW1[resInt].setEmpty(false);
				N++;
			}
			else if (res[0] == "Owner:")
			{
				BW1[resInt].setOwner(res[1]);
				//cout << "owner: " << res[1] <<" "<< BW1[resInt].getOwner()<< endl;
				if (res[1] == "NoNAME")
				{
					BW1[resInt].setEmpty(true);
					N--;
				}

			}
			else if (res[0] == "Price:")
			{
				int resMoney = atoi(res[1].c_str());
				BW1[resInt].setPrice(resMoney);
				//cout << "price: " << res[1] << " " << BW1[resInt].getPrice() << endl;
			}
			else if (res[0] == "Size:") 
			{
				int res1 = atoi(res[1].c_str());
				if((res1==1)||(res1==2))
					BW1[resInt].setSize(res1);
			}
		}
		if (N > 500)
			BW1->setEmpty(false);
	}
	else if (houseNo == 2)
	{
		char buffer[256];
		ifstream DataFileR("BW2DataFile.txt");
		int N = 0;
		if (!DataFileR.is_open())
		{
			cout << "Error opening file";
			exit(1);
		}
		while (!DataFileR.eof())
		{
			DataFileR.getline(buffer, 1000);
			vector<string> res = split(buffer, " ");
			res.resize(500);
			if (res[0] == "Cargo:")
			{
				resInt = atoi(res[1].c_str())-1; 
				BW2[resInt].setEmpty(false);
				N++;
			}
			else if (res[0] == "Owner:")
			{
				if (res[1] == "NoNAME") 
				{
					BW2[resInt].setOwner(res[1]);
					N--;
				}
			}
			else if (res[0] == "Price:" )
			{
				int resMoney = atoi(res[1].c_str());
				BW2[resInt].setPrice(resMoney);
			}
		}
		if (N > 500)
			BW2->setEmpty(false);
	}
	else if (houseNo == 3)
	{
		char buffer[256];
		int N = 0;
		ifstream DataFileR("SW1DataFile.txt");
		if (!DataFileR.is_open())
		{
			cout << "Error opening file";
			exit(1);
		}
		while (!DataFileR.eof())
		{
			DataFileR.getline(buffer, 1000);
			vector<string> res = split(buffer, " ");
			res.resize(500);
			if (res[0] == "Cargo:")
			{
				resInt = atoi(res[1].c_str())-1;
				SW1[resInt].setEmpty(false);
				N++;
			}
			else if (res[0] == "Owner:")
			{
				SW1[resInt].setOwner(res[1]);
				N--;
			}
			else if (res[0] == "Price:")
			{
				int resMoney = atoi(res[1].c_str());
				SW1[resInt].setPrice(resMoney);
			}
		}
		if (N > 400)
			SW1->setEmpty(false);
	}
	else if (houseNo == 4)
	{
		char buffer[256];
		int N = 0;
		ifstream DataFileR("BW1DataFile.txt");
		if (!DataFileR.is_open())
		{
			cout << "Error opening file";
			exit(1);
		}
		while (!DataFileR.eof())
		{
			DataFileR.getline(buffer, 1000);
			vector<string> res = split(buffer, " ");
			res.resize(500);
			if (res[0] == "Cargo:")
			{
				resInt = atoi(res[1].c_str())-1;
				SW2[resInt].setEmpty(false);
				N++;
			}
			else if (res[0] == "Owner:")
			{
				if (res[1] == "NoNAME")
				{
					SW2[resInt].setOwner(res[1]);
					N--;
				}
			}
			else if (res[0] == "Price:")
			{
				int resMoney = atoi(res[1].c_str());
				SW2[resInt].setPrice(resMoney);
			}
		}
		if (N > 400)
			SW2->setEmpty(false);
	}
	else if (houseNo == 5)
	{
		char buffer[256];
		int N = 0;
		ifstream DataFileR("SW3DataFile.txt");
		if (!DataFileR.is_open())
		{
			cout << "Error opening file";
			exit(1);
		}
		while (!DataFileR.eof())
		{
			DataFileR.getline(buffer, 1000);
			vector<string> res = split(buffer, " ");
			res.resize(500);
			if (res[0] == "Cargo:")
			{
				resInt = atoi(res[1].c_str())-1;
				SW3[resInt].setEmpty(false);
				N++;
			}
			else if (res[0] == "Owner:")
			{
				if (res[1] == "NoNAME") 
				{
					SW3[resInt].setOwner(res[1]);
					N--;
				}
			}
			else if (res[0] == "Price:")
			{
				int resMoney = atoi(res[1].c_str());
				SW3[resInt].setPrice(resMoney);
			}
		}
		if (N > 400)
			SW3->setEmpty(false);
	}
	else if (houseNo == 6)
	{
		char buffer[256];
		int N = 0;
		ifstream DataFileR("SW4DataFile.txt");
		if (!DataFileR.is_open())
		{
			cout << "Error opening file";
			exit(1);
		}
		while (!DataFileR.eof())
		{
			DataFileR.getline(buffer, 1000);
			vector<string> res = split(buffer, " ");
			res.resize(500);
			if (res[0] == "Cargo:")
			{
				resInt = atoi(res[1].c_str())-1;
				SW4[resInt].setEmpty(false);
				N++;
			}
			else if (res[0] == "Owner:")
			{
				if (res[1] == "NoNAME") 
				{
					SW4[resInt].setOwner(res[1]);
					N--;
				}
			}
			else if (res[0] == "Price:")
			{
				int resMoney = atoi(res[1].c_str());
				SW4[resInt].setPrice(resMoney);
			}
		}
		if (N > 400)
			SW4->setEmpty(false);
	}
}

string user::getName() {
	return name;
}
