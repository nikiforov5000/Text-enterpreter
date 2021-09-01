#include "Value.h"

double Value::GetValue() {
	return m_value;
}

void Value::SetValue(double value) {
	m_value = value;
}

//template<typename T>
//const T& Value::GetValue() {
//	return m_value;
//}
//
//template<typename T>
//void Value::SetValue(const T& value) {
//	m_value = value;
//}
//
