//#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.cpp"
#include "test_runner.h"
#include <sstream>
#include<set>
#include<execution>
#include <iostream>
#include <stdexcept>
#include <vector>
#include<string>
#include<map>
#include<iomanip>
using namespace std;


//void TestAll();



class Database {
public:
	void Add(Date date, string evnt) {
		try {
			if (evnt_date.at(evnt).count(date) == 0) {
				date_evnt[date].push_back(evnt);
				evnt_date[evnt].insert(date);
			}
		}
		catch (exception &ex) {
			date_evnt[date].push_back(evnt);
			evnt_date[evnt].insert(date);
		}
	}
	void Print(ostream& str) {
		for (auto pr : date_evnt) {
			for (auto event_ : pr.second) {
				cout << pr.first << ' ' << event_<<endl;
			}
		}
	}
	void RemoveIf();
	void FindIf();
	void last();
	map<Date, vector<string>> date_evnt;
	map<string, set<Date>> evnt_date;
};


//Add 2017-01-01 New Year
string ParseEvent(istream& is) {
	// Реализуйте эту функцию
	string evnt;
	getline(is, evnt);
	string answer(evnt.begin() + 1, evnt.end());
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

int main() {
  //TestAll();

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
	//else if (command == "Del") {
 //     auto condition = ParseCondition(is);//shared_ptr<node>_______________________________________________________
 //     auto predicate = [condition](const Date& date, const string& event) {
 //       return condition->Evaluate(date, event);
 //     };
 //     int count = db.RemoveIf(predicate);
 //     cout << "Removed " << count << " entries" << endl;


 //   }
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


    } /*else if (command == "Last") {
      try {
          cout << db.Last(ParseDate(is)) << endl;
      } catch (invalid_argument&) {
          cout << "No entries" << endl;
      }*/
    } else if (command.empty()) {
      continue;
    } else {
      throw logic_error("Unknown command: " + command);
    }
  }

  return 0;
}

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
