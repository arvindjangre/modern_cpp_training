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

  if(argc < 2){
    std::cout << "Usage: ./parser input_file.csv" << std::endl;
    exit(0);
  }

  std::string fileName = argv[1];
  int fileType = getFileType(fileName);

  switch (fileType) {
  case 1: {
    // csv parser
    CSVparser csv{fileName};
    IParser &pref{csv};
    std::cout << pref << std::endl;
  } break;
  case 2: {
    // XML parser
    XMLparser xml{fileName};
    IParser &pref{xml};
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

  if (extension.compare(".csv") == 0) {
    return 1;
  } else if (extension.compare(".xml") == 0) {
    return 2;
  } else if (extension.compare(".json") == 0) {
    std::cout << extension << std::endl;
    return 3;
  }
  return 0;
}