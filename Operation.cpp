#include "Operation.h"

//template<typename T>
double Operation::Operate() {

	//std::cout << "Operation::Operate():" << m_val1.GetValue() << "_" << m_oper.m_str << "_" << m_val2.GetValue() << std::endl;
	if (m_oper.m_type == Type::DIV && m_val2.GetValue() == 0) {
		throw std::exception("[ERROR] Operation::Operate() DIVISION BY ZERO");
	}
	switch (m_oper.m_type)
	{
	case Type::PLUS: return m_val1.GetValue() + m_val2.GetValue();
	case Type::MINUS: return m_val1.GetValue() - m_val2.GetValue();
	case Type::MULT: return m_val1.GetValue() * m_val2.GetValue();
	case Type::DIV: return m_val1.GetValue() / m_val2.GetValue();
	default: throw std::exception("[ERROR] Operation::Operate() failure");
	};
}
