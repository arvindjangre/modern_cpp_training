#include "../include/PlayList.h"
#include <gtest/gtest.h>

TEST(PlayListTest, addSong) {
  PlayList pl;
  pl.addSong("song test");
  Song song;
  song.setSong("song test");
  Song play_lists_song = pl.getSong();
  EXPECT_EQ(song.getSong(), play_lists_song.getSong());
}