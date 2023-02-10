#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H
#include "header.h"
class NetworkUtils
{
private:
  
public:
    int server_fd, sock, new_socket, value;
    int opt = 1;
    int addrlen = sizeof(serverAddress);
    char buffer[MAX_MSG_SIZE] = {0};
    std::string message = "hello from server";
    const char *hello = message.c_str();

    int createSocket();
    std::string readMessage();
    int sendMessage(std::string response);
    int setSocketOption();
    int bindAddress();
    int listenConnection();
    int acceptConnection();
    int connect_();

    std::string readRequestFromClient();
    int sendResponseToClient(std::string response);
    

    int configureClientSocket(std::string, int);
    int connectAsClient();

};

#endif