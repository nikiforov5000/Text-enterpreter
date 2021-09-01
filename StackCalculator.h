#include <map>

#pragma once

void inputError(const std::string& str);

bool isDigit(char ch);

bool isOper(char ch);

int getPrecedence(char ch);

double operation(double val1, double val2, char oper);

double getDigit(const std::string& str, size_t* pos);

std::string checkVariable(const std::string& str);

size_t expLength(const std::string& exp, size_t startIndex);

bool isChar(const char ch);

const std::string getVarName(const std::string& subStr);

std::string newVariable(const std::string& str);

auto isVariable(const std::string& subStr, std::map<std::string, double>& userVariables);

double evaluate(const std::string& str, std::map<std::string, double>& userVariables);

double calculator(const std::string& userInput, std::map<std::string, double>& userVariables);

const std::string getUserInput(std::string& userInput);

//void Print(auto result);


