/*
  * File:   Plant.cpp
  *
  * Last Update: 06/10
  * Added leap year support
 */

#include <iostream>
#include <string>
#include <map>
#include "Plant.h"
#include "Year.h"

Plant::Plant(string name, string plantDate, int year) {
    this->name = name;
    this->year = year;
    startDate = plantDate;
    plantHarvestDates.insert(std::pair<int, string>(0, plantDate));
}

Plant::Plant(string name, string plantDate, string harvestDate, int year) {
    this->name = name;
    this->year = year;
    startDate = plantDate;
    plantHarvestDates.insert(std::pair <int, string>(0, startDate));
    plantHarvestDates.insert(std::pair <int, string>(dateToPos(harvestDate), harvestDate));
}

string Plant::getName() {
    return name;
}

string Plant::getPlantDate() {
    return plantHarvestDates.at(0);
}

string Plant::getHarvestDates() {
    string harvestDates = "";
    for (const auto& datePair : plantHarvestDates) {
        string temp = posToDate(datePair.first);
        harvestDates.append(temp + ",");
    }
    harvestDates = harvestDates.substr(6);
    return harvestDates;
}

int Plant::getYear() {
    return year;
}

void Plant::addHarvestDate(string harvestDate) {
    plantHarvestDates.insert(std::pair<int, string>(dateToPos(harvestDate), harvestDate));
}

string Plant::to_string() {
    string dates = "";
    for (const auto& datePair : plantHarvestDates) {
        string temp = posToDate(datePair.first);
        dates.append("   " + temp);
    }
    return ("Plant: " + name + "    Dates: " + dates);
}

int Plant::dateToPos(string currentDate) {
    int startMonth = std::stoi(startDate.substr(0, 2));
    int startDay = std::stoi(startDate.substr(3));
    int currentMonth = std::stoi(currentDate.substr(0, 2));
    int currentDay = std::stoi(currentDate.substr(3));
    if (currentMonth == startMonth)
        return currentDay - startDay;
    else if (currentMonth > startMonth) {
        int daysInStartMonth = getDaysInMonth(startMonth - 1, year) - startDay;
        int fullMonthDays = 0;
        for (int i = startMonth; i < currentMonth - 1; i++) {
            fullMonthDays += getDaysInMonth(i, year);
        }
        return currentDay + daysInStartMonth + fullMonthDays;
    }
    else
        return -1;
}

string Plant::posToDate(int position) {
    int startMonth = std::stoi(startDate.substr(0, 2));
    int startDay = std::stoi(startDate.substr(3));
    int currentMonth = 0;
    int currentDay = 0;
    if (getDaysInMonth(startMonth - 1, year) >= position + startDay) { // if (# of days in start month >= position + start day)
        if (position + startDay < 10) {
            return (startDate.substr(0, 2) + "/0" + std::to_string(position + startDay));
        }
        else
            return (startDate.substr(0, 2) + "/" + std::to_string(position + startDay));
    }
    else {
        currentMonth = startMonth + 1;
        currentDay = position - getDaysInMonth(startMonth - 1, year) + startDay;
        while (getDaysInMonth(currentMonth - 1, year) < currentDay) {
            currentDay -= getDaysInMonth(currentMonth - 1, year);
            currentMonth++;
        }
        if (currentDay < 10 && currentMonth < 10)
            return ("0" + std::to_string(currentMonth) + "/0" + std::to_string(currentDay));
        else if (currentDay < 10)
            return (std::to_string(currentMonth) + "/0" + std::to_string(currentDay));
        else if (currentMonth < 10)
            return ("0" + std::to_string(currentMonth) + "/" + std::to_string(currentDay));
        else
            return (std::to_string(currentMonth) + "/" + std::to_string(currentDay));
    }
}