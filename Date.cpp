#include "date.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;
//class Date {
//public:
Date::Date(int year_, int month_, int day_) :year(year_), month(month_), day(day_) {
		if (month > 12 || month < 1) {
			throw logic_error("Month value is invalid: " + to_string(month));
		}
		if (day > 31 || day < 1) {
			throw logic_error("Day value is invalid: " + to_string(day));
		}
	}

//	const int year;
//	const int month;
//	const int day;
//};

ostream& operator << (ostream &s, const Date &date) {
	s.fill('0');
	s << setw(4) << date.year << '-' << setw(2) << date.month << '-' << setw(2) << date.day;
	return s;
}
bool operator<(const Date& lhs, const Date& rhs) {
	return vector<int>{lhs.year, lhs.month, lhs.day} <
		vector<int>{rhs.year, rhs.month, rhs.day};
}
bool operator==(const Date& lhs, const Date& rhs){
	return vector<int>{lhs.year, lhs.month, lhs.day} ==
		vector<int>{rhs.year, rhs.month, rhs.day};
}
bool operator>(const Date& lhs, const Date& rhs){
	return vector<int>{lhs.year, lhs.month, lhs.day} >
		vector<int>{rhs.year, rhs.month, rhs.day};
}

string ParseEvent(istream& is) {
	// Реализуйте эту функцию
	
	string evnt;
	//getline(is, evnt);
	while (is.peek() == ' ') {
		 is.get();
	}
	getline(is, evnt);
	string answer(evnt.begin(), evnt.end());
	return answer;
}
Date ParseDate(istream& is) {//Add 2017-01-01 New Year   Год-Месяц-День
	string data;
	is >> data;
	stringstream ss(data);
	string par;
	int year = -1, month = -1, day = -1;
	for (int i = 0; i < 3; ++i) {
		getline(ss, par, '-');
		if (year == -1) { year = stoi(par); }
		else if (month == -1) { month = stoi(par); }
		else if (day == -1) { day = stoi(par); }
	}
	return{ year,month,day };
}