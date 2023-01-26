#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../include/Library.h"

int main() {
  std::cout << "play list" << std::endl;

  Library lib;
  lib.CreatePlaylist();

  return 0;
}