#include "../include/calculator.h"
#include <gtest/gtest.h>

TEST(CalculatorTest, addTest) {
  Calculator<uint8_t> calculator;
  std::vector<uint8_t> a={1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 1, 8, 7, 7, 5, 2, 6, 1, 6, 7, 2, 6, 7, 3};
  std::vector<uint8_t> b={7, 1, 8, 6, 2, 5, 6, 3, 4, 1, 5, 2, 7, 7, 8, 3, 6, 7, 6, 3, 5, 5, 4, 4, 8, 1, 6};
  std::vector<uint8_t> expected_result = {1, 3, 0, 6, 4, 3, 0, 4, 5, 3, 5, 3, 8, 7, 2, 9, 7, 1, 4, 2, 8, 9, 7, 2, 1, 7, 4, 8, 9};

  std::vector<uint8_t> result =  calculator.add(a, b);
  ASSERT_EQ(result, expected_result);
}

TEST(CalculatorTest, addTest2) {
  Calculator<uint8_t> calculator;
  std::vector<uint8_t> a={1, 2, 3, 4};
  std::vector<uint8_t> b={4, 3, 2, 1};
  std::vector<uint8_t> expected_result = {5, 5, 5, 5};

  std::vector<uint8_t> result =  calculator.add(a, b);
  ASSERT_EQ(result, expected_result);
}

TEST(CalculatorTest, addTestReadsNumbersFromStringInput) {
  Calculator<uint8_t> calculator;
  std::string expression = "1+3";
  std::string result = calculator.calculate(expression);
  std::string expected_result = "4";
  ASSERT_EQ(result, expected_result);

  expression = "1123410273012734+3123481212340";
  result = calculator.calculate(expression);
  expected_result = "1126533754225074";
  ASSERT_EQ(result, expected_result);
}

TEST(CalculatorTest, TestAddition) {
  Calculator<uint8_t> calculator;
  std::string input = "12345678901234567890+98765432109876543210";
  std::string expected_output = "111111111011111111100";
  ASSERT_EQ(calculator.calculate(input), expected_output);
}

TEST(CalculatorTest, TestSubtraction) {
  Calculator<int8_t> calculator;
  std::string input = "98765432109876543210-12345678901234567890";
  std::string expected_output = "86419753208641975320";
  ASSERT_EQ(calculator.calculate(input), expected_output);

  input = "1-12345678912341234123401234567890";
  expected_output = "-12345678912341234123401234567889";
  ASSERT_EQ(calculator.calculate(input), expected_output);

  input = "9213498762340-12345678912341234123401234567890";
  expected_output = "-12345678912341234114187735805550";
  ASSERT_EQ(calculator.calculate(input), expected_output);

  input = "9876543210987654321022-1234567890123456789012132";
  expected_output = "-1224691346912469134691110";
  ASSERT_EQ(calculator.calculate(input), expected_output);

  input = "2345123412341234123-12345671234123412348901234567890";
  expected_output = "-12345671234121067225488893333767";
  ASSERT_EQ(calculator.calculate(input), expected_output);
}


TEST(CalculatorTest, TestMultiplication) {
  Calculator<uint8_t> calculator;
  std::string input = "98765432109876543210*12345678901234567890";
  std::string expected_output = "1219326311370217952237463801111263526900";
  ASSERT_EQ(calculator.calculate(input), expected_output);

  input = "8*86";
  expected_output = "688";
  ASSERT_EQ(calculator.calculate(input), expected_output);

  input = "8*8";
  expected_output = "64";
  ASSERT_EQ(calculator.calculate(input), expected_output);
}

TEST(CalculatorTest, TestMultiply) {
    Calculator<uint8_t> calculator;
    std::vector<uint8_t> a = {5, 0};
    std::vector<uint8_t> b = {2, 5};
    std::vector<uint8_t> expected_result = {1, 2, 5, 0};
    ASSERT_EQ(calculator.multiply(a, b), expected_result);

    a = {9};
    b = {9};
    expected_result = {8, 1};
    ASSERT_EQ(calculator.multiply(a, b), expected_result);

    a = {1, 0, 0, 0, 0};
    b = {1, 0, 0};
    expected_result = {1, 0, 0, 0, 0, 0, 0};
    ASSERT_EQ(calculator.multiply(a, b), expected_result);
}

TEST(CalculatorTest, TestDivision1) {
  Calculator<uint8_t> calculator;
  std::string input = "98109876543210/1234567890";
  std::string expected_output = "79469";
  ASSERT_EQ(calculator.calculate(input), expected_output);
}

TEST(CalculatorTest, TestDivide2) {
    Calculator<uint8_t> calculator;
    std::vector<uint8_t> a = {1, 0, 0, 0, 0};
    std::vector<uint8_t> b = {2, 5};
    std::string expected_result = "400";
    ASSERT_EQ(calculator.divide(a, b), expected_result);

    a = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
    b = {9};
    expected_result = "11111111111";
    ASSERT_EQ(calculator.divide(a, b), expected_result);

    a = {5, 0, 0, 0, 0, 0, 0};
    b = {1, 0, 0};
    expected_result = "50000";
    ASSERT_EQ(calculator.divide(a, b), expected_result);
}
TEST(CalculatorTest, TestPower) {
  Calculator<uint8_t> calculator;
  std::string input = "5^2";
  std::string expected_output = "25";
  ASSERT_EQ(calculator.calculate(input), expected_output);

  input = "55555^2";
  expected_output = "3086358025";
  ASSERT_EQ(calculator.calculate(input), expected_output);

}