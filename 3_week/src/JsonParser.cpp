#include "../include/JSONparser.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

std::ostream &JsonParser::print(std::ostream &out) const {
  using namespace rapidjson;
  std::string path = "/home/usinglinux/cpp_arvindjangre/3_week/src/";
  std::string file = path + this->m_filename;
  std::ifstream ifs{file};
  if (!ifs.is_open()) {
    std::cerr << "Could not open file for reading!\n";
  }
  IStreamWrapper isw{ifs};

  Document mydoc;
  mydoc.ParseStream(isw);

  // DOM to string
  StringBuffer buffer;
  Writer<StringBuffer> writer(buffer);

  mydoc.Accept(writer);
  if (mydoc.HasParseError()) {
    out << "Error: " << mydoc.GetParseError() << std::endl
        << "Offset: " << mydoc.GetErrorOffset() << std::endl;
  }

  // Print the output
  out << buffer.GetString() << std::endl;
  return out;
}