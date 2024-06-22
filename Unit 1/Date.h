#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Date {
public:
  Date(int y): year(y), month(1), day(1) {}
  Date(int y, int m): year(y), month(m), day(1) {}
  Date(int y, int m, int d): year(y), month(m), day(d) {}

  Date& addMonths(int n) {
    year  += (month + n) / 12;
    month = (month + n) % 12;
    return *this;
  }

  Date& addDays(int n) {
    int d = daysToDate() + n;
    int y = year, m = 1;
    while (d > daysInMonth(y, m)) {
      d -= daysInMonth(y, m);
      m++;
      if (m > 12){
        m = 1;
        y++;
      }
    }
    day = d;
    month = m;
    year = y;
    return *this;
  }

  static bool isLeapYear(int y) {
    return (y % 4 || (y % 100 == 0 && y % 400)) ? false : true;
  }

  string toString() {
    string date;
    switch(month) {
      case 1:
        date = "January ";
        break;
      case 2:
        date = "February ";
        break;
      case 3:
        date = "March ";
        break;
      case 4:
        date = "April ";
        break;
      case 5:
        date = "May ";
        break;
      case 6:
        date = "June ";
        break;
      case 7:
        date = "July ";
        break;
      case 8:
        date = "August ";
        break;
      case 9:
        date = "September ";
        break;
      case 10:
        date = "October ";
        break;
      case 11:
        date = "November ";
        break;
      case 12:
        date = "December ";
        break;
    }
    date += day + ", " + year;
    return date;
  }

  int daysToDate() {
    int days_in_month[] {31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 0;
    for (int m = 0; m < month - 1; m++) {
      days += days_in_month[m];
    }
    days += day;
    return days;
  }

  Date operator+(Date d) {
    Date newDate(year, month, day);
    newDate.addDays(d.day);
    return newDate;
  }

  friend ostream& operator<<(ostream& out, const Date& d) {
    out << d.month << "/" << d.day + "/" << d.year << endl;
    return out;
  }

private:
  int year, month, day;
  static int daysInMonth(int y, int m){
    int days_in_month[] {31, isLeapYear(y) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days_in_month[m - 1];
  }
};


