#include <iostream>

enum class Type : int{
	NUM = 0,
	OPER = 1,
	VAR = 2,
	EQUAL = 3,
	BROPEN = 4,
	BRCLOSE = 5,
	PLUS = 6,
	MINUS = 7, 
	MULT = 8,
	DIV = 9,
	PLUSEQ = 10,
	MINEQ = 11,
	MULTEQ = 12,
	DIVEQ = 13
};
class Token {
public:
	std::string m_str;
	Type m_type{};
	Token() {
		//std::cout << "Token(). count:" << ++m_tokenCount << std::endl;
	}
	Token(std::string name, Type tokenType) :m_str(name), m_type(tokenType) {
		//std::cout << "Token(std::string name, Type tokenType)" << ++m_tokenCount << std::endl;
	}
	~Token() {
		//std::cout << "~Token(). count:" << --m_tokenCount << std::endl;
	}
};
