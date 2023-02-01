#ifndef PLAYER_H
#define PLAYER_H
#include "PlayList.h"
#include <map>
class Player {
private:

public:
  std::map<std::string, PlayList> playlists;
  void CreatePlaylist(std::string playlist_name);

  void AddSongToPlaylist(std::string playlist_name, Song song);
  void Play(std::string playlist_name);
  void Pause(std::string playlist_name);
  void Next(std::string playlist_name);
  void Previous(std::string playlist_name);
  void MoveUp(std::string Playlist_name, int index);
  void MoveDown(std::string playlist_name, int index);

  void ListPlaylist();
  void ListSongsInPlaylist(std::string playlist_name);
  int getCount();
};
#endif
