#include "../include/CSVparser.h"
#include "../csv-parser/include/csv.hpp"

std::ostream &CSVparser::print(std::ostream &out) const {
  using namespace csv;

  out << "CSV parser";
  out << "arvind" << std::endl;
  CSVReader reader("/home/usinglinux/cppTraining2022/cpp_arvindjangre/3_week/"
                   "src/very_big_file.csv");

  for (CSVRow &row : reader) { // Input iterator
    for (CSVField &field : row) {
      // By default, get<>() produces a std::string.
      // A more efficient get<string_view>() is also available, where the
      // resulting string_view is valid as long as the parent CSVRow is alive
      out << field.get<>() << std::endl;
    }
  }
  return out;
}
