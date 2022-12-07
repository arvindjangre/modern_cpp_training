#ifndef CSVPARSER_H
#define CSVPARSER_H
#include "Iparser.h"
class CSVparser : public IParser {
private:
  std::string m_filename;

public:
  CSVparser(std::string fileName) : m_filename{fileName} {}
  virtual std::ostream &print(std::ostream &out) const override;
};

#endif