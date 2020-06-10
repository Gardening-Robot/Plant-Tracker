 /*
  * File:   Plant.h
  *
  * Last Update: 06/10
  * Added leap year support
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
    int year;
    map <int, string> plantHarvestDates;
    string startDate;
    int dateToPos(string date);
    string posToDate(int position);

public:
    Plant(string name, string plantDate, int year);
    Plant(string name, string plantDate, string harvestDate, int year);
    void addHarvestDate(string harvestDate);
    string getName();
    string getPlantDate();
    string getHarvestDates();
    int getYear();
    string to_string();
};
#endif  /*PLANT_H*/ 

