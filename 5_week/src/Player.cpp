#include "../include/Player.h"
#include <iostream>

  void Player::CreatePlaylist(std::string playlist_name) {
    playlists[playlist_name] = PlayList();
  }

  void Player::AddSongToPlaylist(std::string playlist_name, Song song) {
    playlists[playlist_name].addSong(song);
  }
  void Player::Play(std::string playlist_name) {
    if (playlists.size() == 0) {
      std::cout << "Playlists is empty." << std::endl;
      return;
    }
    if (playlists.find(playlist_name) != playlists.end()) {
      playlists[playlist_name].Play();
    }
    else {
      std::cout << "Playlist not found." << std::endl;
    }
  }
  void Player::Pause(std::string playlist_name) { playlists[playlist_name].Pause(); }
  void Player::Next(std::string playlist_name) { playlists[playlist_name].Next(); }
  void Player::Previous(std::string playlist_name) {
    playlists[playlist_name].Previous();
  }
  void Player::MoveUp(std::string Playlist_name, int index) {
    playlists[Playlist_name].MoveUp(index);
  }
  void Player::MoveDown(std::string playlist_name, int index) {
    playlists[playlist_name].MoveDown(index);
  }

  void Player::ListPlaylist() {
    for (auto playlist : playlists) {
        std::cout << playlist.first << std::endl;
    }
  }
  void Player::ListSongsInPlaylist(std::string playlist_name) {
    playlists[playlist_name].ListSongs();
  }
