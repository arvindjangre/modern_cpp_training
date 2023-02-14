#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <tuple>
#include <list>
#include <algorithm>
#include <map>

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

#include <mutex>
#include <thread>
#include <condition_variable>

#define IP_ADDER

#define PORT 6379 // for socket

extern struct sockaddr_in serverAddress;

#define IP_ADDR "127.0.0.1"
#define BAD_CONNECTION "Bad Connection"
#define LISTEN_CONNECTION 100
#define MAX_MSG_SIZE 1024


const int MAX_CLIENTS = 100;
const int BACKLOG = 10;
const int MAX_MESSAGE_LENGTH = 1024;
const int NOTIFICATION_DELAY = 500;


#include<fstream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
