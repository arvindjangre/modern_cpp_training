#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "calculator.h"

int main() {
    Calculator<uint8_t> calculator;
    std::string input;
    while (true) {
        std::cout << "Enter an arithmetic expression: ";
        std::getline(std::cin, input);
        if (input == "q") {
            break;
        }
        if(input == "h") {
            calculator.showHistory();
        } else {
            std::cout << "Result: " << calculator.calculate(input) << std::endl;
        }
    }
    return 0;
}
