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
	vector<TaxiInfo> taxisInfo;
	TaxiInfo ingresoTaxi;
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
	
	taxisInfo = loadDataFromTxtFile();
		for(int i=0; i< taxisInfo.size() ;i++) {
			cout<<taxisInfo[i].id<<endl;
			cout<<taxisInfo[i].plate<<endl;
			cout<<taxisInfo[i].engine<<endl;
			cout<<taxisInfo[i].year<<endl;
			cout<<taxisInfo[i].model<<endl;
			cout<<taxisInfo[i].category<<endl;
			cout<<taxisInfo[i].driver<<endl;
			cout<<taxisInfo[i].dui<<endl;
			cout<<taxisInfo[i].socialNumber<<endl;
			cout<<taxisInfo[i].phoneNumber<<endl;
		}

	
	do{
//		system("cls");
		cout<<"Main menu options:\n\n"<<endl;
		cout<<"\t\t1. Add New Taxi to standby queue"<<endl;
		cout<<"\t\t2. Check for actual data"<<endl;
		cout<<"\t\t3. Sent Taxi to a Client"<<endl;
		cout<<"\t\t4. Check for taxis in routes"<<endl;
		cout<<"\t\t5. Reinsert a taxi to avaialable queue"<<endl;
		cout<<"\t\t6. Exit program"<<endl<<endl;
		cout<<"Please, input your option: ";
		cin>>option;
		
		taxis.clear();
		drivers.clear();
		plates.clear();
		engines.clear();
		models.clear();
		duis.clear();
		socialNumbers.clear();
		phoneNumbers.clear();
		categories.clear();
		years.clear();
		
		for(int i=0; i<0 ;i++) {
			taxis.push_back(taxisInfo[i].id);
			drivers.push_back(taxisInfo[i].driver);
			plates.push_back(taxisInfo[i].plate);
			engines.push_back(taxisInfo[i].engine);
			models.push_back(taxisInfo[i].model);
			duis.push_back(taxisInfo[i].dui);
			socialNumbers.push_back(taxisInfo[i].socialNumber);
			phoneNumbers.push_back(taxisInfo[i].phoneNumber);
			categories.push_back(taxisInfo[i].category);
			years.push_back(taxisInfo[i].year);
		}
		
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
				ingresoTaxi.id = id;
//				taxis.push_back(id);
				
				do{
					cout<<"Driver Name: ";
					cin.ignore();
					getline(cin,driverName);
					
				}while(maskForOnlyCharacters(driverName) || checkForItemInt(drivers, driverName));
				ingresoTaxi.driver = driverName;
//				drivers.push_back(driverName);
				
				do{
					cout<<"Plate Number: ";
					getline(cin,plateNumber);
				}while(maskForCarPlates(plateNumber) || checkForItemInt(plates, plateNumber));
				ingresoTaxi.plate = plateNumber;
//				plates.push_back(plateNumber);
				
				do{
					cout<<"Engine Number: ";
					getline(cin,engineNumber);
				}while(maskForEngineNumber(engineNumber) || checkForItemInt(engines, engineNumber));
				ingresoTaxi.engine = engineNumber;
//				engines.push_back(engineNumber);
				
				do{
					cout<<"Model: ";
					getline(cin, model);
				}while(maskForModel(model));
				ingresoTaxi.model = model;
//				models.push_back(model);

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
				ingresoTaxi.year = year;
//				years.push_back(year);
				
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
				ingresoTaxi.dui = dui;
//				duis.push_back(dui);
				
				do{
					cout<<"Social Number: ";
					getline(cin, socialNumber);
				}while(maskForSocialNumber(socialNumber) || checkForItemInt(socialNumbers, socialNumber));
				ingresoTaxi.socialNumber = socialNumber;
//				socialNumbers.push_back(socialNumber);
				
				do{
					cout<<"Phone number: ";
					getline(cin, phoneNumber);
				}while(maskForPhoneNumber(phoneNumber) || checkForItemInt(phoneNumbers, phoneNumber));
				ingresoTaxi.phoneNumber = phoneNumber;
//				phoneNumbers.push_back(phoneNumber);
				
				ingresoTaxi.category = category;
				taxisInfo.push_back(ingresoTaxi);
				categories.push_back(category);
				taxisQueue.push_back({id, category});
				category = "";
				
				
//				int hachy =  TaxiInfo.id;
//				typedef TaxiInfo hachy;
//				for(int i = 0; i < taxisInfo.size(); i++){
//					
//					cout<<"taxi Id in struct: "<<taxisInfo[i].id<<endl;
//				}

				
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

