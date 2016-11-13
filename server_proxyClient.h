/*
 * server_proxyClient.h
 *
 *  Created on: 9 de nov. de 2016
 *      Author: kmoriell
 */

#ifndef SERVER_PROXYCLIENT_H_
#define SERVER_PROXYCLIENT_H_

#include "common_proxy.h"

class ProxyClient : public Proxy {
 private:
  Server &server;
 public:
  ProxyClient(Socket &socket, Server &server) : Proxy(socket), server(server) { }
  virtual void sendCode(std::string code);
  virtual void run();
};



#endif /* SERVER_PROXYCLIENT_H_ */
