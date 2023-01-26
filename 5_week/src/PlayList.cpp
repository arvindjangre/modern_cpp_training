#include "../include/PlayList.h"
#include <iostream>

Song PlayList::getSong() {
  return this->play_list.front();
}

void PlayList::addSong(std::string song_name) {
  Song song;
  song.setSong(song_name);
  this->play_list.push_back(song);
}