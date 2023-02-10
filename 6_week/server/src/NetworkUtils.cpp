#include "../include/header.h"
#include "../include/NetworkUtils.h"

int NetworkUtils::createSocket()
{
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  return 0;
}
int NetworkUtils::bindAddress()
{
  NetworkUtils::setSocketOption();

  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = INADDR_ANY;
  serverAddress.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
  return 0;

}
std::string NetworkUtils::readMessage()
{
  memset(buffer, '\0', MAX_MSG_SIZE);
  value = read(sock, buffer, MAX_MSG_SIZE);
  if(value == -1){
    perror("readMessage");
  }
  return std::string(buffer);
}
int NetworkUtils::sendMessage(std::string response)
{
  if(send(sock, response.c_str(), strlen(response.c_str()), 0) == -1){
    perror("socket send function");
  }
  return 0;

}

int NetworkUtils::setSocketOption()
{
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt)))
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
  return 0;

}

int NetworkUtils::connect_()
{
  NetworkUtils::createSocket();
  NetworkUtils::bindAddress();
  return 0;
}

int NetworkUtils::listenConnection(){
  if (listen(server_fd, LISTEN_CONNECTION) < 0)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  return 0;

}
int NetworkUtils::acceptConnection(){
  if ((sock = accept(server_fd, (struct sockaddr *)&serverAddress,
                           (socklen_t *)&addrlen)) < 0)
  {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  return sock;
}
std::string NetworkUtils::readRequestFromClient()
{
  std::string request = NetworkUtils::readMessage();

  return request;
}
int NetworkUtils::sendResponseToClient(std::string response)
{
  NetworkUtils::sendMessage(response);

  return 0;
}

int NetworkUtils::configureClientSocket(std::string serverIP, int portNumber)
{
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
        printf("\n Socket creation error \n");
        return -1;
  }
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(portNumber);

  if (inet_pton(AF_INET, serverIP.c_str(), &serverAddress.sin_addr) <= 0)
  {
    printf("\nInvalid address/ Address not supported\n");
    return -1;
  }
  return 0;

}
int NetworkUtils::connectAsClient()
{
  if (connect(sock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)))
  {
    printf("connection failed\n");
    return -1;
  }

  return 0;
}
