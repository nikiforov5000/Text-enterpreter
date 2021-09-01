#pragma once
#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <vector>
#include <regex>

#include "Variable.h"
#include "Operation.h"

class Calculator {
	std::map<std::string, Variable> m_userVariables;
	std::string m_userInput;
	std::vector<Token> m_tokens{};
	size_t m_strIndex{ 0 };
	size_t m_end{ m_userInput.length() };
	char m_pos{ m_userInput[m_strIndex] };
	size_t m_tokenIndex{ 0 };
	Value evaluate(size_t endToken);
public:
	Calculator(){
		//std::cout << "Calculator(). count:" << ++constrCount << std::endl;
	};
	const std::string getUserInput(std::string& userInput);
	int getPrecedence(Token spot);
	size_t expLength();
	Value evaluate(std::string userInput);
	void moveIndex();
	bool isBracket();
	bool isOper();
	void printTokens();
	void getOper();
	bool isDigit();
	void getDigit();
	void getOneToken(std::string& validSet);
	void getVarName();
	bool isChar();
	void GetTokens();
	~Calculator() {
		//std::cout << "~Calculator(). count:" << --constrCount << std::endl;
	}
};

