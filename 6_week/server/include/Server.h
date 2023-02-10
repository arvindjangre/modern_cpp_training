#ifndef SERVER_H
#define SERVER_H

class Server
{
private:
  
public:
  void listen();
  void accept();
  int read();
  int send();
};

#endif