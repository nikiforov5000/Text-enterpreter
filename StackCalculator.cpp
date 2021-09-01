#include <iostream>
#include <stack>
#include <string>
#include <map>
#include "StackCalculator.h"

void inputError(const std::string& str) {
	std::cout << "Invalid input: " << str << std::endl;
}
bool isDigit(char ch) {
	return (ch > 47 && ch < 58) || ch == '.';
}
bool isOper(char ch) {
	return
		ch == '+' ||
		ch == '-' ||
		ch == '*' ||
		ch == '/' ||
		ch == '(' ||
		ch == ')';
}
int getPrecedence(char ch) {
	switch (ch) {
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '(':
	case ')': return 3;
	default: return -1;
	}
}
double operation(double val1, double val2, char oper) {
	switch (oper) {
	case '+': return val1 + val2;
	case '-': return val1 - val2;
	case '*': return val1 * val2;
	default: return val1 / val2;
	}
}
double getDigit(const std::string& str, size_t* pos) {
	std::string charBuffer{};
	size_t dotCount{ 0 };
	while (isDigit(str[*pos])) {
		if (str[*pos] == '.') {
			++dotCount;
			if (dotCount > 1) {
				return -1;
			}
		}
		charBuffer.push_back(str[*pos]);
		++*pos;
	}
	--*pos;
	return std::stod(charBuffer);
}
std::string checkVariable(const std::string& str)
{
	return std::string();
}
size_t expLength(const std::string& exp, size_t startIndex) {
	size_t length{};
	size_t bracketCount{ 1 };////// Checking if valid
	for (size_t i = startIndex; i < exp.length() && bracketCount != 0; ++i) {////// Checking if valid
		if (exp[i] == '(') {
			bracketCount++;////// Checking if valid
		}
		if (exp[i] == ')') {
			bracketCount--;////// Checking if valid
		}
		length++;
	}
	if (bracketCount != 0) {////// Checking if valid
		inputError(exp);
		return 0;
	}
	--length;
	return length;
}
bool isChar(const char ch) {
	return ch >= 65 && ch <= 122;
}
const std::string getVarName(const std::string& subStr) {
	size_t start{ subStr.find_first_not_of("	 ") };
	size_t pos{ subStr.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", start) };
	return subStr.substr(start, (pos - start));
}
std::string newVariable(const std::string& str) {
	size_t pos{ str.find_first_of("=") };
	std::string varName{};
	if (pos != str.npos) {
		varName = getVarName(str);
	}
	return varName;
}
auto isVariable(const std::string& subStr, std::map<std::string, double>& userVariables) {
	if (isChar(subStr[0])) {
		return userVariables.contains(getVarName(subStr));
	}
	return false;
}

double e valuate(const std::string& str, std::map<std::string, double>& userVariables) {
	std::stack<double> values{};
	std::stack<char> opers{};

	double val{ 0 };
	size_t pos{ 0 };
	int valCount{ 0 };////// Checking if valid

	while (pos < str.length()) {
		char spot = str[pos];
		if (isChar(spot)) {
			std::string name{ getVarName(str.substr(pos)) };
			if (isVariable(name, userVariables)) {
				val = userVariables.find(name)->second;
				pos += name.length() - 1;
			}
			else {
				std::cout << "[ERROR] unidentified variable \"" << name << "\"" << std::endl;
			}
		}
		else if(isDigit(spot) && valCount == 0) {////// Checking if valid
			val = getDigit(str, &pos);
			if (val == -1) {////// Checking if valid
				inputError(str);
				return 0;
			}
			valCount++;////// Checking if valid
		}
		else if (isOper(spot)) {
			valCount = 0;////// Checking if valid
			if (spot == '(') {
				size_t length = { expLength(str, pos + 1) };
				std::string subStr = str.substr(pos + 1, length);
				val = evaluate(subStr, userVariables);
				pos += length + 1;
				spot = str[pos];
			}
			else if (values.empty()) {
				values.push(val);
				opers.push(spot);
				val = 0;
			}
			else if (spot == ')') {
				values.push(val);
				while (opers.top() != '(') {
					spot = opers.top();
					opers.pop();
					val = values.top();
					values.pop();
					double prev{ values.top() };
					values.pop();
					val = operation(prev, val, spot);
					values.push(val);
				}
				opers.pop();
				values.pop();
			}
			else {
				char prev = opers.top();
				if (getPrecedence(spot) > getPrecedence(prev)) {
					values.push(val);
					opers.push(spot);
					val = 0;
				}
				else {
					double prevval = values.top();
					values.pop();
					char prevoper = opers.top();
					opers.pop();
					prevval = operation(prevval, val, prevoper);
					values.push(prevval);
					opers.push(spot);
					val = 0;
				}
			}
		}
		else {////// Checking if valid
			if (spot != ' ' && spot != '	') {
				inputError(str);
				return 0;
			}
		}
		pos++;
	}
	while (!opers.empty()) {
		if (values.empty()) {////// Checking if valid
			inputError(str);
			return 0;
		}
		double prev{ values.top() };
		values.pop();

		char spot = opers.top();
		if (spot == '(' || spot == ')') {////// Checking if valid
			inputError(str);
			return 0;
		}
		opers.pop();
		val = operation(prev, val, spot);
	}
	return val;
}

const std::string getUserInput(std::string& userInput) {
	std::getline(std::cin, userInput);
	return userInput;
}
void Print(auto result) {
	std::cout << result << std::endl;
}

double calculator(const std::string& userInput, std::map<std::string, double>& userVariables) {
	std::string name{ newVariable(userInput) };
	double result{};
	if (name.empty()) {
		result = evaluate(userInput, userVariables);
		Print(result);
	}
	else {
		size_t offset{ userInput.find('=') + 1 };
		result = evaluate(userInput.substr(offset), userVariables);
		if (isVariable(name, userVariables)) {
			userVariables.find(name)->second = result;
		}
		userVariables.insert(std::pair<std::string, double>(name, result));
		std::cout << userVariables.find(name)->first << "=" << userVariables.find(name)->second << std::endl;
		std::cout << "-------------------"<< std::endl;
	}
	return result;

}

/*





*/