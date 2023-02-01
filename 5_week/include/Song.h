#ifndef SONG_H
#define SONG_H
#include <string>
class Song
{
private:
  std::string name;
public:
  Song(std::string name) : name(name) {}
  std::string getSong() {
    return name;
  }
};




#endif