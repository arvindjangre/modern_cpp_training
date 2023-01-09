#include "matrix.hpp"
#include <iostream>

void show_choices();

int main() {
  int row, col, choice;
  char ch = 'y';

  system("clear");
  std::cout << "Enter matix 1 dimensions: ";
  std::cin >> row >> col;
  Matrix m1{row, col};

  std::cout << "Enter matix 2 dimensions: ";
  std::cin >> row >> col;
  Matrix m2{row, col};

  m1.fillValues();
  m2.fillValues();

  do {
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    std::cout << "Enter your choice:\n";
    show_choices();
    std::cin >> choice;
    try {
      switch (choice) {
      case 1: {
        Matrix m3(m1 + m2);
        std::cout << m3 << std::endl;
      } break;
      case 2: {
        Matrix m3(m1 * m2);
        std::cout << m3 << std::endl;
      } break;
      default:
        std::cout << "Invalid choice" << std::endl;
        break;
      }
    } catch (std::out_of_range &e) {
      std::cout << "Error: " << e.what() << std::endl;
    }

    while ((getchar()) != '\n')
      ;

    std::cout << "Do you want to continue(y/Y): ";
    std::cin >> ch;
  } while (ch == 'y' || ch == 'Y');
  
  return 0;
}

void show_choices() {
  std::cout << "1. Addition" << std::endl;
  std::cout << "2. Multiplication" << std::endl;
}