/*
 * client_proxyServer.h
 *
 *  Created on: 9 de nov. de 2016
 *      Author: kmoriell
 */

#ifndef CLIENT_PROXYSERVER_H_
#define CLIENT_PROXYSERVER_H_

#include "common_socket.h"
#include "common_proxy.h"
#include "client_morph.h"
#include "client_parserProtocoloCliente.h"

class ProxyServer : public Proxy {
 private:
  Socket socket;
  Morph &morph;

 public:
  ProxyServer(std::string hostname, uint32_t port, Morph& morph)
      : socket(hostname, port),
        Proxy(socket),
        morph(morph) {
    this->serverSocket.connect();
  }

  virtual void sendCode(std::string code) {
    command_t command(code.size(), SENDCOMMAND, code);
    this->send(command);
  }

  void run() {
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
          case OKMESSAGE:
            std::cout << "OK";
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

  int receive() {
    int s = Proxy::receive();
    std::string str = clientMessage.getMessage();
    ParserProtocoloCliente parser(morph, str);

   return s;
  }

};

#endif /* CLIENT_PROXYSERVER_H_ */
