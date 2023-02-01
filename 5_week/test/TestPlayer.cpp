#include "../include/PlayList.h"
#include "../include/Song.h"
#include "../include/Player.h"
#include <gtest/gtest.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::AtLeast;

class MockPlayList : public PlayList {
  public:
    MOCK_METHOD0(Play, void());
    MOCK_METHOD0(Pause, void());
    MOCK_METHOD0(Next, void());
    MOCK_METHOD0(Previous, void());
    MOCK_METHOD1(MoveUp, void(int));
    MOCK_METHOD1(MoveDown, void(int));
};

class PlayerTest : public ::testing::Test {
  protected:
    Player player_;
    MockPlayList play_list_;
};

TEST_F(PlayerTest, CreatePlayListTest) {
  std::string playlist_name = "first";
  player_.CreatePlaylist(playlist_name);
  ASSERT_TRUE(player_.getCount() == 1);
}

TEST_F(PlayerTest, PlayTest) {
  std::string playlist_name = "first";
  player_.CreatePlaylist(playlist_name);
  player_.AddSongToPlaylist(playlist_name, Song("one"));
  play_list_.addSong(Song("two"));
  EXPECT_CALL(play_list_, Play()).Times(AtLeast(1));
  play_list_.Play();
}

TEST_F(PlayerTest, PauseTest) {
 std::string playlist_name = "first";
  player_.CreatePlaylist(playlist_name);
  player_.AddSongToPlaylist(playlist_name, Song("one"));
  play_list_.addSong(Song("two"));
  EXPECT_CALL(play_list_, Pause()).Times(AtLeast(1));
  play_list_.Pause();
}

TEST_F(PlayerTest, NextTest) {
 std::string playlist_name = "first";
  player_.CreatePlaylist(playlist_name);
  player_.AddSongToPlaylist(playlist_name, Song("one"));
  play_list_.addSong(Song("two"));
  EXPECT_CALL(play_list_, Next()).Times(AtLeast(1));
  play_list_.Next();
}

TEST_F(PlayerTest, PreviousTest) {
 std::string playlist_name = "first";
  player_.CreatePlaylist(playlist_name);
  player_.AddSongToPlaylist(playlist_name, Song("one"));
  play_list_.addSong(Song("two"));
  EXPECT_CALL(play_list_, Previous()).Times(AtLeast(1));
  play_list_.Previous();
}