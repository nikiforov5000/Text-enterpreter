#include <iostream>

#ifndef VALUE_HEADER
#define VALUE_HEADER

class Value {
	double m_value{};
public:
	size_t m_valCount{ 0 };
	size_t m_varCount{ 0 };
	size_t m_operCount{ 0 };
	size_t m_tokenCount{ 0 };
	size_t m_calcCount{ 0 };
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
