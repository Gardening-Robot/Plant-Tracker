/*
 * File:   Source.cpp
 *
 * Last Update: 06/10
 * Added leap year support
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Plant.h"
#include "Year.h"

using std::vector;
using std::cout;
using std::cin;
using std::endl;

vector<Plant> dataInit(string fileName);
void harvestPlant(vector<Plant>& plants, string plantName, string date);
string allToString(vector<Plant> plants);
void writeToFile(vector<Plant> plants, string year);
bool checkDateFormat(string &date, int year);

int main()
{
    string yearS = "";
    cout << "Year to load: ";
    cin >> yearS;
    int year = stoi(yearS);
    vector<Plant> myPlants = dataInit(yearS + ".csv"); // import data from csv file to vector
    char choice = ' ';
    while (choice != '4')
    {
        cout << "MENU\n";
        cout << "[1] See your plants\n";
        cout << "[2] Add a plant to your garden\n";
        cout << "[3] Harvest plant\n";
        cout << "[4] Save and quit\n\n";
        cout << "Menu choice:  ";
        cin >> choice; // input menu choice
        while (cin.fail()) {
            cin.clear();
            cin >> choice; // re-enter input menu choice
        }
        switch (choice)
        {
        case '1': //see all plants
        {
            cout << allToString(myPlants);
            break;
        }
        case '2': //add plant
        {
            string enterName, enterTime;
            cout << "Enter plant name (one word only): ";
            cin >> enterName;
            cout << "Enter date planted (Format: MM/DD): ";
            while (!checkDateFormat(enterTime, year)) { // gets input and checks its validity
                cout << "Incorrect format" << endl << "Enter date planted (Format: MM/DD): ";
            }
            myPlants.push_back(Plant(enterName, enterTime, year));
            break;
        }
        case '3': //harvest plant
        {
            string enterName, enterTime;
            cout << "Enter plant name: ";
            cin >> enterName;
            cout << "Enter date harvested (Format: MM/DD): ";
            while (!checkDateFormat(enterTime, year)) { // gets input and checks its validity
                cout << "Incorrect format" << endl << "Enter date harvested (Format: MM/DD): ";
            }
            harvestPlant(myPlants, enterName, enterTime);
            break;
        }
        case '4': //end program
        {
            writeToFile(myPlants, yearS); //save changes
            return 0;
            break;
        }
        default:
        {
            cout << "Invalid input. Choose again: ";
            break;
        }
        }
    }

    return 0;
}

vector<Plant> dataInit(string fileName)
{
    vector<Plant> plants;
    std::ifstream plantFile;
    plantFile.open(fileName);
    if (plantFile.is_open()) {
        int year = stoi(fileName.substr(0, 4));
        vector<string> row;
        string line, word;
        int plantCount = 0; // plantCount = current row
        while (plantFile >> line) { // inputting 1 line at a time
            row.clear();
            std::stringstream s(line);
            while (getline(s, word, ',')) { // read each column and store each word into the vector
                row.push_back(word);
            }
            if (row.size() >= 2) //has name and plant date
                plants.push_back(Plant(row.at(0), row.at(1), year));
            if (row.size() > 2) { // also has harvest dates
                for (int i = 2; i < row.size(); i++) // add as many harvest dates as needed
                    plants.at(plantCount).addHarvestDate(row.at(i));
            }
            plantCount++;
        }
    }
    plantFile.close();
    return plants;
}

string allToString(vector<Plant> plants)
{
    string info = "";
    for (Plant plant : plants)
    {
        info += plant.to_string() + "\n";
    }
    return info;
}

void harvestPlant(vector<Plant>& plants, string plantName, string date)
{
    bool plantPlanted = false;
    for (int i = 0; i < plants.size(); i++)
    {
        if (plants.at(i).getName() == plantName) // search for entered name
        {
            plantPlanted = true;
            plants.at(i).addHarvestDate(date);
        }
    }
    if (!plantPlanted)
    {
        cout << "No plant found under that name\n\n";
    }
}

void writeToFile(vector<Plant> plants, string year)
{
    std::ofstream plantFile;
    plantFile.open(year + ".csv", std::ofstream::trunc); //open and clear file
    for (Plant plant : plants) //input all data
    {
        plantFile << plant.getName() << ","
            << plant.getPlantDate() << ","
            << plant.getHarvestDates() << endl;
    }
    plantFile.close();
}

bool checkDateFormat(string &date, int year)
{
    cin.clear();
    cin >> date;
    if (date.length() != 5) {
        return false;
    }
    int month = atoi(date.substr(0, 2).c_str());
    if (month > 12 || month < 1) { // checks month validity
        return false;
    }
    if (atoi(date.substr(3, 5).c_str()) > getDaysInMonth(month - 1, year) && atoi(date.substr(3, 5).c_str()) > 0) { //checks day validity
        return false;
    }
    return true;
}