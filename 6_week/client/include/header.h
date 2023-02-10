#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <tuple>
#include <list>

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>

#include <netinet/in.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>

#define IP_ADDER

#define PORT 6379 // for socket

extern struct sockaddr_in serverAddress;

#define IP_ADDR "127.0.0.1"
#define COMM_INITIATIOR "ics 1000"
#define INITIATOR_RESPONSE "1001 ics"
#define BAD_CONNECTION "Bad Connection"
#define LISTEN_CONNECTION 100
#define MAX_MSG_SIZE 1024
