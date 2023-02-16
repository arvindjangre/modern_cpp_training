#include "../include/NetworkUtils.h"
#include "../include/header.h"

extern int next_id;
extern std::mutex mtx;
extern std::condition_variable cv;
extern std::unordered_map<int, std::string> clients;
extern std::unordered_map<std::string, std::vector<int>> groups;
extern std::unordered_map<int, std::vector<std::pair<int, std::string>>>
    messages;
extern std::unordered_map<
    int, std::unordered_map<std::string, std::vector<std::string>>>
    messages_group;

extern NetworkUtils server;

void writeDataToFile();

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
  for (const auto &[key, values] : groups) {
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
      std::string group = message.substr(1, message.find(' ') - 1);
      send_to_group(group, buffer + group.length() + 2,
                    length - group.length() - 2);

      messages_group[client][group].push_back(message);
      send_to_client(client, "DELIVERED", 11);

    } else if (message.substr(0, 1) == "#") {
      std::string recipient = message.substr(1, message.find(' '));
      std::unique_lock<std::mutex> lock(mtx);
      auto it = clients.find(std::stoi(recipient));
      if (it == clients.end()) {
        continue;
      }
      send_to_client(it->first, buffer + recipient.length() + 1,
                     length - recipient.length() - 1);
      messages[client].push_back(
          std::make_pair(it->first, buffer + recipient.length() + 1));
      send_to_client(client, "DELIVERED", 11);

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

    } else if (message.substr(0, 5) == "!show") {
      std::string group = message.substr(6, message.find(' '));
      std::unique_lock<std::mutex> lock(mtx);
      if (groups.count(group) == 0) {
        message = "Group:" + group + " does not exist";
        send_to_client(client, message.c_str(), message.length() + 1);
      } else {
        for (const auto &[senderId, groups] : messages_group) {
          for (const auto &[groupName, messages_] : groups) {
            if (groupName == group) {
              for (const auto &message : messages_) {
                send_to_client(client, message.c_str(), message.length() + 1);
              }
            }
          }
        }
      }
      lock.unlock();
    }
    writeDataToFile();
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
  std::string jsonData((std::istreambuf_iterator<char>(jsonFile)),
                       std::istreambuf_iterator<char>());
  jsonFile.close();

  // parse json data
  Document document;
  document.Parse(jsonData.c_str());

  // read clients
  const Value &clientsArray = document["clients"];
  for (SizeType i = 0; i < clientsArray.Size(); i++) {
    int id = clientsArray[i]["id"].GetInt();
    std::string name = clientsArray[i]["name"].GetString();
    clients[id] = name;
  }

  // read groups
  const Value &groupsArray = document["groups"];
  for (SizeType i = 0; i < groupsArray.Size(); i++) {
    std::string name = groupsArray[i]["name"].GetString();
    std::vector<int> clientIds;
    const Value &groupClientsArray = groupsArray[i]["clients"];
    for (SizeType j = 0; j < groupClientsArray.Size(); j++) {
      int clientId = groupClientsArray[j].GetInt();
      clientIds.push_back(clientId);
    }
    groups[name] = clientIds;
  }

  // read messages
  const Value &messagesArray = document["messages"];
  for (SizeType i = 0; i < messagesArray.Size(); i++) {
    int sender = messagesArray[i]["sender"].GetInt();
    int recipient = messagesArray[i]["recipient"].GetInt();
    std::string message = messagesArray[i]["message"].GetString();

    // check if the recipient is a group
    auto it = groups.begin();
    for (it = groups.begin(); it != groups.end(); ++it) {
      auto &group = *it;
      if (std::find(group.second.begin(), group.second.end(), recipient) !=
          group.second.end()) {
        break;
      }
    }
    if (it != groups.end()) {
      // the recipient is a group
      messages_group[sender][it->first].push_back(message);
    } else {
      // the recipient is a single client
      messages[sender].push_back(make_pair(recipient, message));
    }
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
  for (const auto &[id, name] : clients) {
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
  for (const auto &[name, clientIds] : groups) {
    writer.StartObject();
    writer.Key("name");
    writer.String(name.c_str(), name.length());
    writer.Key("clients");
    writer.StartArray();
    for (const auto &clientId : clientIds) {
      writer.Int(clientId);
    }
    writer.EndArray();
    writer.EndObject();
  }
  writer.EndArray();

  // write messages
  writer.Key("messages");
  writer.StartArray();
  for (const auto &[senderId, messages_] : messages) {
    for (const auto &[receiverId, message] : messages_) {
      writer.StartObject();
      writer.Key("sender");
      writer.Int(senderId);
      writer.Key("receiver");
      writer.Int(receiverId);
      writer.Key("message");
      writer.String(message.c_str(), message.length());
      writer.EndObject();
    }
  }
  for (const auto &[senderId, groups_] : messages_group) {
    for (const auto &[groupName, messages_] : groups_) {
      for (const auto &message : messages_) {
        writer.StartObject();
        writer.Key("sender");
        writer.Int(senderId);
        writer.Key("group");
        writer.String(groupName.c_str(), groupName.length());
        writer.Key("message");
        writer.String(message.c_str(), message.length());
        writer.EndObject();
      }
    }
  }
  writer.EndArray();

  writer.EndObject();

  std::ofstream outputFile("data.json");
  outputFile << sb.GetString();
  outputFile.close();
}