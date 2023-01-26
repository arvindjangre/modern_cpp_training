#ifndef LIBRARY_H
#define LIBRARY_H
#include <vector>
#include <list>
#include "PlayList.h"

class Library
{
private:
  std::vector<PlayList> lib;  
public:
  void CreatePlaylist();
  PlayList GetPlayList();
};

#endif