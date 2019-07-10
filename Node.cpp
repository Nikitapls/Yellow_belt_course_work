#pragma once
#include"Node.h"
#include<memory>
#include<string>
#include<vector>
#include"Date.h"



//
//class DateComparisonNode :public Node {
//public:
DateComparisonNode::DateComparisonNode(const Comparison op_, const Date& lhs_)
		: op(op_), lhs(lhs_) {}

bool DateComparisonNode:: Evaluate(const Date& date, const string& event){
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

	/*const Comparison op;
	const Date lhs;*/
////};
//class EmptyNode :public Node {
//public:
EmptyNode ::EmptyNode(){}
bool EmptyNode:: Evaluate(const Date& date, const string& event) { return true; }//??
//};

//class EventComparisonNode :public Node {
//public:
EventComparisonNode::EventComparisonNode(const Comparison& op_, const string& lhs_)
		:op(op_), lhs(lhs_) {}

	bool EventComparisonNode::Evaluate(const Date& date, const string& event) {
		if (op == Comparison::Less) { return event < lhs; }
		else if (op == Comparison::LessOrEqual) {
			if (event < lhs || event == lhs) { return true; }
		}
		else if (op == Comparison::Greater) { return event > lhs; }
		else if (op == Comparison::GreaterOrEqual) {
			if (event > lhs || event == lhs) { return true; }
		}
		else if (op == Comparison::Equal) { return event == lhs; }
		else if (op == Comparison::NotEqual) { return !(event == lhs); }

	}
//	const Comparison op;
//	const string lhs;
//};
//class LogicalOperationNode :public Node {
//public:
	LogicalOperationNode ::LogicalOperationNode(const LogicalOperation op_,
		const shared_ptr<Node> lhs_, const shared_ptr<Node> rhs_)
		:op(op_), lhs(lhs_), rhs(rhs_) {}

	bool  LogicalOperationNode ::Evaluate(const Date& date, const string& event) {
		if (op == LogicalOperation::And) {
			return (lhs->Evaluate(date, event) && rhs->Evaluate(date, event));
		}else if(op==LogicalOperation::Or)
		{
			return( lhs->Evaluate(date, event) || rhs->Evaluate(date, event));
		}
	}
//
//	const LogicalOperation op;
//	const shared_ptr<Node> lhs;
//	const shared_ptr<Node> rhs;
//};
