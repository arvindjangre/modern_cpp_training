#include "../include/Library.h"
#include "../include/Player.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

void show_choices();
int main() {
  Player player;
  int choice;
  std::string play_list_name;
  std::string song_name;
  int index;

  char ch = 'y';
  system("clear");
  do {
    std::cout << "\n\nEnter your choice:\n";
    show_choices();
    std::cin >> choice;

    switch (choice) {
    case 1: {
      std::cout << "Enter playlist name: ";
      std::cin >> play_list_name;
      player.Play(play_list_name);
    } break;
    case 6: {

      std::cout << "Enter playlist name: ";
      std::cin >> play_list_name;
      player.CreatePlaylist(play_list_name);
    } break;

    case 2:
      player.Next(play_list_name);
      break;
    case 3:
      player.Previous(play_list_name);
      break;
    case 4:
      std::cout << "Enter index :";
      std::cin >> index;
      player.MoveUp(play_list_name, index);
      break;
    case 5:
      std::cout << "Enter index :";
      std::cin >> index;
      player.MoveDown(play_list_name, index);
      break;
    case 7:
      std::cout << "Enter song name: ";
      std::cin.ignore();
      getline(std::cin, song_name);
      player.AddSongToPlaylist(play_list_name, Song(song_name));
      break;
    case 8:
      player.ListPlaylist();
      std::cout << "Select your playlist: " << std::endl;
      std::cin >> play_list_name;
      player.Play(play_list_name);
    case 9:
      player.ListSongsInPlaylist(play_list_name);
    default:
      break;
    }
    while ((getchar()) != '\n')
      ;

  } while (ch == 'y' || ch == 'Y');
  return 0;
}

void show_choices() {
  std::cout << "1. Play/Pause" << std::endl;
  std::cout << "2. Next" << std::endl;
  std::cout << "3. Previous" << std::endl;
  std::cout << "4. Move Song up the playlist" << std::endl;
  std::cout << "5. Move Song down the playlist" << std::endl;
  std::cout << "6. Create Playlist" << std::endl;
  std::cout << "7. Add song to playlist" << std::endl;
  std::cout << "8. Select Playlist" << std::endl;
  std::cout << "9. List song in playlist:\n" << std::endl;
}