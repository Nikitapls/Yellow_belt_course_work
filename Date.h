#pragma once

#include <iostream>

using namespace std;

class Date {
public:
	Date(int year_, int month_, int day_);
	

	const int year;
	const int month;
	const int day;
};
ostream& operator << (ostream &s, const Date &date);
bool operator<(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);


string ParseEvent(istream& is);
Date ParseDate(istream& is);