
#ifndef COMMON_PROXY_H_
#define COMMON_PROXY_H_

#include "common_socket.h"
#include "common_object.h"
#include "common_thread.h"
#include "server_server.h"
#include "common_types.h"
#include <string>
#include <vector>

class Proxy : public Thread {
 public:
  Proxy(Socket &socket);
  virtual void run() = 0;
  bool is_finished();
  void interrupt();

 protected:
  Socket &serverSocket;
  //Workspace *workspace = nullptr;
  bool _interrupt;
  bool finished;
  command_t clientMessage;

  /*void loadWorkspace(std::string name);
  void availableWorkspace();
  void newWorkspace(std::string name);
  void closeWorkspace(std::string name);
  void deleteWorkspace(std::string name);*/
  virtual void sendCode(std::string code) = 0;
  void send(command_t &message);
  int receive();

  void sendError(std::string msg);
  void sendOK(std::string msg);
};

#endif /* COMMON_PROXY_H_ */
