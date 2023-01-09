/*
This is the app that uses calc library.
*/
#include <iostream>
#include "calc.hpp"

int main() {
  int choice;
  char ch = 'y';
  do {
    system("clear");
    std::cout << "Enter your choice:\n";
    show_choices();
    std::cin >> choice;
    process(choice);
    std::cout << "Do you want to continue(y/Y): ";
    std::cin >> ch;
  } while(ch == 'y' || ch == 'Y');

  return 0;
}