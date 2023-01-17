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
    Calculator<uint8_t> calculator;
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
            std::cout << "Result: " << calculator.calculate(input) << std::endl;
        }
    }
    return 0;
}
