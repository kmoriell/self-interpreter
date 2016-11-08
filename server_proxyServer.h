#include "common_socket.h"
#include "common_object.h"
#include "common_thread.h"
#include "server_server.h"
#include <string>
#include <vector>

class ProxyServer : public Thread {
 public:
  ProxyServer(Socket &socket, Server &server);
  Object* send();
  void receive(std::string code);

  void loadWorkspace(std::string name);
  std::vector<std::string> availableWorkspace();
  void newWorkspace(std::string name);
  void closeWorkspace(std::string name);
  void deleteWorkspace(std::string name);
 private:
  Socket &serverSocket;
  Server &server;
};
