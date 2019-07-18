
#include "node.h"
#include "date.h"
#include "condition_parser.h"
#include "database.h"


#include <sstream>

#include <iostream>
#include <stdexcept>

#include<iomanip>

#include<algorithm>
using namespace std;


//void TestAll();


//
//class Database {
//public:
//	void Add(Date date, string evnt) {
//		try {
//			if (setcont.at(date).count(evnt) == 0) {
//				setcont[date].insert(evnt);
//				date_evnt[date].push_back(evnt);
//			}
//		}
//		catch (exception &ex) {
//			setcont[date].insert(evnt);
//			date_evnt[date].push_back(evnt);
//		}
//
//	}
//	void Print(ostream& str) {
//		for (auto pr : date_evnt) {
//			for (auto event_ : pr.second) {
//				cout << pr.first << ' ' << event_<<endl;
//			}
//		}
//	}
//	
//	template <class predicate>
//	int RemoveIf(predicate pred) {
//		int num_deleted_el = 0;
//		for (auto it = date_evnt.begin(); ; ) {
//
//			auto it1 = remove_if(it->second.begin(), it->second.end(), [pred, &it, &num_deleted_el](string event) {
//				if (pred(it->first, event)) {
//					num_deleted_el++;
//					return true;
//				}
//				return false;
//			});
//			cout << "del" << endl;
//			//if (it1 != it->second.end()) {
//				for (auto del = it1; del != it->second.end(); ++del) {
//					cout << "as" << *del << endl;
//					setcont[it->first].erase(*del);
//					if (setcont[it->first].size() == 0) {
//						setcont.erase(it->first);
//					}
//
//				}
//				it->second.erase(it1, it->second.end());
//				if (it != date_evnt.end()) {
//					if (it->second.size() == 0) {
//						date_evnt.erase(it++);//??
//					}
//					else {
//						it++;
//					}
//				}
//				if (it == date_evnt.end()) break;
//			
//		}
//		return num_deleted_el;
//	}
//
//
//	template <class predicate>
//	vector<pair<Date, string>> FindIf(predicate pred)const { 
//			vector < pair<Date, string>> answer;
//		for ( auto it = date_evnt.begin(); it != date_evnt.end(); ++it) {
//			for (string str : it->second) {
//				if (pred(it->first, str)) {
//					answer.push_back(make_pair(it->first, str));
//				}
//			}
//		}
//		
//	
//		return answer;
//	}
//
//	
//	pair<Date, string>Last(const Date &date) const {
//		if (date_evnt.count(date)) {
//			if (date_evnt.at(date).empty()) {
//				throw invalid_argument("");
//			}
//			return make_pair(date, date_evnt.at(date).back());
//		}
//		auto it = date_evnt.upper_bound(date);
//		if (it == date_evnt.begin()) {
//			throw invalid_argument("");
//		}
//		it--;
//		if (it->second.empty()) {
//			throw invalid_argument("");
//		}
//		return make_pair(it->first, it->second.back());
//	}
//	
//	
//	map<Date, vector<string>> date_evnt;
//	map<Date,set<string>>  setcont;
//};


//Add 2017-01-01 New Year

//string ParseEvent(istream& is) {
//	// Реализуйте эту функцию
//	string evnt;
//	getline(is, evnt);
//	string answer(evnt.begin() + 1, evnt.end());
//	return answer;
//}
int main() {
 // TestAll();

  Database db;

  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "Add") {
      const auto date = ParseDate(is);
      const auto event = ParseEvent(is);
      db.Add(date, event);
    } else if (command == "Print") {
      db.Print(cout);
    } 
	else if (command == "Del") {
      auto condition = ParseCondition(is);//shared_ptr<node>_______________________________________________________
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      int count = db.RemoveIf(predicate);
      cout << "Removed " << count << " entries" << endl;


    }
	else if (command == "Find") {
      auto condition = ParseCondition(is);
      auto predicate = [condition](const Date& date, const string& event) {
        return condition->Evaluate(date, event);
      };
      const auto entries = db.FindIf(predicate);
      for (const auto& entry : entries) {
        cout << entry << endl;
      }
      cout << "Found " << entries.size() << " entries" << endl;


    } else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }
    }
	else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}
//
//void TestParseEvent() {
//  {
//    istringstream is("event");
//    AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
//  }
//  {
//    istringstream is("   sport event ");
//    AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
//  }
//  {
//    istringstream is("  first event  \n  second event");
//    vector<string> events;
//    events.push_back(ParseEvent(is));
//    events.push_back(ParseEvent(is));
//    AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
//  }
//}
//
//void TestAll() {
//  TestRunner tr;
//  tr.RunTest(TestParseEvent, "TestParseEvent");
//  tr.RunTest(TestParseCondition, "TestParseCondition");
//}
