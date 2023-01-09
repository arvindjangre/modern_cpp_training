#ifndef IPARSER_H
#define IPARSER_H
#include <iostream>
class IParser {
private:
public:
  friend std::ostream &operator<<(std::ostream &out, const IParser &p) {
    return p.print(out);
  }

  virtual std::ostream &print(std::ostream &out) const = 0;
};
#endif