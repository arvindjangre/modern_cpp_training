#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "calculator.h"
void printUsage() {
    std::cout << "Usage: 112342134+12341234" << std::endl;
    std::cout << "to quit: q" << std::endl;
    std::cout << "to see history: h" << std::endl;
}

int main() {
    Calculator<int8_t> calculator;
    std::string input;
    printUsage();
    while (true) {
        std::cout << "Enter an arithmetic expression: ";
        std::getline(std::cin, input);
        if (input == "q") {
            break;
        }
        if(input == "h") {
            calculator.showHistory();
        } else {
            std::string result = calculator.calculate(input);
            std::cout << "Result: " << result << std::endl;
            calculator.addToHistory(input, result);
        }
    }
    return 0;
}