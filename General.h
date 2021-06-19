#include<iostream>
#include<vector>
#include<ctime>
#include<string>
#include<fstream>
#include"Textable.h"

using namespace std;

struct TaxiInfo{
	int id;
	string plate;
	string engine;
	int year;
	string model;
	string category;
	string driver;
	string dui;
	string socialNumber;
	string phoneNumber;
};

struct Trip {
	int id;
	string pickUpAddress, destinyAddress;
	float cost;
};

struct TaxiQueue {
	int id;
	string category;
};

vector<TaxiInfo> loadDataFromTxtFile(){
	string line;
	TaxiInfo ingreso;
	vector<TaxiInfo> taxisInfo;
	ifstream myfile ("example.txt");
	
	if (myfile.is_open()) {
		
		while (true) {
		    getline(myfile,line);
		      	if(line.length()!=0) {
			      	ingreso.id= stoi(line);
			      	getline(myfile,line);
			      	ingreso.plate=line;
			      	getline(myfile,line);
			      	ingreso.engine=line;
			      	getline(myfile,line);
			      	ingreso.year=stoi(line);
			      	getline(myfile,line);
			      	ingreso.model=line;
			      	getline(myfile,line);
			      	ingreso.category=line;
			      	getline(myfile,line);
			      	ingreso.driver=line;
			      	getline(myfile,line);
			      	ingreso.dui=line;
			      	getline(myfile,line);
			      	ingreso.socialNumber=line;
			      	getline(myfile,line);
			      	ingreso.phoneNumber=line;
			      	taxisInfo.push_back(ingreso);
			  	}
				  	else {
				  		break;
				   }
		}
		    myfile.close();
  		}
  			else{
  			cout << "Unable to open file"<<endl; 	
  		}
  		return taxisInfo;
}


string getTaxi(vector<string> categories, vector<int> taxis, int id){
	for(int i =0; i<taxis.size();i++){
		if(taxis.at(i) == id){
			return categories.at(i);
		}
	}
}

bool checkForItemInt(vector<int> arr, int data){	
	for(int i=0;i<arr.size();i++)
	{
		if(arr.at(i)==data)
		{
			cout<<"Data is already registered at position ["<<i<<"].\nPlease Enter Data again.\n";
			return true;
		}
	}	
	return false;	
}

bool checkForItemInt(vector<string> arr, string data){
	for(int i=0;i<arr.size();i++)
	{
	if(arr.at(i)==data)
		{
			cout<<"Data is already registered at position ["<<i<<"].\nPlease Enter Data again.\n";
			return true;
		}
		else
		{
			return false;
		}
	}		
}

bool maskForOnlyCharacters(string data){
	for(int i=0;i<data.size();i++)
	{
	if(isdigit(data[i]))
		{
			cout<<"You can not use numbers here.\nPlease Enter Data again.\n"<<endl;
			return true;
		}
	}
	return false;
}

bool maskForOnlyNumbers(string data){
	for(int i=0;i<data.size();i++)
	{
	if(!isdigit(data[i]))
		{
			cout<<"You can not use characters here.\nPlease Enter Data again.\n"<<endl;
			return true;
		}
	}
	return false;
}

bool maskForCarPlates(string data){
	if(data[0] != 'P')
	{
		cout<<"Car plates should start with the letter P.\nPlease Enter Data again.\n"<<endl;
		return true;
	}
	
	if(data.size() <=1 || data.size() > 7)
	{
		cout<<"Car plates should have at least 1 number and a maximum of 6 numbers.\nPlease Enter Data again.\n"<<endl;
		return true;
	}
	
	for(int i=0;i<data.size();i++)
	{
	if(i == 0) continue;
	if(!isdigit(data[i]))
		{
			cout<<"You can not use characters here.\nPlease Enter Data again.\n"<<endl;
			return true;
		}
	}
	return false;
}

bool maskForModel(string data){
	
	if(!data.length()){
		cout<<"Model must have more than one number."<<endl;
		return true;
	}
	
	return false;
}

bool maskForEngineNumber(string data){
	if(data.size() < 10 || data.size() > 18)
	{
		cout<<"The Engine number should have between 10 and 18 characters/numbers.\nPlease Enter Data again.\n"<<endl;
		return true;
	}
		return false;
}

bool maskForYear(int data){
	time_t now = time(0);
    tm *ltm = localtime(&now);
   	if(data < 2010 || data > 1900 + ltm->tm_year) 
	{
		cout<<"The year of the car must be between 2010 and the current year.\nPlease Enter Data again.\n"<<endl;
		return true;
	}
   return false;
}

bool checkStringLength(string data, int expectedLength, string message){
	if(data.length() != expectedLength){
		cout<<message<<"\nPlease Enter Data again.\n"<<endl;
		return true;
	}
}

bool maskForDui(string data){
	
	if(checkStringLength(data, 9, "The DUI must have 9 numbers.")) return true;
	
	if(data[0] != '0' || data[1] > '6'){
		cout<<"The DUI should start with 0 and 6.\nPlease Enter Data again.\n"<<endl;
		return true;
	}
	
	return maskForOnlyNumbers(data);
}

bool maskForSocialNumber(string data){
	
	if(checkStringLength(data, 12, "Social number should have 12 numbers.")) return true;
	
	return maskForOnlyNumbers(data);
}

bool maskForPhoneNumber(string data){
	
	if(checkStringLength(data, 8, "Phone number should have 8 numbers.")) return true;
	
	return maskForOnlyNumbers(data);
}

void printTable(vector<int> taxis, vector<string> plates, vector<string> engines, vector<int> years, vector<string> models, vector<string> categories, vector<string> drivers, vector<string> duis, vector<string> socialNumbers, vector<string> phoneNumbers)
{
	TextTable t( '-', '|', '+' );
	t.add("Order");
	t.add("ID");
	t.add("Plate Number");
	t.add("Engine Number");
	t.add("Year");
	t.add("Category");
	t.add("Model");
	t.add("Driver Name");
	t.add("DUI");
	t.add("Social Number");
	t.add("Phone Number");
	t.endOfRow();
	for(int i=0; i<taxis.size();i++)
	{
		t.add(to_string(i));
		t.add(to_string(taxis.at(i)));
		t.add(plates.at(i));
		t.add(engines.at(i));
		t.add(to_string(years.at(i)));
		t.add(categories.at(i));
		t.add(models.at(i));
		t.add(drivers.at(i));
		t.add(duis.at(i));
		t.add(socialNumbers.at(i));
		t.add(phoneNumbers.at(i));
		t.endOfRow();	
	}
	t.setAlignment( 2, TextTable::Alignment::RIGHT );
	cout<<t;
}


void printTableForTaxisOnRoute(vector<Trip> trips)
{
	TextTable t( '-', '|', '+' );
	t.add("Order");
	t.add("Taxi ID");
	t.add("Pickup address");
	t.add("Destiny address");
	t.add("Trip cost");
	t.endOfRow();
	for(int i=0; i<trips.size();i++)
	{
		t.add(to_string(i));
		t.add(to_string(trips.at(i).id));
		t.add(trips.at(i).pickUpAddress);
		t.add(trips.at(i).destinyAddress);
		t.add(to_string(trips.at(i).cost));
		t.endOfRow();	
	}
	t.setAlignment( 4, TextTable::Alignment::RIGHT );
	cout<<t;
}

void printTableForTaxisInQueue(vector<TaxiQueue> taxiQueue)
{
	TextTable t( '-', '|', '+' );
	t.add("Order");
	t.add("Taxi ID");
	t.add("Category");
	t.endOfRow();
	for(int i=0; i<taxiQueue.size();i++)
	{
		t.add(to_string(i));
		t.add(to_string(taxiQueue.at(i).id));
		t.add(taxiQueue.at(i).category);
		t.endOfRow();	
	}
	t.setAlignment( 4, TextTable::Alignment::RIGHT );
	cout<<t;
}
