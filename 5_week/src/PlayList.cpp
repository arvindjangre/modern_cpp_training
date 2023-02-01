#include "../include/PlayList.h"
#include <iostream>

void PlayList::addSong(Song song) { this->play_list.push_back(song); }
void PlayList::Play() {
  if (play_list.size() == 0) {
    std::cout << "Playlist is empty." << std::endl;
    return;
  }
  std::cout << "Playing: " << play_list[current_song_index].getSong()
            << std::endl;
}
void PlayList::Pause() {
  std::cout << "Paused: " << play_list[current_song_index].getSong()
            << std::endl;
}
void PlayList::Next() {
  current_song_index = (current_song_index + 1) % play_list.size();
  std::cout << "Playing next: " << play_list[current_song_index].getSong()
            << std::endl;
}
void PlayList::Previous() {
  current_song_index =
      (current_song_index - 1 + play_list.size()) % play_list.size();
  std::cout << "Playing previous: " << play_list[current_song_index].getSong()
            << std::endl;
}
void PlayList::MoveUp(int index) {
  if (index > 0 && index < play_list.size()) {
    std::swap(play_list[index], play_list[index - 1]);
  }
}
void PlayList::MoveDown(int index) {
  if (index >= 0 && index < play_list.size() - 1) {
    std::swap(play_list[index], play_list[index + 1]);
  }
}
void PlayList::ListSongs() {
  for (auto song : play_list) {
    std::cout << song.getSong() << std::endl;
  }
}