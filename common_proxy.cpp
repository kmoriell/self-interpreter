/*
 * server_proxyClient.cpp
 *
 *  Created on: 8 nov. 2016
 *      Author: kmoriell
 */

#include "common_proxy.h"
#include <iostream>

Proxy::Proxy(Socket &socket) : serverSocket(socket) {
  finished = false;
  _interrupt = false;
}


/*
void ProxyClient::loadWorkspace(std::string name) {
  std::string code = server.loadWorkspace(name);
  workspace = new Workspace(name);
  try {
    workspace->receive(code);
  } catch (const std::runtime_error &e) {
    delete workspace;
    throw e;
  }
}

void ProxyClient::availableWorkspace() {
  std::vector<std::string> avlWorkspaces = server.availableWorkspace();
  std::string strWorkspaces;
  for (auto str : avlWorkspaces) {
    strWorkspaces += str;
  }

  command_t response(strWorkspaces.size() + 1,0x01, strWorkspaces);
  send(response);
}

void ProxyClient::newWorkspace(std::string name) {
  server.newWorkspace(name);
  sendOK();
}

void ProxyClient::closeWorkspace(std::string name) {
  server.closeWorkspace(name);
  sendOK();

}

void ProxyClient::deleteWorkspace(std::string name) {
  server.deleteWorkspace(name);
  sendOK();
}
*/


int Proxy::receive() {
  char *strLen = new char[sizeof(int)];
  memset(strLen, 0, sizeof(int));

  int s = serverSocket.receive(strLen, sizeof(int));
  unsigned int len = 0;
  memcpy(&len, strLen, sizeof(int));
  len = ntohl(len);

  char command;
  s = serverSocket.receive(&command, sizeof(char));

  s = 0;
  char *message = new char[len];
  message[0] = command;

  while (s < len) {
    s += serverSocket.receive(message + s, len);
  }


  clientMessage.setCommand(command);
  clientMessage.setLength(len);
  clientMessage.setMessage(message);
/*
  char *message_str = new char[length];
  memset(message_str, 0, length);
  s += serverSocket.receive(message_str, length);

  clientMessage.fromString(message_str, length); */

  std::cout << "receive()" << std::endl;
  std::cout << "len = " << len << std::endl << " command = " << command << std::endl <<
      " message = " << message << std::endl;

  delete message;
  delete[] strLen;
  return s;
}

void Proxy::send(command_t &response) {
  char command = response.getCommand();

  unsigned int len = response.getLength();
  len = htonl(len);

  char *strLen = new char[sizeof(int)];
  memcpy(strLen, &len, sizeof(int));

  std::cout << "send()" << std::endl;
  std::cout << "len = " << len << std::endl << " command = " << command << std::endl <<
      " message = " << response.getMessage() << std::endl;

  this->serverSocket.send(strLen, sizeof(int));
  this->serverSocket.send(&command, sizeof(char));
  this->serverSocket.send(response.getMessage().c_str(), response.getMessage().size());
}

void Proxy::sendError(std::string msg) {
  command_t response(msg.size() + 1, ERRORMESSAGE, msg);
  send(response);
}

void Proxy::sendOK(std::string msg) {
  command_t response(msg.size(), OKMESSAGE, msg);
  send(response);
}

bool Proxy::is_finished() {
  return this->finished;
}

void Proxy::interrupt() {
  this->_interrupt = true;
  serverSocket.shutdown();
}

