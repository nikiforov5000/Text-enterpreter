#include "pch.h"
#include <gtest/gtest.h>
#include "../Calculator/StackCalculator.h"

TEST(evaluate_function, validInput) {
	ASSERT_TRUE(evaluate("1 + 2") == 3);
	ASSERT_TRUE(evaluate("1+((1.50/20))-2") == -0.925);
	ASSERT_TRUE(evaluate("(1.5 * 10)") == 15);
	ASSERT_TRUE(evaluate("(333+(1+(1)))") == 335);
	ASSERT_TRUE(evaluate("1 + (( 2)) + 0") == 3);
	ASSERT_TRUE(evaluate(".1 + (( 2)) + 0") == 2.1);
	ASSERT_TRUE(evaluate("()") == 0);
}

TEST(isValid_function, invalidInput) {
	ASSERT_TRUE(isValid("((((()") == false);
	ASSERT_TRUE(isValid("1(2(((()") == false);
	ASSERT_TRUE(isValid("1% 2 + 0") == false);
	ASSERT_TRUE(isValid("1 2 + 0") == false);
	ASSERT_TRUE(isValid("1 + (2h) + 0") == false);
	ASSERT_TRUE(isValid("(1.5.. * 10)") == false);
}
TEST(calculator_function, invalidInput) {
	ASSERT_TRUE(calculator("((((()") == 0);
	ASSERT_TRUE(calculator("1(2(((()") == 0);
	ASSERT_TRUE(calculator("1% 2 + 0") == 0);
	ASSERT_TRUE(calculator("1 2 + 0") == 0);
	ASSERT_TRUE(calculator("1 + (2h) + 0") == 0);
	ASSERT_TRUE(calculator("(1.5.. * 10)") == 0);
}

TEST(isValid_function, validInput) {
	ASSERT_TRUE(isValid("1 + 2") == true);
	ASSERT_TRUE(isValid("1+((1.50/20))-2") == true);
	ASSERT_TRUE(isValid("(1.5 * 10)") == true);
	ASSERT_TRUE(isValid("(333+(1+(1)))") == true);
	ASSERT_TRUE(isValid("1 + (( 2)) + 0") == true);
	ASSERT_TRUE(isValid(".1 + (( 2)) + 0") == true);
	ASSERT_TRUE(isValid("()") == true);
}

