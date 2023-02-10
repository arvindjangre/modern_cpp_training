// #include<iostream>

// #define TICK "\U00002714"

// int main() {
//   std::cout << TICK << std::endl;
//   return 0;
// }

#include "../include/NetworkUtils.h"
#include "../include/header.h"
#include "../include/helper_functions.h"
#include <pthread.h>
int next_id = 0;
std::mutex mtx;
std::condition_variable cv;
std::unordered_map<int, std::string> clients;
std::unordered_map<std::string, std::vector<int>> groups;
NetworkUtils server;

struct sockaddr_in serverAddress;

void signalHandlerForSIGINT(int signal) {
  std::cout << "SIGINT signal received. Cleaning up resources." << std::endl;
  // Perform any necessary cleanup tasks here.
  exit(0);
}

int main(int argc, char *argv[]) {
  // Register the signal handler for SIGINT
  signal(SIGINT, signalHandlerForSIGINT);
  
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    std::cerr << "Error: Could not create socket." << std::endl;
    return 1;
  }
  int optval = 1;
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(PORT);
  address.sin_addr.s_addr = INADDR_ANY;
  if (bind(server_socket, (sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    std::cerr << "Error: Could not bind socket to address." << std::endl;

    return 1;
  }

  if (listen(server_socket, BACKLOG) < 0) {
    std::cerr << "Error: Could not listen on socket." << std::endl;
    return 1;
  }

  std::cout << "Server is ready." << std::endl;
  while (true) {
    int client_socket = accept(server_socket, NULL, NULL);
    std::cout << client_socket << "\n";
    if (client_socket < 0) {
      std::cerr << "Error: Could not accept client connection." << std::endl;
      continue;
    }
    int id;

    cv.notify_all();
    std::thread t(handle_client, client_socket, id);
    t.detach();
  }

  close(server_socket);
  return 0;
}
