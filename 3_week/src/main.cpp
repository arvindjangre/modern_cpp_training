#include "../include/CSVparser.h"
#include "../include/Iparser.h"
#include "../include/JSONparser.h"
#include "../include/XMLparser.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int getFileType(const std::string &);

int main(int argc, char *argv[]) {

  int fileType = 3;
  std::string fileName = argv[1];

  switch (fileType) {
  case 1: {
    // csv parser
    CSVparser c{fileName};
    IParser &pref{c};
    std::cout << pref << std::endl;
  } break;
  case 2: {
    // XML parser
    XMLparser x{fileName};
    IParser &pref{x};
    std::cout << pref << std::endl;
  } break;
  case 3: {
    // json parser
    JsonParser j{fileName};
    IParser &pref{j};
    std::cout << pref << std::endl;
  } break;

  default:
    std::cout << "Invalid file type." << std::endl;
    break;
  }
  return 0;
}

int getFileType(const std::string &filename) {
  std::string extension = std::filesystem::path(filename).extension();

  if (extension.compare(".csv")) {
    return 1;
  } else if (extension.compare(".xml")) {
    return 2;
  } else if (extension.compare(".json")) {
    std::cout << extension << std::endl;
    return 3;
  }
  return 0;
}