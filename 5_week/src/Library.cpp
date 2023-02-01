#include "../include/Library.h"
#include <iostream>

void Library::LoadPlayLists() {

}
void Library::SavePlayLists() {
  
}

void Library::CreatePlaylist() {
  std::cout << "hello";
  PlayList pl;
  this->lib.push_back(pl);
}

PlayList Library::GetPlayList() {
  return this->lib.front();
}
