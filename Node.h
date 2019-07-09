#pragma once


class Node {
	virtual bool Evaluate(const Date& date, const string& event);
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

class DateComparisonNode :public Node {
	DateComparisonNode(const Comparison op_, const Date& lhs_);
	
	bool Evaluate(const Date& date, const string& event)override;

	const Comparison op;
	const Date lhs;
};
class EmptyNode :public Node {
	bool Evaluate(const Date& date, const string& event)override;
};

class EventComparisonNode :public Node {
public:
	EventComparisonNode(const Comparison& op_, const string& lhs_);

	bool Evaluate(const Date& date, const string& event)override;
	
	const Comparison op;
	const string lhs;
};
class LogicalOperationNode :public Node {
public:
	LogicalOperationNode(const LogicalOperation op_,
		const shared_ptr<Node> lhs_, const shared_ptr<Node> rhs_);

	 bool Evaluate(const Date& date, const string& event)override;

	const LogicalOperation op;
	const shared_ptr<Node> lhs;
	const shared_ptr<Node> rhs;
};
