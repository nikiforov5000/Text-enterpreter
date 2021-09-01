#include <iostream>
#include <fstream>
#include "Calculator.h"

//void Write() {
//	std::ofstream out{ "data.txt" };
//	out << "Hello world" << std::endl;
//	out << 10 << std::endl;
//	out.close();
//}

std::string Read(std::string& keybInput) {
	std::ifstream input(keybInput);
	std::string expStr;
	std::getline(input, expStr);
	return expStr;
}

int main() {
	//Read();

	std::string keybInput{};
	Calculator newCalc;

	std::getline(std::cin, keybInput);
	if (keybInput.empty()) {
		std::getline(std::cin, keybInput);
	}
	else {
		keybInput = Read(keybInput);
	}
	
	//while (newCalc.getUserInput(userInput)!= (std::string{"exit"})) {
		try	{
			newCalc.evaluate(keybInput);
		}
		catch (const std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
	//}
	
}
