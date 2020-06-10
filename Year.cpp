/*
  * File:   Year.cpp
  *
  * Last Update: 6/10
  * Added leap year support
 */

#include "Year.h"

int daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 30, 30, 31, 30, 31 };

int getDaysInMonth(int month, int year) {
    if (month < 12) {
        if (isLeapYear(year) && month == 1) {
            return 29;
        }
        else
            return daysInMonth[month];
    }
    return -1;
}

bool isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}

