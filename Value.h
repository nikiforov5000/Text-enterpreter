#include <iostream>

#ifndef VALUE_HEADER
#define VALUE_HEADER

class Value {
	double m_value{};
public:
	Value() {
		//std::cout << "Value(). count:" << ++m_valCount << std::endl;
	};
	Value(double val) :m_value(val) {

	};
	double GetValue();
	void SetValue(double value);
	~Value() {
		//std::cout << "~Value(). count:" << --m_valCount << std::endl;
	}
};
#endif
