#include "../include/NetworkUtils.h"
#include "../include/header.h"
#include <thread>
struct sockaddr_in serverAddress;
std::string serverHostName = "127.0.0.1";
std::string serverPortNumber = "6379";
#define MAX_MESSAGE_LENGTH 1024

void signalCallbackHandler(int signum) {
  printf("Caught signal SIGPIPE %d\n", signum);
}

struct sockaddr_in serv_addr;
NetworkUtils protocol;
void sendMessage();
void receiveMessage();

int main(int argc, char *argv[]) {
  signal(SIGPIPE, signalCallbackHandler);
  std::string key;
  std::string value;
  std::string request;
  std::string response;
  std::string serverAddress = "";

  while (true) {
    protocol.configureClientSocket(serverHostName,
                                   atoi(serverPortNumber.c_str()));
    if (protocol.connectAsClient() == -1) {
      throw std::runtime_error("Couldn't connect.");
    }
    std::thread send_thread(sendMessage);
    std::thread receive_thread(receiveMessage);

    send_thread.join();
    receive_thread.join();
  }

  return 0;
}

void sendMessage() {
  while (true) {
    std::cout << "\nSending:  -> ";
    std::string message;
    std::getline(std::cin, message);
    protocol.sendMessage(message);
  }
}

void receiveMessage() {
  while (true) {
    std::cout << "\nReceived: -> ";
    std::cout << protocol.readMessage() << std::endl;
  }
}