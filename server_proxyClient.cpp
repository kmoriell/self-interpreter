/*
 * server_proxyClient.cpp
 *
 *  Created on: 8 nov. 2016
 *      Author: kmoriell
 */

#include "server_proxyClient.h"

ProxyClient::ProxyClient(Socket &socket, Server &server) : serverSocket(socket), server(server) {
  finished = false;
  _interrupt = false;
}

Object* ProxyClient::send() {
  // TODO: hacer este metodo
  return nullptr;
}

void ProxyClient::receive(std::string code) {
  if (!workspace)
    // TODO: error
    //sendError("");
    ;
  workspace->receive(code);
  sendOK();

}

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

void ProxyClient::run() {
  while (!_interrupt) {
    try {
      int s = this->receive();
      if (s == 0) {
        finished = true;
        break;
      }
      switch (this->clientMessage.getCommand()) {
        case -1:
          // TODO: error
          break;
        case LOADCOMMAND:
          loadWorkspace(clientMessage.getMessage());
          break;
        case AVAILABLECOMMAND:
          availableWorkspace();
          break;
        case NEWCOMMAND:
          newWorkspace(clientMessage.getMessage());
          break;
        case DELETECOMMAND:
          deleteWorkspace(clientMessage.getMessage());
          break;
        case CLOSECOMMAND:
          closeWorkspace(clientMessage.getMessage());
          break;
        default:
          sendError("Comando desconocido.");
      }
    } catch (const std::runtime_error &e) {
      if (!_interrupt)
        throw e;
    }
  }
}

void ProxyClient::send(command_t response) {
  char *response_str = nullptr;
  response.toString(response_str);
  this->serverSocket.send(response_str, response.getLength());
  delete[] response_str;
}

int ProxyClient::receive() {
  char *messageLength = new char[sizeof(int)];
  memset(messageLength, 0, sizeof(int));
  int s = serverSocket.receive(messageLength, sizeof(int));
  size_t length = ::atoi(messageLength);
  length = ::ntohl(length);
  delete messageLength;

  char *message_str = new char[length];
  memset(message_str, 0, length);
  s += serverSocket.receive(message_str, length);

  clientMessage.fromString(message_str, length);
  delete[] message_str;
  return s;
}

void ProxyClient::sendError(std::string msg) {
  command_t response(msg.size() + 1, ERRORMESSAGE, msg);
  send(response);
}

void ProxyClient::sendOK() {
  command_t response(1, OKMESSAGE, std::string{});
  send(response);
}

