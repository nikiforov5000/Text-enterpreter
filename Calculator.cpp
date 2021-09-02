#include "Calculator.h"

void printTokens(std::vector<Token>& tokens) {
	for (auto x : tokens) {
		std::cout << x.m_str   << "_";
	}
	std::cout << std::endl;
	std::cout << "----------" << std::endl;
}
int getPrecedence(Token oper) {
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
size_t expLength(const std::vector<Token>& tokens, size_t tokenIndex) {
	size_t length{};
	size_t bracketCount{ 1 };
	Token currentToken{ tokens[tokenIndex] };
	for (tokenIndex; tokenIndex < tokens.size() && bracketCount != 0; ) {
		tokenIndex++;
		if (tokenIndex >= tokens.size()) {
			throw std::exception("[ERROR] [invalid input] Calculator::expLength() tokenIndex out of range");
		}
		currentToken = tokens[tokenIndex];
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
	--length;
	return length;
}
bool isBracket(char ch) {
	return ch == '(' || ch == ')';
}
Token getOper(const std::string& userInput, size_t strIndex) {
	std::string name{};
	if (userInput[strIndex + 1] == '=') {
		name = userInput.substr(strIndex, 2);
		if (name == "+=") {
			return Token(name, Type::PLUSEQ);
		}
		if (name == "-=") {
			return Token(name, Type::MINEQ);
		}
		else {
			throw std::exception("[ERROR] Calculator::getOper failure");
		}
	}
	else {
		name = userInput.substr(strIndex, 1);
		if (name == "-") {
			return Token(name, Type::MINUS);
		}
		else if (name == "+") {
			return Token(name, Type::PLUS);
		}
		else if (name == "*") {
			return Token(name, Type::MULT);
		}
		else if (name == "/") {
			return Token(name, Type::DIV);
		}
		else if (name == "(") {
			return Token(name, Type::BROPEN);
		}
		else if (name == ")") {
			return Token(name, Type::BRCLOSE);
		}
		else if (name == "=") {
			return Token(name, Type::EQUAL);
		}
		else {
			std::cout << userInput[strIndex];
			throw std::exception("[ERROR] Calculator::getOper failure");
		}
	}
}
bool isOper(char ch) {
	return ch == '+' ||
		   ch == '-' ||
		   ch == '*' ||
		   ch == '/' ||
		   ch == '=';
}
bool isDigit(char ch) {
	return (ch > 47 && ch < 58) || ch == '.';
}
Token getDigit(const std::string& userInput, size_t strIndex) {
	std::string validSet{ "0123456789." };
	size_t strEnd = userInput.find_first_not_of(validSet, strIndex);

	if (strEnd == userInput.npos) {
		strEnd = userInput.length();
	}
	std::string name{ userInput.substr(strIndex, strEnd - strIndex) };

	std::regex twoDots("\.*\\.[0-9]*\\.");
	std::smatch m;
	if (name == "." || std::regex_search(name, m, twoDots)) {
		throw std::exception("[ERROR] [invalid input] invalid point in number");
	}
	for (auto x : name) {
		if (!((x > 47 && x < 58) || (x == '.'))) {
			std::cout << "\"" << x << "\" in token \"" << name << "\"" << std::endl;
			throw std::exception("[ERROR] Calculator::getDigit NOT a digit");
		}
	}
	return Token(name, Type::NUM);

}
Token getVarName(const std::string& userInput, size_t strIndex) {
	std::string validSet{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
	size_t strEnd = userInput.find_first_not_of(validSet, strIndex);
	if (strEnd == userInput.npos) {
		strEnd = userInput.length();
	}
	std::string name{ userInput.substr(strIndex, strEnd - strIndex) };
	if (name[0] < 65 || name[0] > 122) {
		throw std::exception("[ERROR] Calculator::getDigit NOT a digit");
	}
	return Token(name, Type::VAR);
}
bool isChar(char ch) {
	return ch >= 65 && ch <= 122;
}
const std::vector<Token> GetTokens(const std::string& userInput) {
	std::vector<Token> tokens;
	size_t strEnd{ userInput.length() };
	size_t strIndex{ 0 };
	char pos{userInput[0]};
	int operCounter{ 0 };
	int bracketCounter{ 0 };

	while (strIndex < strEnd) {
		pos = userInput[strIndex];
		if (pos == ' ' || pos == '	') {
			strIndex++;
			continue;
		}
		if (isChar(pos)) {
			tokens.push_back(getVarName(userInput, strIndex));
			++operCounter;
		}
		else if (isDigit(pos)) {
			tokens.push_back(getDigit(userInput, strIndex));
			++operCounter;
		}
		else if (isOper(pos)) {
			tokens.push_back(getOper(userInput, strIndex));
			--operCounter;
		}
		else if (isBracket(pos)) {
			pos == '(' ? ++bracketCounter : --bracketCounter;
			tokens.push_back(getOper(userInput, strIndex));
		}
		else {
			throw std::exception("[ERROR] [invalid input] [invalid character] Calculator::GetTokens() ");
		}
		strIndex += tokens.back().m_str.length();
	}
	if (operCounter != 1 || bracketCounter != 0) {
		throw std::exception("[ERROR] [invalid input] [invalid character order] Calculator::GetTokens() ");
	}
	//printTokens();
	return tokens;
}
Value Calculator::evaluate(const std::vector<Token>& tokens, size_t tokenIndex, size_t endToken) {
	std::stack<Value> values{};
	std::stack<Token> opers{};
	Value val;
	size_t valCount{ 0 };
	while (tokenIndex < endToken) {
		Token currentToken = tokens[tokenIndex];
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
				size_t length{ expLength(tokens, tokenIndex) };
				val = evaluate(tokens, tokenIndex, ++tokenIndex + length);
				tokenIndex += length;
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
				if (getPrecedence(tokens[tokenIndex]) > getPrecedence(prevOper)) {
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
		++tokenIndex;
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
Value Calculator::evaluate(const std::string& userInput) {
	std::vector<Token> tokens{ GetTokens(userInput) };
 	Value result;

	if (tokens[1].m_type != Type::EQUAL) {
		result = evaluate(tokens, (size_t)0, tokens.size());
		std::cout << "result:" << result.GetValue() << std::endl;;
	}
	else {
		result = evaluate(tokens, (size_t)2, tokens.size());
		if (m_userVariables.contains(tokens[0].m_str)) {
			m_userVariables.find(tokens[0].m_str)->second.SetValue(result);
		}
		else {
			std::string& name{ tokens[0].m_str };
			m_userVariables.insert(std::make_pair(name, Variable(name, result)));
		}
		std::cout << tokens[0].m_str << "=" << result.GetValue() << std::endl;;
	}
	return result;
}
