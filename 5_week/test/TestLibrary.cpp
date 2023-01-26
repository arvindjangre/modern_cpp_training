#include <gtest/gtest.h>
#include "../include/Library.h"
#include "../include/PlayList.h"


TEST(LibraryTest, createsLibrary) {
  Library lib;
  ASSERT_EQ(1, 1);
}

TEST(LibraryTest, createsPlayList) {
  Library lib;
  lib.CreatePlaylist();
  ASSERT_EQ(1, 1);
}

TEST(LibraryTest, getsFirstPlayList) {
  Library lib;
  lib.CreatePlaylist();
  PlayList pl = lib.GetPlayList();
}