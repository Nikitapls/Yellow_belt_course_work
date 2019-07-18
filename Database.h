#pragma once
#include"date.h"
//#include <execution>

#include<map>
#include<set>
#include<vector>

#include<string>


using namespace std;

template<class T>
void PrintRange(const T &range_begin, const T &range_end) {
	for (auto it = range_begin; it != range_end; ++it) {
		cout << *it << " ";
	}
	cout << endl;
}
class Database {
public:
	void Add(Date date, string evnt);
	void Print(ostream &stream) const;
	

	template <class predicate>
	int RemoveIf(predicate pred) {
		int num_deleted_el = 0;
		
		for (auto it = date_evnt.begin(); ; ) {
			vector<string> todel;
			auto it1 = remove_if(it->second.begin(), it->second.end(), [pred, &it, &num_deleted_el,&todel](string event) {
				if (pred(it->first, event)) {
					todel.push_back(event);
					num_deleted_el++;
					return true;
				}
				return false;
			});

			//cout <<"answ_removeif " <<*it1 << endl<<*(--it1)<<'1'<<endl;
			//cout << "del" << endl;
			//if (it1 != it->second.end()) { tut
			/*for (auto del = it1; del != it->second.end();++del) {
				
					setcont[it->first].erase(*del);
				
				if (setcont[it->first].size() == 0) {
					setcont.erase(it->first);
				}
				
			}*/
			for (const auto & el : todel) {
				setcont[it->first].erase(el);
				if (setcont[it->first].size() == 0) {
					setcont.erase(it->first);
				}
			}

			it->second.erase(it1, it->second.end());
			if (it != date_evnt.end()) {
				if (it->second.size() == 0) {
					date_evnt.erase(it++);//??
				}
				else {
					it++;
				}
			}
			if (it == date_evnt.end()) break;

		}
		return num_deleted_el;
	}


	template <class predicate>
	vector<pair<Date, string>> FindIf(predicate pred)const {
		vector < pair<Date, string>> answer;
		for (auto it = date_evnt.begin(); it != date_evnt.end(); ++it) {
			for (string str : it->second) {
				if (pred(it->first, str)) {
					answer.push_back(make_pair(it->first, str));
				}
			}
		}


		return answer;
	}


	pair<Date, string>Last(const Date &date) const;


	map<Date, vector<string>> date_evnt;
	map<Date, set<string>>  setcont;
};
ostream& operator << (ostream &s, const pair<Date, string>& date);
//ostream &operator<<(ostream &stream, const pair<Date, string> &p);