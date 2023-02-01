#include "../include/PlayList.h"
#include "../include/Song.h"
#include <gtest/gtest.h>

TEST(SongTest, addSong) {
  std::string song_name = "just a song name";
  Song song(song_name);

  EXPECT_EQ(song_name, song.getSong());
}