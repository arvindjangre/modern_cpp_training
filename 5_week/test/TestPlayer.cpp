#include "../include/PlayList.h"
#include "../include/Song.h"
#include "../include/Player.h"
#include <gtest/gtest.h>

TEST(PlayerTest, createPlaylist){
  Player player;
  player.CreatePlaylist("first_playlist");
}