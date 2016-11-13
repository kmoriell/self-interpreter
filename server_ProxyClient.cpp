/*
 * server_ProxyClient.cpp
 *
 *  Created on: 12 de nov. de 2016
 *      Author: kmoriell
 */

#include "server_proxyClient.h"

void ProxyClient::sendCode(std::string code) {
  sendOK(server.receiveCode(code));
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
          /*case LOADCOMMAND:
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
            break;*/
          case SENDCOMMAND:
            sendCode(clientMessage.getMessage());
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
