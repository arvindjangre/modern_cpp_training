#include "../include/CSVparser.h"
#include "../include/Iparser.h"
#include <iostream>
#include <string>

int getFileType(const std::string &);

int main(int argc, char *argv[]) {

  int fileType = getFileType(argv[1]);
  std::string fileName = argv[1];

  switch (fileType) {
  case 1:
    // csv parser
    {
      CSVparser c{fileName};
      IParser &pref{c};
      std::cout << pref << std::endl;
    }
    break;

  default:
    break;
  }
  return 0;
}

int getFileType(const std::string &argv) {
  std::cout << argv << std::endl;
  return 1;
}