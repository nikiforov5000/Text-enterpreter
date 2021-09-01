#include "Calculator.h"

const std::string Calculator::getUserInput(std::string& userInput) {
	std::getline(std::cin, userInput);
	return userInput;
}
void Calculator::printTokens() {
	for (auto x : m_tokens) {
		std::cout << x.m_str   << "_";
	}
	std::cout << std::endl;
	std::cout << "----------" << std::endl;
}
int Calculator::getPrecedence(Token oper) {
	switch (oper.m_type) {
	case Type::PLUS:
	case Type::MINUS: return 1;
	case Type::MULT:
	case Type::DIV: return 2;
	case Type::BROPEN:
	case Type::BRCLOSE: return 3;
	default: return -1;
	}
}
size_t Calculator::expLength() {
	size_t length{};
	size_t bracketCount{ 1 };
	Token& currentToken{ m_tokens[m_tokenIndex] };
	for (m_tokenIndex; m_tokenIndex < m_tokens.size() && bracketCount != 0; ) {
		m_tokenIndex++;
		if (m_tokenIndex >= m_tokens.size()) {
			throw std::exception("[ERROR] [invalid input] Calculator::expLength() m_tokenIndex out of range");
		}
		currentToken = m_tokens[m_tokenIndex];
		if (currentToken.m_type == Type::BROPEN) {
			bracketCount++;
		}
		if (currentToken.m_type == Type::BRCLOSE) {
			bracketCount--;
		}
		length++;
	}
	if (bracketCount != 0) {
		throw std::exception("[ERROR] [invalid input] Calculator::expLength bracketCout failure");
	}
	m_tokenIndex -= length;
	--length;
	return length;
}
void Calculator::moveIndex() {
	m_strIndex += m_tokens.back().m_str.length();
}
bool Calculator::isBracket() {
	return m_pos == '(' || m_pos == ')';
}
void Calculator::getOper() {
	std::string name{};
	if (m_userInput[m_strIndex + 1] == '=') {
		name = m_userInput.substr(m_strIndex, 2);
		if (name == "+=") {
			m_tokens.push_back(Token(name, Type::PLUSEQ));
		}
		if (name == "-=") {
			m_tokens.push_back(Token(name, Type::MINEQ));
		}
		else {
			throw std::exception("[ERROR] Calculator::getOper failure");
		}
	}
	else {
		name = m_userInput.substr(m_strIndex, 1);
		if (name == "-") {
			m_tokens.push_back(Token(name, Type::MINUS));
		}
		else if (name == "+") {
			m_tokens.push_back(Token(name, Type::PLUS));
		}
		else if (name == "*") {
			m_tokens.push_back(Token(name, Type::MULT));
		}
		else if (name == "/") {
			m_tokens.push_back(Token(name, Type::DIV));
		}
		else if (name == "(") {
			m_tokens.push_back(Token(name, Type::BROPEN));
		}
		else if (name == ")") {
			m_tokens.push_back(Token(name, Type::BRCLOSE));
		}
		else if (name == "=") {
			m_tokens.push_back(Token(name, Type::EQUAL));
		}
		else {
			std::cout << m_userInput[m_strIndex];
			throw std::exception("[ERROR] Calculator::getOper failure");
		}
	}
}
bool Calculator::isOper() {
	return m_pos == '+' ||
		   m_pos == '-' ||
		   m_pos == '*' ||
		   m_pos == '/' ||
		   m_pos == '=';
}

bool Calculator::isDigit() {
	return (m_pos > 47 && m_pos < 58) || m_pos == '.';
}
void Calculator::getDigit() {
	std::string validSet{ "0123456789." };
	size_t strEnd = m_userInput.find_first_not_of(validSet, m_strIndex);

	if (strEnd == m_userInput.npos) {
		strEnd = m_end;
	}
	std::string name{ m_userInput.substr(m_strIndex, strEnd - m_strIndex) };

	std::regex twoDots("\.*\\.[0-9]*\\.");
	std::smatch m;
	if (name == "." || std::regex_search(name, m, twoDots)) {
		//std::cout << "=================" << m.str() << "_in_" << name << std::endl;
		throw std::exception("[ERROR] [invalid input] invalid point in number");
	}
	m_tokens.push_back(Token(name, Type::NUM));
	for (auto x : m_tokens.back().m_str) {
		if (!((x > 47 && x < 58) || (x == '.'))) {
			std::cout << "\"" << x << "\" in token \"" << m_tokens.back().m_str << "\"" << std::endl;
			throw std::exception("[ERROR] Calculator::getDigit NOT a digit");
		}
	}
}
void Calculator::getVarName() {
	std::string validSet{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
	size_t strEnd = m_userInput.find_first_not_of(validSet, m_strIndex);
	if (strEnd == m_userInput.npos) {
		strEnd = m_end;
	}
	std::string name{ m_userInput.substr(m_strIndex, strEnd - m_strIndex) };
	m_tokens.push_back(Token(name, Type::VAR));
	if (name[0] < 65 || name[0] > 122) {
		throw std::exception("[ERROR] Calculator::getDigit NOT a digit");
	}
}
bool Calculator::isChar() {
	return m_pos >= 65 && m_pos <= 122;
}
void Calculator::GetTokens() {
	int operCounter{ 0 };
	int bracketCounter{ 0 };
	while (m_strIndex < m_end) {
		m_pos = m_userInput[m_strIndex];
		if (m_pos == ' ' || m_pos == '	') {
			m_strIndex++;
			continue;
		}
		if (isChar()) {
			getVarName();
			++operCounter;
		}
		else if (isDigit()) {
			getDigit();
			++operCounter;
		}
		else if (isOper()) {
			getOper();
			--operCounter;
		}
		else if (isBracket()) {
			m_pos == '(' ? ++bracketCounter : --bracketCounter;
			getOper();
		}
		else {
			throw std::exception("[ERROR] [invalid input] [invalid character] Calculator::GetTokens() ");
		}
		moveIndex();
	}
	if (operCounter != 1 || bracketCounter != 0) {
		throw std::exception("[ERROR] [invalid input] [invalid character order] Calculator::GetTokens() ");
	}
	//printTokens();
}
Value Calculator::evaluate(size_t endToken) {
	std::stack<Value> values{};
	std::stack<Token> opers{};
	Value val;
	int valCount{ 0 };
	while (m_tokenIndex < endToken) {
		Token& currentToken = m_tokens[m_tokenIndex];
		if (currentToken.m_type == Type::VAR) {
			if (m_userVariables.contains(currentToken.m_str)) {
				val = (m_userVariables.find(currentToken.m_str))->second.GetValue();
			}
			else {
				throw std::exception("[ERROR] Calculator::evaluate: undefined variable name");
			}
		}
		else if (currentToken.m_type == Type::NUM && valCount == 0) {
			auto temp{ std::stod(currentToken.m_str) };
			val.SetValue(temp);
			valCount++;
		}
		else {
			valCount = 0;
			if (currentToken.m_type == Type::BROPEN) {
				size_t length{ expLength() };
				val = evaluate(++m_tokenIndex + length);
			}
			else if (values.empty()) {
				values.push(val);
				opers.push(currentToken);
				val.SetValue(0);
			}
			else if (currentToken.m_type == Type::BRCLOSE) {
				values.push(val);
				while (opers.top().m_type != Type::BROPEN) {
					currentToken = opers.top();
					opers.pop();
					val = values.top();
					values.pop();
					Value prevVal{ values.top() };
					values.pop();
					Operation newOperation(prevVal, val, currentToken);
					val = newOperation.Operate();
					values.push(val);
				}
				opers.pop();
				values.pop();
			}
			else {
				Token prevOper = opers.top();
				if (getPrecedence(m_tokens[m_tokenIndex]) > getPrecedence(prevOper)) {
					values.push(val);
					opers.push(currentToken);
					val.SetValue(0);
				}
				else {
					Value prevVal = values.top();
					values.pop();
					Token prevOper= opers.top();
					opers.pop();
					Operation newOperation(prevVal, val, prevOper);
					prevVal = newOperation.Operate();
					values.push(prevVal);
					opers.push(currentToken);
					val.SetValue(0);
				}
			}
		}
		++m_tokenIndex;
	}
	while (!opers.empty()) {
		if (values.empty()) {
			throw std::exception("[ERROR] Calculator::evaluate(size_t startToken, size_t endToken) line 260 values.empty!");
		}
		Value prev{ values.top() };
		values.pop();
		Token oper = opers.top();
		if (oper.m_type == Type::BROPEN || oper.m_type == Type::BRCLOSE) {
			throw std::exception("[ERROR] Calculator::evaluate(size_t startToken, size_t endToken) line 267 current token is a bracket!");
		}
		opers.pop();
		Operation newOperation(prev, val, oper);
		val = newOperation.Operate();
	}
	return val;
}
Value Calculator::evaluate(std::string userInput) {
	m_tokens.clear();
	m_userInput = userInput;
	m_strIndex = 0;
	m_end = m_userInput.length();
	m_pos = m_userInput[m_strIndex];
	m_tokenIndex = 0;
	GetTokens();

 	Value result{};
	if (m_tokens[1].m_type != Type::EQUAL) {
		m_tokenIndex = 0;
		result = evaluate(m_tokens.size());
		std::cout << "result:" << result.GetValue() << std::endl;;
	}
	else {
		m_tokenIndex = 2;
		result = evaluate(m_tokens.size());
		if (m_userVariables.contains(m_tokens[0].m_str)) {
			m_userVariables.find(m_tokens[0].m_str)->second.SetValue(result);
		}
		else {
			std::string& name{ m_tokens[0].m_str };
			m_userVariables.insert(std::make_pair(name, Variable(name, result)));
		}
		std::cout << m_tokens[0].m_str << "=" << result.GetValue() << std::endl;;
	}
	return result;
}
