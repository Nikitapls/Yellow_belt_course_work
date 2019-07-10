//#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
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
#include<memory>
#include<utility>
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
	template <class predicate>
	vector<pair<Date, string>> FindIf(predicate pred) { 
		vector < pair<Date, string>> answer;
		for ( auto it = date_evnt.begin(); it != date_evnt.end(); ++it) {
			for (string str : it->second) {
				if (pred(it->first, str)) {
					answer.push_back(make_pair(it->first, str));
				}
			}
		}
		return answer;
	}
	void last();
	map<Date, vector<string>> date_evnt;
	map<string, set<Date>> evnt_date;
};


//Add 2017-01-01 New Year


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
    //}
	else if (command.empty()) {
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
