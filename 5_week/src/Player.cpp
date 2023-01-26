#include "../include/Player.h"
#include <iostream>

void Player::play() {
  Library lib;
  PlayList pl = lib.GetPlayList();
  std::cout << pl.getSong().getSong() << std::endl;
}
