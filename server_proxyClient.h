#ifndef SERVER_PROXYCLIENT_H_
#define SERVER_PROXYCLIENT_H_

#include "common_proxy.h"
#include "server_parserProtocoloServidor.h"

class ProxyClient : public Proxy {
private:
	Server &server;
public:
	ProxyClient(Socket &socket, Server &server) : Proxy(socket), server(server) {}
	void execLobbyCMD(std::string code);
	virtual void run();
};

#endif /* SERVER_PROXYCLIENT_H_ */
