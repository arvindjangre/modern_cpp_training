#ifndef JSONPARSER_H
#define JSONPARSER_H
#include "Iparser.h"
class JsonParser : public IParser {
private:
  std::string m_filename;
  std::string json;

public:
  JsonParser(std::string fileName) : m_filename{fileName} {}
  virtual std::ostream &print(std::ostream &out) const override;
};
#endif