#include<iostream>
#include<vector>
#include<string>
#include<conio.h>
#include"General.h"
#include<limits>
using namespace std;

int main(){
	char response='\0';
	int option;
	int id;
	int idToSend;
	string driverName;
	string plateNumber;
	string engineNumber;
	string model;
	string dui;
	string socialNumber;
	string phoneNumber;
	string category;
	string executive = "executive";
	string traditional = "traditional";
	string pickUpAddress;
	string destinyAddress;
	float cost;
	int year;
	cout<<"Taxi queue system\t\n";
	vector<int> taxis;
	vector<string> drivers;
	vector<string> plates;
	vector<string> engines;
	vector<string> models;
	vector<string> duis;
	vector<string> socialNumbers; 
	vector<string> phoneNumbers; 
	vector<string> categories; 
	vector<int> years;
	vector<TaxiQueue> taxisQueue;
	vector<Trip> trips;
	bool checkValue;
	int count;
	do{
		system("cls");
		cout<<"Main menu options:\n\n"<<endl;
		cout<<"\t\t1. Add New Taxi to standby queue"<<endl;
		cout<<"\t\t2. Check for actual data"<<endl;
		cout<<"\t\t3. Sent Taxi to a Client"<<endl;
		cout<<"\t\t4. Check for taxis in routes"<<endl;
		cout<<"\t\t5. Reinsert a taxi to avaialable queue"<<endl;
		cout<<"\t\t6. Exit program"<<endl<<endl;
		cout<<"Please, input your option: ";
		cin>>option;
		switch(option){
			case 1:
				do{
					cout<<"Taxi ID: ";
					if (cin >> id)
					{
						checkValue = false;
					} else 
					{
					    cout << "Value must be an integer.\nPlease Enter Data again.\n" << endl;
					    cin.clear();
					    cin.ignore(numeric_limits<streamsize>::max(), '\n');
					    checkValue = true;
					}
				
				}while(checkValue || checkForItemInt(taxis, id));
				taxis.push_back(id);
				
				do{
					cout<<"Driver Name: ";
					cin.ignore();
					getline(cin,driverName);
				}while(maskForOnlyCharacters(driverName) || checkForItemInt(drivers, driverName));
				drivers.push_back(driverName);
				
				do{
					cout<<"Plate Number: ";
					getline(cin,plateNumber);
				}while(maskForCarPlates(plateNumber) || checkForItemInt(plates, plateNumber));
				plates.push_back(plateNumber);
				
				do{
					cout<<"Engine Number: ";
					getline(cin,engineNumber);
				}while(maskForEngineNumber(engineNumber) || checkForItemInt(engines, engineNumber));
				engines.push_back(engineNumber);
				
				do{
					cout<<"Model: ";
					getline(cin, model);
				}while(maskForModel(model));
				models.push_back(model);

				do
				{
					cout<<"Year: ";
					if (cin >> year)
					{
						checkValue = false;
        				continue;
					} else 
					{
					    cout << "Value must be an integer.\nPlease Enter Data again.\n" << endl;
					    cin.clear();
					    cin.ignore(numeric_limits<streamsize>::max(), '\n');
					    checkValue = true;
					}
					
				}while(checkValue || maskForYear(year)) ;
				years.push_back(year);
				
				if(year >= 2015){
					
					cout<<"Choose a category:\n"<<endl;
					cout<<"\t1. Executive car"<<endl;
					cout<<"\t2. Traditional car"<<endl;
					checkValue = false;
							
					do{
					cin>>option;
					switch(option){
						case 1:
							category = executive;
							break;
						case 2:
							category = traditional;
							break;
						default:
							cout<<"Non correct option has been chosen."<<endl;
							checkValue = true;
							break;
					}
						
					}while(checkValue);	
				
				}else {
					cout<<"\nThe category of this car is: Traditional"<<endl;
					category = traditional;
				}
				
				do{
					cout<<"DUI: ";
					getline(cin, dui);
				}while(maskForDui(dui) || checkForItemInt(duis, dui));
				duis.push_back(dui);
				
				do{
					cout<<"Social Number: ";
					getline(cin, socialNumber);
				}while(maskForSocialNumber(socialNumber) || checkForItemInt(socialNumbers, socialNumber));
				socialNumbers.push_back(socialNumber);
				
				do{
					cout<<"Phone number: ";
					getline(cin, phoneNumber);
				}while(maskForPhoneNumber(phoneNumber) || checkForItemInt(phoneNumbers, phoneNumber));
				phoneNumbers.push_back(phoneNumber);
				
				categories.push_back(category);
				taxisQueue.push_back({id, category});
				category = "";
				
			break;
			case 2:		
				printTableForTaxisInQueue(taxisQueue);
				cout<<endl;
				printTable(taxis, plates, engines, years, models, categories, drivers, duis, socialNumbers, phoneNumbers);
			break;
			case 3:
				//code logic for sending taxis here
				cout<<"Choose a category:\n"<<endl;
				cout<<"\t1. Executive car"<<endl;
				cout<<"\t2. Traditional car"<<endl;
				checkValue = false;
							
				do{
				cin>>option;
				category = "";
				switch(option){
					case 1:
						category = executive;
					break;
					case 2:
						category = traditional;
					break;
					default:
						cout<<"Non correct option has been chosen."<<endl;
						checkValue = true;
						break;
				}
							
				}while(checkValue);	
			
				cin.ignore();
				cout<<"Where to pickup: ";
				getline(cin, pickUpAddress);
				
				cout<<"Destiny address: ";
				getline(cin, destinyAddress);
				
				cout<<"Cost: ";
				cin>>cost;
				count = 0;
				cout<<"count: "<<count<<endl;
				for (auto it = taxisQueue.begin(); it != taxisQueue.end(); it++){
					if((*it).category == category){
						cout<<(*it).category<<endl;
						idToSend = (*it).id;
						cout<<(*it).id<<endl;
						taxisQueue.erase(it + count);
						break;
					}
					count++;
				}
							
				trips.push_back({idToSend, pickUpAddress, destinyAddress, cost});
       		 		
			break;
			case 4:
				//code logic for on route checks				
				printTableForTaxisOnRoute(trips);
			break;
			case 5:
				//code logic for reinset taxis into avaialable queue
				do{
					cout<<"Which Taxi ID do you want to return: ";
					if (cin >> id)
					{
						checkValue = false;
					} else 
					{
					    cout << "Value must be an integer.\nPlease Enter Data again.\n" << endl;
					    cin.clear();
					    cin.ignore(numeric_limits<streamsize>::max(), '\n');
					    checkValue = true;
					}
				}while(checkValue);
				
				for (auto it = trips.begin(); it != trips.end(); ++it){
				
					if((*it).id == id){
						trips.erase(it);
						taxisQueue.push_back({(*it).id, getTaxi(categories, taxis,id)});
						 cout << "Taxi returned to the queue successfully." << endl;
						break;
					}
				}
				
			break;
			case 6:
				cout<<"Program has ended...";
				system("pause");
				system("exit");
			break;
			default:
				cout<<"Non correct option has been chosen."<<endl;
			break;
		}
  	cout<<"Want to continue? (Y/N)?: ";
  	response=getch();
	}while(response=='Y' || response=='y');	
}

