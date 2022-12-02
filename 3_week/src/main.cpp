#include "../csv-parser/include/csv.hpp"
#include <iostream>

using namespace csv;

int main() {
  std::cout << "arvind" << std::endl;
  CSVReader reader("/home/usinglinux/cppTraining2022/cpp_arvindjangre/3_week/"
                   "src/very_big_file.csv");

  for (CSVRow &row : reader) { // Input iterator
    for (CSVField &field : row) {
      // By default, get<>() produces a std::string.
      // A more efficient get<string_view>() is also available, where the
      // resulting string_view is valid as long as the parent CSVRow is alive
      std::cout << field.get<>() << std::endl;
    }
  }
  return 0;
}