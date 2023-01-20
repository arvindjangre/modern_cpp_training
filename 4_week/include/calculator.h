#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "helper_functions.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
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
      if (ans[0] < 0) {
        result += '-';
        ans[0] = -ans[0];
      }
      for (int i = 0; i < ans.size(); ++i) {
        result += (char)(ans[i] + '0');
      }
    } break;

    case '*': {
      std::vector<T> ans;
      ans = multiply(num1, num2);
      for (int i = 0; i < ans.size(); ++i) {
        result += (char)(ans[i] + '0');
      }
    } break;

    case '^': {
      std::vector<T> ans;
      ans = power(num1, num2);
      for (int i = 0; i < ans.size(); ++i) {
        result += (char)(ans[i] + '0');
      }
    } break;

    case '/': {
      std::pair<std::vector<T>, std::vector<T>> ans;
      ans = divide(num1, num2);
      std::vector<T> quotient = ans.first;
      std::vector<T> remainder = ans.second;
      for (int i = 0; i < quotient.size(); ++i) {
        result += (char)(quotient[i] + '0');
      }
      result += "    ";
      for (int i = 0; i < remainder.size(); ++i) {
        result += (char)(remainder[i] + '0');
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
    return result;
  }

  std::vector<T> subtract(std::vector<T> &num1, std::vector<T> &num2) {
    std::vector<T> result;
    int i = num1.size() - 1, j = num2.size() - 1, carry = 0;

    while (i >= 0 || j >= 0) {
      int a = i < 0 ? 0 : num1[i--];
      int b = j < 0 ? 0 : num2[j--];
      int sum = a - b + carry;

      if (sum < 0) {
        carry = -1;
        sum += 10;
      } else {
        carry = 0;
      }
      result.push_back(sum);
    }

    if (carry < 0) {
      std::vector<T> temp = subtract(num2, num1);
      temp[0] *= -1;
      return temp;
    }

    std::reverse(result.begin(), result.end());
    return result;
  }

  std::vector<T> multiply(std::vector<T> num1, std::vector<T> num2) {
    std::vector<T> result(num1.size() + num2.size(), 0);
    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());
    for (int i = 0; i < num1.size(); i++) {
      for (int j = 0; j < num2.size(); j++) {
        result[i + j] += num1[i] * num2[j];
        result[i + j + 1] += result[i + j] / 10; // carry
        result[i + j] %= 10;
      }
    }
    while (result.size() > 1 && result.back() == 0) {
      result.pop_back();
    }
    std::reverse(result.begin(), result.end());
    return result;
  }

  std::pair<std::vector<T>, std::vector<T>> divide(std::vector<T> num1, std::vector<T> num2) {
    std::vector<T> quotient;
    std::vector<T> remainder;
    
    if(num2.size() == 1 && num2[0] == 0) {
      std::cout << "Error: Division by zero." << std::endl;
      return std::make_pair(quotient, remainder);
    }

    if(num1.size() < num2.size()) {
      quotient.push_back(0);
      remainder = num1;
      return std::make_pair(quotient, remainder);
    }

    int num1_len = num1.size();
    int num2_len = num2.size();

    std::vector<T> num_to_divide;
    for(int i = 0; i < num2_len; i++) {
      num_to_divide.push_back(num1[i]);
    }

    int quotient_digit = 0;

    for(int i = 0; i <= num1_len - num2_len; i++) {
      quotient_digit = 0;

      while(compare_vec(num_to_divide, num2)) {
        num_to_divide = subtract(num_to_divide, num2);
        quotient_digit++;
      }
      quotient.push_back(quotient_digit);
      
      if(i + num2_len < num1_len) {
        num_to_divide.push_back(num1[i + num2_len ]);
      }
    }

    remainder = num_to_divide;
    removeLeadingZeroes(quotient);
    removeLeadingZeroes(remainder);
    return std::make_pair(quotient, remainder);
  }

std::vector<T> power(std::vector<T> num1_vec, std::vector<T> num2_vec) {
    std::vector<T> result {1};
    long long int num2 = 0;
    for (int i = 0; i < num2_vec.size(); i++) {
      num2 = num2 * 10 + num2_vec[i];
    }
    while(num2) {
      result = multiply(result, num1_vec);
      num2--;
    }
    return result;
}


  void addToHistory(std::string input, std::string result) {
    // history contains last 10 calculations.
    if (history.size() == 10) {
      history.erase(history.begin());
    }
    history.push_back(input + " = " + result);
  }

  void showHistory() {
    for (auto &str : history) {
      std::cout << str << std::endl;
    }
  }
  std::vector<T> removeLeadingZeroes(std::vector<T> &vec) {
    while (vec.front() == 0 && vec.size() > 1) {
      vec.erase(vec.begin());
    }
    return vec;
  }
  
  bool compare_vec(std::vector<T> num1_vec, std::vector<T> num2_vec) {
    long long int num1 = 0;
    for (int i = 0; i < num1_vec.size(); i++) {
      num1 = num1 * 10 + num1_vec[i];
    }
    long long int num2 = 0;
    for (int i = 0; i < num2_vec.size(); i++) {
      num2 = num2 * 10 + num2_vec[i];
    }

    return num1 >= num2 ? 1 : 0;
  }
};

#endif