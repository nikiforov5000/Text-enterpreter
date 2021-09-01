#pragma once
#include "Value.h"
#include "Token.h"

class Operation {
	Value m_val1;
	Value m_val2;
	Token m_oper;
public:
	Operation(const Value& v1, const Value& v2, Token op) :m_val1(v1), m_val2(v2), m_oper(op){
		//std::cout << "Operation(const Value& v1, const Value& v2, Token op). count:" << ++constrCount << std::endl;
	}
	double Operate();
	~Operation() {
		//std::cout << "~Operation(). count:" << --constrCount << std::endl;
	}
};

