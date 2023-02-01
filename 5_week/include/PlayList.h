#ifndef PLAYLIST_H
#define PLAYLIST_H
#include "Song.h"
#include <vector>
#include <list>
#include <string>
#include <iostream>
class PlayList
{
private:
  int current_song_index;
  std::vector<Song> play_list;
public:
  void addSong(Song);
  void Play();
  void Pause();
  void Next();
  void Previous();
  void MoveUp(int index);
  void MoveDown(int index);
  void ListSongs();

};




#endif