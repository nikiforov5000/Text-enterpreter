#include "Variable.h"

Value Variable::GetValue() {
	return m_value;
}

void Variable::SetValue(Value val) {
	m_value = val;
}
