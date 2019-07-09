//#include"Node.h"
#include<memory>
#include<string>
#include<vector>
#include"Date.h"
class Node {

	virtual bool Evaluate(const Date& date, const string& event) = 0;
};



enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};
enum class  LogicalOperation {
	And,
	Or
};
/*bool operator<(const Date& lhs, const Date& rhs) {
	return vector<int>{lhs.year, lhs.month, lhs.day} <
		vector<int>{rhs.year, rhs.month, rhs.day};
}*/
class DateComparisonNode :public Node {
	DateComparisonNode(const Comparison op_, const Date& lhs_)
		: op(op_), lhs(lhs_) {}

	bool Evaluate(const Date& date, const string& event) override{
		if (op == Comparison::Less) { return date < lhs; }
		else if (op == Comparison::LessOrEqual) {
			if (date < lhs || date == lhs) { return true; }
		}
		else if (op == Comparison::Greater) { return date > lhs; }
		else if (op == Comparison::GreaterOrEqual) {
			if (date > lhs || date == lhs) { return true; }
		}
		else if (op == Comparison::Equal) { return date == lhs; }
		else if (op == Comparison::NotEqual) { return !(date == lhs); }

	}

	const Comparison op;
	const Date lhs;
};
class EmptyNode :public Node {
	EmptyNode(){}
	bool Evaluate(const Date& date, const string& event)override { return true; }//??
};

class EventComparisonNode :public Node {
public:
	EventComparisonNode(const Comparison& op_, const string& lhs_)
		:op(op_), lhs(lhs_) {}

	bool Evaluate(const Date& date, const string& event)override {
		if (op == Comparison::Equal) { return event == lhs; }
		else if (op == Comparison::NotEqual) { return!(event == lhs); }
	}
	const Comparison op;
	const string lhs;
};
class LogicalOperationNode :public Node {
public:
	LogicalOperationNode(const LogicalOperation op_,
		const shared_ptr<Node> lhs_, const shared_ptr<Node> rhs_)
		:op(op_), lhs(lhs_), rhs(rhs_) {}

	bool Evaluate(const Date& date, const string& event)override {
		if (op == LogicalOperation::And) {
			return (lhs->Evaluate(date, event) && rhs->Evaluate(date, event);
		}else if(op==LogicalOperation::or)
		{
			return lhs->Evaluate(date, event) || rhs->Evaluate(date, event);
		}
	}

	const LogicalOperation op;
	const shared_ptr<Node> lhs;
	const shared_ptr<Node> rhs;
};
