#include "../include/NetworkUtils.h"
#include "../include/header.h"

extern int next_id;
extern std::mutex mtx;
extern std::condition_variable cv;
extern std::unordered_map<int, std::string> clients;
extern std::unordered_map<std::string, std::vector<int>> groups;
extern NetworkUtils server;

void send_to_client(int client, const char *message, int length) {
  send(client, message, length, 0);
}

void broadcast(const char *message, int length) {
  std::unique_lock<std::mutex> lock(mtx);
  for (const auto &client : clients) {
    send_to_client(client.first, message, length);
  }
}

void send_to_group(const std::string &group, const char *message, int length) {
  std::unique_lock<std::mutex> lock(mtx);
  for (const auto& [key, values] : groups) {
  std::cout << "Key: " << key << std::endl;
  std::cout << "Values: ";
  for (const int value : values) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}
  auto it = groups.find(group);
  if (it == groups.end()) {
    return;
  }

  for (int client : it->second) {
    send_to_client(client, message, length);
  }
}

void send_notification(int client, const char *message, int length) {
  std::this_thread::sleep_for(std::chrono::milliseconds(NOTIFICATION_DELAY));
  char notification[MAX_MESSAGE_LENGTH];
  strcpy(notification, "DELIVERED: ");
  strcat(notification, message);
  send_to_client(client, notification, strlen(notification));
  strcpy(notification, "READ: ");
  strcat(notification, message);
  send_to_client(client, notification, strlen(notification));
}

void handle_client(int client, int id) {
  char buffer[MAX_MESSAGE_LENGTH];

  while (true) {
    int length = recv(client, buffer, MAX_MESSAGE_LENGTH, 0);
    if (length <= 0) {
      break;
    }

    std::string message(buffer, length);
    if (message.substr(0, 4) == "@all") {
      broadcast(buffer + 5, length - 5);
    } else if (message.substr(0, 1) == "@") {
      std::string group = message.substr(1, message.find(' ')-1);
      send_to_group(group, buffer + group.length() + 2,
                    length - group.length() - 2);

    } else if (message.substr(0, 1) == "#") {
      std::string recipient = message.substr(1, message.find(' '));
      std::unique_lock<std::mutex> lock(mtx);
      auto it = clients.find(std::stoi(recipient));
      if (it == clients.end()) {
        continue;
      }
      send_to_client(it->first, buffer + recipient.length() + 1,
                     length - recipient.length() - 1);
      // t.detach();

    } else if (message == "!list") {
      std::string response = "CLIENTS: ";
      std::unique_lock<std::mutex> lock(mtx);
      for (const auto &client : clients) {
        response += client.second + " ";
      }
      send_to_client(client, response.c_str(), response.length());

    } else if (message.substr(0, 5) == "!join") {
      std::string group = message.substr(6, message.find(' '));
      std::unique_lock<std::mutex> lock(mtx);
      if (groups.count(group) == 0) {
        // Key does not exist, create a new vector
        groups[group] = std::vector<int>();
      }
      groups[group].push_back(client);
      send_to_client(client, "Success", 9);
    } else if (message.substr(0, 1) == "+") {
      std::string name = message.substr(1, message.find(' '));
      std::unique_lock<std::mutex> lock(mtx);

      if (clients.find(client) == clients.end()) {
        clients[client] = std::to_string(client);
      }
      lock.unlock();
      send_to_client(client, "Success", 9);
    }
  }

  std::unique_lock<std::mutex> lock(mtx);
  for (auto it = groups.begin(); it != groups.end();) {
    it = groups.erase(it);
  }
  clients.erase(client);
  lock.unlock();
  cv.notify_all();
  close(client);
}

void loadDataFromFile() {
  using namespace rapidjson;

  std::ifstream jsonFile("data.json");
  std::string jsonData((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());
  jsonFile.close();

  // parse json data
  Document document;
  document.Parse(jsonData.c_str());

  // read clients
  const Value& clientsArray = document["clients"];
  for(SizeType i = 0; i < clientsArray.Size(); i++) {
    int id = clientsArray[i]["id"].GetInt();
    std::string name = clientsArray[i]["name"].GetString();
    clients[id] = name;
  }

  // read groups

  const Value& groupsArray = document["groups"];
  for(SizeType i = 0; i < groupsArray.Size(); i++) {
    std::string name = groupsArray[i]["name"].GetString();
    std::vector<int> clientIds;
    const Value& groupClientsArray = groupsArray[i]["clients"];
    for(SizeType j = 0; j < groupClientsArray.Size(); j++) {
      int clientId = groupClientsArray[j].GetInt();
      clientIds.push_back(clientId);
    }
    groups[name] = clientIds;
  }
}

void writeDataToFile() {
  using namespace rapidjson;
  StringBuffer sb;
  Writer<StringBuffer> writer(sb);

  writer.StartObject();

  // write clients

  writer.Key("clients");
  writer.StartArray();
  for (const auto& [id, name] : clients) {
    writer.StartObject();
    writer.Key("id");
    writer.Int(id);
    writer.Key("name");
    writer.String(name.c_str(), name.length());
    writer.EndObject();
  }
  writer.EndArray();

  // write groups
  writer.Key("groups");
  writer.StartArray();
  for (const auto& [name, clientIds] : groups) {
    writer.StartObject();
    writer.Key("name");
    writer.String(name.c_str(), name.length());
    writer.Key("clients");
    writer.StartArray();
    for (const auto& clientId: clientIds) {
      writer.Int(clientId);
    }
    writer.EndArray();
    writer.EndObject();
  }
  writer.EndArray();
  writer.EndObject();

  std::ofstream outputFile("data.json");
  outputFile << sb.GetString();
  outputFile.close();
}