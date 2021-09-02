#include "pch.h"
#pragma once
#include <gtest/gtest.h>
#include "../Calculator/Calculator.h"

TEST(evaluate_function, validInput) {
	Calculator testCalc;
	std::string testExp{};

	testExp = "100 + 200";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == 300);
	testExp = "1 + ((1.50 / 20)) - 2";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == -0.925);
	testExp = "(1.5 * 10)";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == 15);
	testExp = "(333+(1+(1)))";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == 335);
	testExp = "1 + (( 2)) + 0";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == 3);
	testExp = "(2.1)";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == 2.1);
}

TEST(evaluate_function, invalidPoint) {
	Calculator testCalc;
	std::string testExp{};

	testExp = "()";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "1234.5. * 10";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "1..5 * 10";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "a = ..5234. * 10";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "30 + .1.2345. * 10";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "9999999*.100000. * 10";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "(. * 10)";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
}
TEST(evaluate_function, invalidBracket) {
	Calculator testCalc;
	std::string testExp{};

	testExp = "(()";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "1(2(((()";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "1) 2 + 0";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "asdasd=) 80 + 0";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "1 + )(2) + 0";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
}
TEST(evaluate_function, invalidChars) {
	Calculator testCalc;
	std::string testExp{};


	testExp = "100 + 200o";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "1+((1.50/20))-*2";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "(1.#5 * 10)";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "(,333+(1+(1)))";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "1 + (( 2------)) + 0";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = ".1 + (( 2)^) + 0";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "& = ()";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
	testExp = "";
	EXPECT_THROW(testCalc.evaluate(testExp).GetValue(), std::exception);
}

TEST(evaluate_function, variablesInput) {
	Calculator testCalc;
	std::string testExp{};

	testExp = "a=1 / 2";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == 0.5);
	testExp = "a=20+30";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == 50);
	testExp = "b=a*a";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == 2500);
	testExp = "newValue=b-2499";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == 1);
	testExp = "newValue=300/299";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == 1.0033444816053511705685618729097);
	testExp = "	 a =    a +(.1 *	70)";
	ASSERT_TRUE(testCalc.evaluate(testExp).GetValue() == 57);
}
