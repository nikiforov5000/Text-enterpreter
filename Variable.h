//#pragma once
#include <string>

#include "Value.h"


class Variable {
	std::string m_name;
	Value m_value;
public:
	Variable(std::string name) :m_name(name) {
		//std::cout << "Variable(std::string name). count:" << ++m_varCount << std::endl;
	}
	Variable(std::string name, Value& value) : m_name(name), m_value(value) {
		//std::cout << "Variable(std::string name, Value& value). count:" << ++m_varCount << std::endl;
	}
	Value GetValue();
	void SetValue(Value val);
	~Variable() {
		//std::cout << "~Variable(). count:" << --m_varCount << std::endl;
	}

};
