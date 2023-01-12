#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// template <typename T>
class Calculator {
  private:
    std::vector<std::string> history;
  public:
  Calculator() {
    history.reserve(10);
  }

};

#endif