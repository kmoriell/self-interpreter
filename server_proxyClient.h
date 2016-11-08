
#ifndef SERVER_PROXYCLIENT_H_
#define SERVER_PROXYCLIENT_H_

#include "common_socket.h"
#include "common_object.h"
#include "common_thread.h"
#include "server_server.h"
#include "common_types.h"
#include "server_workspace.h"
#include <string>
#include <vector>

class ProxyClient : public Thread {
 public:
  ProxyClient(Socket &socket, Server &server);
  Object* send();
  void receive(std::string code);
  void run();

 private:
  Socket &serverSocket;
  Server &server;
  Workspace *workspace = nullptr;
  bool _interrupt;
  bool finished;
  command_t clientMessage;

  void loadWorkspace(std::string name);
  void availableWorkspace();
  void newWorkspace(std::string name);
  void closeWorkspace(std::string name);
  void deleteWorkspace(std::string name);
  void send(command_t message);
  int receive();

  void sendError(std::string msg);
  void sendOK();
};

#endif /* SERVER_PROXYCLIENT_H_ */
