 /*
  * File:   Plant.h
  * Author: Olivia Leonard
  *
  * Last Update: 5/08
  */

#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <map>
using std::string;
using std::map;

class Plant
{
protected:
    string name;
    map <int, string> plantHarvestDates;
    string startDate;
    int dateToPos(string date);
    string posToDate(int position);

public:
    const static int daysInMonth[12];
    Plant(string name, string plantDate);
    Plant(string name, string plantDate, string harvestDate);
    void addHarvestDate(string harvestDate);
    string getName();
    string getPlantDate();
    string getHarvestDates();
    string to_string();
};
#endif  /*PLANT_H*/ 

