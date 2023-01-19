#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "helper_functions.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
template <typename T> class Calculator {
private:
  std::vector<std::string> history;

public:
  Calculator() { history.reserve(10); };

  std::string calculate(std::string input) {
    int operator_index = -1;
    std::string result;
    bool is_negative = false;

    for (int i = 0; i < input.length(); i++) {
      if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
          input[i] == '/' || input[i] == '^') {
        operator_index = i;
        break;
      }
    }

    if (operator_index == -1) {
      std::cout << "Invalid input. No operator found." << std::endl;
      return result;
    }

    std::pair<std::vector<T>, std::vector<T>> nums =
        extractNumberFromInput<T>(input, operator_index);
    std::vector<T> num1 = nums.first;
    std::vector<T> num2 = nums.second;
    num1 = removeLeadingZeroes(num1);
    switch (input[operator_index]) {
    case '+': {
      std::vector<T> temp;
      temp = add(num1, num2);

      for (int i = 0; i < temp.size(); ++i) {
        result += (char)(temp[i] + '0');
      }
    } break;
    case '-': {
      std::vector<T> ans;
      ans = subtract(num1, num2);
      if(ans[0] < 0) {
        result += '-';
        ans[0] = -ans[0];
      }
      for (int i = 0; i < ans.size(); ++i) {
        result += (char)(ans[i] + '0');
      }
    } break;

    default:
      break;
    }

    return result;
  }

  std::vector<T> add(std::vector<T> num1, std::vector<T> num2) {
    std::vector<T> result;
    T carry = 0;

    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0) {
      uint8_t number_from_first_list = i < 0 ? 0 : num1[i];
      uint8_t number_from_second_list = j < 0 ? 0 : num2[j];
      uint8_t sum = number_from_first_list + number_from_second_list + carry;
      carry = sum / 10;
      result.push_back(sum % 10);
      i--;
      j--;
    }
    if (carry) {
      result.push_back(carry);
    }
    std::reverse(result.begin(), result.end());
    addToHistory(num1, num2, result, "+");
    return result;
  }

  std::vector<T> subtract(std::vector<T> &num1, std::vector<T> &num2) {
    std::vector<T> result;
    int i = num1.size() -1, j = num2.size() - 1, carry = 0;

    while( i >= 0 || j >= 0) {
      int a = i < 0 ? 0 : num1[i--];
      int b = j < 0 ? 0 : num2[j--];
      int sum = a - b + carry;

      if(sum < 0) {
        carry = -1;
        sum += 10;
      } else {
        carry = 0;
      }
      result.push_back(sum);
    }

    if( carry < 0) {
      std::vector<T> temp = subtract(num2, num1);
      temp[0] *= -1;
      return temp;
    }

    std::reverse(result.begin(), result.end());
    addToHistory(num1, num2, result, "-");
    return result;
  }

  void addToHistory(std::vector<T> num1, std::vector<T> num2,
                    std::vector<T> result, std::string operation) {
    // history contains last 10 calculations.
    if (history.size() == 10) {
      history.erase(history.begin());
    }

    std::string num1_str, num2_str, result_str;
    for (auto &i : num1) {
      num1_str += std::to_string(i);
    }
    for (auto &i : num2) {
      num2_str += std::to_string(i);
    }
    for (auto &i : result) {
      result_str += std::to_string(i);
    }

    history.push_back("(" + operation + ") ----> " + num1_str + " + " + num2_str + " = " +
                      result_str);
  }

  void showHistory() {
    for (auto &str : history) {
      std::cout << str << std::endl;
    }
  }
    std::vector<T> removeLeadingZeroes(std::vector<T> &vec) {
    while(vec.front() == 0 && vec.size() > 1) {
      vec.erase(vec.begin());
    }
    return vec;
  }
};

#endif