#pragma once
#include<memory>
#include<string>
#include<vector>
#include"Date.h"

using namespace std;

class Node {
public:
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

class DateComparisonNode :public Node {
public:
	DateComparisonNode(const Comparison op_, const Date& lhs_);

	bool Evaluate(const Date& date, const string& event) override;

	const Comparison op;
	const Date lhs;
};
class EmptyNode :public Node {
public:
	EmptyNode();
	bool Evaluate(const Date& date, const string& event)override;//??
};

class EventComparisonNode :public Node {
public:
	EventComparisonNode(const Comparison& op_, const string& lhs_);
	bool Evaluate(const Date& date, const string& event)override;
	const Comparison op;
	const string lhs;
};

enum class  LogicalOperation {
	And,
	Or
};


class LogicalOperationNode :public Node {
public:
	LogicalOperationNode(const LogicalOperation op_,const shared_ptr<Node> lhs_, const shared_ptr<Node> rhs_);
	bool Evaluate(const Date& date, const string& event)override;
	

	const LogicalOperation op;
	const shared_ptr<Node> lhs;
	const shared_ptr<Node> rhs;
};
