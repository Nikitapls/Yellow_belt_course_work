#include"database.h"

#include<string>
#include<utility>
#include<iostream>
#include<iomanip>
using namespace std;

	void Database:: Add(Date date, string evnt) {
		try {
			if (setcont.at(date).count(evnt) == 0) {
				setcont[date].insert(evnt);
				date_evnt[date].push_back(evnt);
			}
		}
		catch (exception &ex) {
			setcont[date].insert(evnt);
			date_evnt[date].push_back(evnt);
		}

	}


	void Database::Print(ostream &stream) const {
		for (const auto &item : date_evnt) {
			for (const string &event : item.second) {
				stream << item.first << " " << event << endl;
			}
		}
	}

	//template <class predicate>
	//int Database:: RemoveIf(predicate pred) {
	//	int num_deleted_el = 0;
	//	for (auto it = date_evnt.begin(); ; ) {

	//		auto it1 = remove_if(it->second.begin(), it->second.end(), [pred, &it, &num_deleted_el](string event) {
	//			if (pred(it->first, event)) {
	//				num_deleted_el++;
	//				return true;
	//			}
	//			return false;
	//		});
	//		//cout << "del" << endl;
	//		//if (it1 != it->second.end()) {
	//		for (auto del = it1; del != it->second.end(); ++del) {
	//			//cout << "as" << *del << endl;
	//			setcont[it->first].erase(*del);
	//			if (setcont[it->first].size() == 0) {
	//				setcont.erase(it->first);
	//			}

	//		}
	//		it->second.erase(it1, it->second.end());
	//		if (it != date_evnt.end()) {
	//			if (it->second.size() == 0) {
	//				date_evnt.erase(it++);//??
	//			}
	//			else {
	//				it++;
	//			}
	//		}
	//		if (it == date_evnt.end()) break;

	//	}
	//	return num_deleted_el;
	//}


	//template <class predicate>
	//vector<pair<Date, string>> Database:: FindIf(predicate pred)const {
	//	vector < pair<Date, string>> answer;
	//	for (auto it = date_evnt.begin(); it != date_evnt.end(); ++it) {
	//		for (string str : it->second) {
	//			if (pred(it->first, str)) {
	//				answer.push_back(make_pair(it->first, str));
	//			}
	//		}
	//	}


	//	return answer;
	//}


	pair<Date, string> Database::Last(const Date &date) const {
		if (date_evnt.count(date)) {
			if (date_evnt.at(date).empty()) {
				throw invalid_argument("");
			}
			return make_pair(date, date_evnt.at(date).back());
		}
		auto it = date_evnt.upper_bound(date);
		if (it == date_evnt.begin()) {
			throw invalid_argument("");
		}
		it--;
		if (it->second.empty()) {
			throw invalid_argument("");
		}
		return make_pair(it->first, it->second.back());
	}

	ostream& operator << (ostream &s, const pair<Date, string>& date) {
		s.fill('0');
		s << setw(4) << date.first.year << '-' << setw(2) << date.first.month << '-' << setw(2) << date.first.day << ' ' << date.second;
		return s;
	}