#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <vector>
#include <string>

template <typename T>
std::pair<std::vector<T>, std::vector<T>> extractNumberFromInput(std::string& input, int& operator_index) {
    std::string first_number = input.substr(0, operator_index);
    std::string second_number = input.substr(operator_index + 1);
    std::vector<T> num1, num2;

    for(int i = 0; i < first_number.length(); ++i) {
      num1.push_back(first_number[i] - '0');
    }

    for(int i = 0; i < second_number.length(); ++i) {
      num2.push_back(second_number[i] - '0');
    }
    return std::make_pair(num1, num2);
}
#endif