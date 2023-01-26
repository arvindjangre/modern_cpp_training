#ifndef SONG_H
#define SONG_H
#include <string>
class Song
{
private:
  std::string name;
public:
  std::string getSong() {
    return name;
  }
  void setSong(std::string name) {
    this->name = name;
  }
};




#endif