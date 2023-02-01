#include "../include/PlayList.h"
#include "../include/Song.h"
#include <gtest/gtest.h>

TEST(PlayListTest, addSong) {
  std::string song_name = "aaaaaaa";
  PlayList play_list;
  play_list.addSong(Song(song_name));
}