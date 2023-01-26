#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "Song.h"
#include <vector>
#include <list>
#include <string>
class PlayList
{
private:
  std::list<Song> play_list;
  
public:
  Song getSong();
  void addSong(std::string);
};




#endif