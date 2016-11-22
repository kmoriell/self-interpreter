#ifndef SERVER_PROXYCLIENT_H_
#define SERVER_PROXYCLIENT_H_

#include "common_proxy.h"
#include "server_parserProtocoloServidor.h"
#include "server_workspace.h"
#include "server_object.h"

class ProxyClient: public Proxy {
private:
	Server &server;
	//El proxy se guarda un puntero del objeto que ve el cliente.
	Object* objClientView = nullptr;
	Socket* sckptr = nullptr;
public:
	ProxyClient(Socket &socket, Server &server);
	~ProxyClient();
	void execLobbyCMD(std::string &cad);
	void execLocalCMD(std::string &cad);
	void showLobby();
	void execRefresh();
	void setObjName(const std::string &cad);
	void setCodeSegment(const std::string &cad);
	void getSlotObj(const std::string &cad);
	virtual void run();
};

#endif /* SERVER_PROXYCLIENT_H_ */
