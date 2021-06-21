#include<iostream>
#include<vector>
#include<string>
#include<conio.h>
#include"General.h"
#include<limits>
#include <ctime>
#include <stdio.h>
#include <time.h>

using namespace std;

int main() {
    char response = '\0';
    int option;
    int id;
    int idToSend;
    int selectedMonth;
    int countTrips;
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
    vector < TaxiInfo > taxisInfo;
    TaxiInfo taxiEntry;
    vector < int > taxis;
    vector < string > drivers;
    vector < string > plates;
    vector < string > engines;
    vector < string > models;
    vector < string > duis;
    vector < string > socialNumbers;
    vector < string > phoneNumbers;
    vector < string > categories;
    vector < int > years;
    vector < TaxiQueue > taxisQueue;
    vector < Trip > trips;
    vector < Trip > tripsIncompleted;
    vector < Trip > tripsCompleted;
    bool checkValue;

    time_t rawtime;
    tm * format;
    char dateChar[15];
    string dateString;

    float totalEarnings;
    string evaluateDate;

    taxisInfo = loadTaxisInfoDataFromTxtFile();

    if (taxisInfo.size() != 0) {

        for (int i = 0; i < taxisInfo.size(); i++) {
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
    }

    trips = loadTripsDataFromTxtFile();

    taxisQueue = loadQueueDataFromTxtFile();

    do {
        system("cls");
        cout << "Taxi queue system\t\n";
        cout << "Main menu options:\n\n" << endl;
        cout << "\t\t1. Add New Taxi to standby queue" << endl;
        cout << "\t\t2. Check for actual data" << endl;
        cout << "\t\t3. Sent Taxi to a Client" << endl;
        cout << "\t\t4. Check for taxis in routes" << endl;
        cout << "\t\t5. Reinsert a taxi to available queue" << endl;
        cout << "\t\t6. Reports" << endl;
        cout << "\t\t7. Exit program" << endl << endl;
        cout << "Please, input your option: ";
        cin >> option;

        switch (option) {
        case 1:
            do {
                cout << "Taxi ID: ";
                if (cin >> id) {
                    checkValue = false;
                } else {
                    cout << "Value must be an integer.\nPlease Enter Data again.\n" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                    checkValue = true;
                }

            } while (checkValue || checkForItemInt(taxis, id));
            taxiEntry.id = id;
            taxis.push_back(id);

            do {
                cout << "Driver Name: ";
                cin.ignore();
                getline(cin, driverName);

            } while (maskForOnlyCharacters(driverName) || checkForItemInt(drivers, driverName));
            taxiEntry.driver = driverName;
            drivers.push_back(driverName);

            do {
                cout << "Plate Number: ";
                getline(cin, plateNumber);
            } while (maskForCarPlates(plateNumber) || checkForItemInt(plates, plateNumber));
            taxiEntry.plate = plateNumber;
            plates.push_back(plateNumber);

            do {
                cout << "Engine Number: ";
                getline(cin, engineNumber);
            } while (maskForEngineNumber(engineNumber) || checkForItemInt(engines, engineNumber));
            taxiEntry.engine = engineNumber;
            engines.push_back(engineNumber);

            do {
                cout << "Model: ";
                getline(cin, model);
            } while (maskForModel(model));
            taxiEntry.model = model;
            models.push_back(model);

            do {
                cout << "Year: ";
                if (cin >> year) {
                    checkValue = false;
                    continue;
                } else {
                    cout << "Value must be an integer.\nPlease Enter Data again.\n" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                    checkValue = true;
                }

            } while (checkValue || maskForYear(year));
            taxiEntry.year = year;
            years.push_back(year);

            if (year >= 2015) {

                cout << "Choose a category:\n" << endl;
                cout << "\t1. Executive car" << endl;
                cout << "\t2. Traditional car" << endl;
                checkValue = false;

                do {
                    cin >> option;
                    switch (option) {
                    case 1:
                        category = executive;
                        checkValue = false;
                        break;
                    case 2:
                        category = traditional;
                        checkValue = false;
                        break;
                    default:
                        cout << "Non correct option has been chosen. Please, try again." << endl;
                        checkValue = true;
                        break;
                    }

                } while (checkValue);

            } else {
                cout << "\nThe category of this car is: Traditional" << endl;
                category = traditional;
            }

            do {
                cout << "DUI: ";
                getline(cin, dui);
            } while (maskForDui(dui) || checkForItemInt(duis, dui));
            taxiEntry.dui = dui;
            duis.push_back(dui);

            do {
                cout << "Social Number: ";
                getline(cin, socialNumber);
            } while (maskForSocialNumber(socialNumber) || checkForItemInt(socialNumbers, socialNumber));
            taxiEntry.socialNumber = socialNumber;
            socialNumbers.push_back(socialNumber);

            do {
                cout << "Phone number: ";
                getline(cin, phoneNumber);
            } while (maskForPhoneNumber(phoneNumber) || checkForItemInt(phoneNumbers, phoneNumber));
            taxiEntry.phoneNumber = phoneNumber;
            phoneNumbers.push_back(phoneNumber);

            taxiEntry.category = category;

            taxisInfo.push_back(taxiEntry);

            saveTaxiInfoInTxtFile(taxiEntry);

            categories.push_back(category);

            saveQueueInTxtFile({
                id,
                category
            });

            taxisQueue.push_back({
                id,
                category
            });
            category = "";

            break;
        case 2:
            printTableForTaxisInQueue(taxisQueue);
            cout << endl;
            printTable(taxis, plates, engines, years, models, categories, drivers, duis, socialNumbers, phoneNumbers);
            break;
        case 3:
            //code logic for sending taxis here
            cout << "Choose a category:\n" << endl;
            cout << "\t1. Executive car" << endl;
            cout << "\t2. Traditional car" << endl;
            checkValue = false;

            do {
                cin >> option;
                category = "";
                switch (option) {
                case 1:
                    category = executive;
                    checkValue = false;
                    break;
                case 2:
                    category = traditional;
                    checkValue = false;
                    break;
                default:
                    cout << "Non correct option has been chosen. Please, try again." << endl;
                    checkValue = true;
                    break;
                }

            } while (checkValue);

            cin.ignore();
            cout << "Where to pickup: ";
            getline(cin, pickUpAddress);

            cout << "Destiny address: ";
            getline(cin, destinyAddress);

            cout << "Cost: ";
            cin >> cost;

            rawtime = time(0);
            format = localtime( & rawtime);
            strftime(dateChar, 15, "%x", format);
            dateString = dateChar;

            for (int i = 0; i < taxisQueue.size(); i++) {
                if (taxisQueue[i].category == category) {
                    idToSend = taxisQueue[i].id;
                    taxisQueue.erase(taxisQueue.begin() + i);
                    deleteFromQueueInTxtFile(idToSend);
                    break;
                }
            }

            saveTripsInTxtFile({
                idToSend,
                pickUpAddress,
                destinyAddress,
                cost,
                dateString,
                completed: "false",
            });

            trips.push_back({
                idToSend,
                pickUpAddress,
                destinyAddress,
                cost,
                dateString,
                completed: "false",
            });

            cout << "Taxi sent successfully." << endl;

            break;
        case 4:
            //code logic for on route checks		
            tripsIncompleted.clear();
            for (int i = 0; i < trips.size(); i++) {
                if (trips[i].completed == "true") {
                    continue;
                }
                tripsIncompleted.push_back(trips[i]);
            }
            printTableForTaxisOnRoute(tripsIncompleted);
            break;
        case 5:
            //code logic for reinset taxis into avaialable queue
            do {
                cout << "Which Taxi ID do you want to return: ";
                if (cin >> id) {
                    checkValue = false;
                } else {
                    cout << "Value must be an integer.\nPlease Enter Data again.\n" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                    checkValue = true;
                }
            } while (checkValue);

            for (int i = 0; i < trips.size(); i++) {
                if (trips[i].id == id) {
                    updateTripCompletedInTxtFile(id);
                    trips = loadTripsDataFromTxtFile();

                    taxiEntry = getTaxi(taxisInfo, id);

                    saveQueueInTxtFile({
                        id,
                        taxiEntry.category
                    });
                    taxisQueue.push_back({
                        id,
                        taxiEntry.category
                    });
                    cout << "Taxi returned to the queue successfully." << endl;
                    id = 0;
                    break;
                }
            }

            if (id) {
                cout << "Taxi ID not found. Failed to return a taxi." << endl;
            }

            break;
        case 6:
            //code logic for reports
            cout << "Choose an option:\n" << endl;
            cout << "\t1. Check earnings for a specific month" << endl;
            cout << "\t2. Check monthly earnings of a specific taxi." << endl;
            cout << "\t3. Check earnings for a specific month" << endl;
            cout << "\t4. Check monthly earnings of a specific taxi." << endl;

            do {
                checkValue = false;
                cin >> option;
                switch (option) {
                case 1:
                    for (int i = 0; i < taxis.size(); i++) {
                        tripsCompleted.clear();
                        taxiEntry = getTaxi(taxisInfo, taxis[i]);
                        for (int j = 0; j < trips.size(); j++) {
                            if (trips[j].id == taxis[i] && trips[j].completed == "true") {
                                tripsCompleted.push_back(trips[j]);
                            }
                        }
                        cout << "Taxi Plate: " << taxiEntry.plate << ", Taxi ID: " << taxiEntry.id << endl;
                        printTableForTaxisOnRoute(tripsCompleted);
                        cout << endl;
                    }

                    break;
                case 2:
                    do {
                        cout << "Which Taxi ID do you want to query: ";
                        if (cin >> id) {
                            checkValue = false;
                        } else {
                            cout << "Value must be an integer.\nPlease Enter Data again.\n" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                            checkValue = true;
                        }
                    } while (checkValue);

                    for (int i = 0; i < taxis.size(); i++) {
                        if (taxis[i] == id) {
                            checkValue = false;
                            break;
                        } else {
                            checkValue = true;
                        }
                    }
                    if (checkValue) {
                        cout << "Taxi ID not found, please try again." << endl;
                        checkValue = false;
                    } else {
                        tripsCompleted.clear();
                        for (int j = 0; j < trips.size(); j++) {
                            if (trips[j].id == id && trips[j].completed == "true") {
                                tripsCompleted.push_back(trips[j]);
                            }
                        }

                        taxiEntry = getTaxi(taxisInfo, id);
                        cout << "Taxi Plate: " << taxiEntry.plate << ", Taxi ID: " << taxiEntry.id << endl;
                        printTableForTaxisOnRoute(tripsCompleted);
                        cout << endl;
                    }

                    break;
                case 3:
                    checkValue = false;
                    cout << "Choose an option:\n" << endl;
                    cout << "\t1. January" << endl;
                    cout << "\t2. February" << endl;
                    cout << "\t3. March" << endl;
                    cout << "\t4. April" << endl;
                    cout << "\t5. May" << endl;
                    cout << "\t6. June" << endl;
                    cout << "\t7. July" << endl;
                    cout << "\t8. August" << endl;
                    cout << "\t9. September" << endl;
                    cout << "\t10. October" << endl;
                    cout << "\t11. November" << endl;
                    cout << "\t12. December" << endl << endl;
                    cout << "Option: ";

                    do {
                        cin >> selectedMonth;
                        cout << "selectedmonth: " << selectedMonth << endl;
                        if (selectedMonth <= 0 || selectedMonth > 12) {
                            cout << "Non correct option has been chosen. Please, try again." << endl;
                        }
                    } while (selectedMonth <= 0 || selectedMonth > 12);

                    totalEarnings = 0;
                    for (int i = 0; i < trips.size(); i++) {
                        if (trips[i].completed == "false") {
                            continue;
                        }

                        evaluateDate = trips[i].date[0];
                        evaluateDate += trips[i].date[1];

                        if (stoi(evaluateDate) == selectedMonth) {
                            totalEarnings += trips[i].cost;
                        }
                    }

                    if (totalEarnings == 0) {
                        cout << "There is no data of month " << selectedMonth << ".\n" << endl;
                    } else {
                        cout << "Total earnings of month " << selectedMonth << " are $" << totalEarnings << "\n" << endl;
                    }

                    break;
                case 4:
                    checkValue = false;

                    do {
                        cout << "Enter the Taxi ID that you want to query: ";
                        if (cin >> id) {
                            checkValue = false;
                        } else {
                            cout << "Value must be an integer.\nPlease Enter Data again.\n" << endl;
                            cin.clear();
                            cin.ignore(numeric_limits < streamsize > ::max(), '\n');
                            checkValue = true;
                        }
                    } while (checkValue);

                    totalEarnings = 0;
                    for (int i = 0; i < trips.size(); i++) {
                        if (trips[i].completed == "false") {
                            continue;
                        }

                        if (trips[i].id == id) {
                            totalEarnings += trips[i].cost;
                        }
                    }

                    if (totalEarnings == 0) {
                        cout << "There is no data of Taxi ID " << id << " .\n" << endl;
                    } else {
                        taxiEntry = getTaxi(taxisInfo, id);

                        cout << "Total earnings of Taxi ID " << id << " with plates: " << taxiEntry.plate << " are $" << totalEarnings << "\n" << endl;
                    }

                    break;
                default:
                    cout << "Non correct option has been chosen. Please, try again." << endl;
                    checkValue = true;
                    break;
                }

            } while (checkValue);
            break;
        case 7:
            cout << "Program has ended...";
            system("pause");
            system("exit");
            break;
        default:
            cout << "Non correct option has been chosen." << endl;
            break;
        }
        cout << "Want to continue? (Y/N)?: ";
        response = getch();
    } while (response == 'Y' || response == 'y');
}
