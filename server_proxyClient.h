
#ifndef SERVER_PROXYCLIENT_H_
#define SERVER_PROXYCLIENT_H_

#include "common_socket.h"
#include "common_object.h"
#include "common_thread.h"
#include "server_server.h"
#include "common_types.h"
#include <string>
#include <vector>

class ProxyClient : public Thread {
 public:
  ProxyClient(Socket &socket, Server &server);
  void run();
  bool is_finished();
  void interrupt();

 private:
  Socket &serverSocket;
  Server &server;
  //Workspace *workspace = nullptr;
  bool _interrupt;
  bool finished;
  command_t clientMessage;

  /*void loadWorkspace(std::string name);
  void availableWorkspace();
  void newWorkspace(std::string name);
  void closeWorkspace(std::string name);
  void deleteWorkspace(std::string name);*/
  void receiveCode(std::string code);
  void send(command_t message);
  int receive();

  void sendError(std::string msg);
  void sendOK(std::string msg);
};

#endif /* SERVER_PROXYCLIENT_H_ */
