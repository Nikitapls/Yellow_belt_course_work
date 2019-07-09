#include"Date.h"
class Date {
public:
	Date(int year_, int month_, int day_) :year(year_), month(month_), day(day_) {
		if (month > 12 || month < 1) {
			throw logic_error("Month value is invalid: " + to_string(month));
		}
		if (day > 31 || day < 1) {
			throw logic_error("Day value is invalid: " + to_string(day));
		}
	}

	const int year;
	const int month;
	const int day;
};
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