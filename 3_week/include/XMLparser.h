#ifndef XMLPARSER_H
#define XMLPARSER_H
#include "Iparser.h"

class XMLparser : public IParser {
  private:
    std::string m_filename;
  
  public:
    XMLparser(std::string fileName) : m_filename{fileName} {}
    virtual std::ostream &print(std::ostream &out) const override;
};
#endif;