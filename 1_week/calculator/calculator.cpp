#include "calculator.hpp"

void show_choices() {
  std::cout << "1. Addition" << std::endl;
  std::cout << "2. Subtraction" << std::endl;
  std::cout << "3. Multiplication" << std::endl;
  std::cout << "4. Division" << std::endl;
  std::cout << "5. Square " << std::endl;
  std::cout << "6. Square root" << std::endl;
  std::cout << "7. Cube " << std::endl;
  std::cout << "8. Cube root" << std::endl;
  std::cout << "9. Bitwise OR" << std::endl;
  std::cout << "10. Bitwise AND" << std::endl;
  std::cout << "11. Bitwise NOT" << std::endl;
  std::cout << "12. Bitwise XOR" << std::endl << std::endl;
}

void process(int choice) {
  int result, num1, num2;
  switch (choice) {
  case 1:
    get_two_numbers(&num1, &num2);
    result = num1 + num2;
    std::cout << "Output: " << result << std::endl;
    break;
  case 2:
    get_two_numbers(&num1, &num2);
    result = num1 - num2;
    std::cout << "Output: " << result << std::endl;
    break;
  case 3:
    get_two_numbers(&num1, &num2);
    result = num1 * num2;
    std::cout << "Output: " << result << std::endl;
    break;
  case 4:
    get_two_numbers(&num1, &num2);
    std::cout << "Output: " << num1 / num2 << std::endl;
    break;
  case 5:
    get_number(&num1);
    result = num1 * num1;
    std::cout << "Output: " << result << std::endl;
    break;
  case 6:
    get_number(&num1);
    std::cout << "Output: " << sqrt(num1) << std::endl;
    break;
  case 7:
    get_number(&num1);
    result = num1 * num1 * num1;
    std::cout << "Output: " << result << std::endl;
    break;

  case 8:
    get_number(&num1);
    std::cout << "Output: " << cbrt(num1) << std::endl;
    break;
  case 9:
    get_two_numbers(&num1, &num2);
    std::cout << "Output: " << (num1 | num2) << std::endl;
    break;
  case 10:
    get_two_numbers(&num1, &num2);
    std::cout << "Output: " << (num1 & num2) << std::endl;
    break;
  case 11:
    get_number(&num1);
    std::cout << "Output: " << ~num1 << std::endl;
    break;
  case 12:
    get_two_numbers(&num1, &num2);
    std::cout << "Output: " << (num1 ^ num2) << std::endl;
    break;

  default:
    break;
  }
}
void get_two_numbers(int *num1, int *num2) {
  std::cout << "Enter two numbers:\nInput: ";
  std::cin >> *num1 >> *num2;
}

void get_number(int *num1) {
  std::cout << "Enter the number:\nInput: ";
  std::cin >> *num1;
}
