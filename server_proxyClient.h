#ifndef SERVER_PROXYCLIENT_H_
#define SERVER_PROXYCLIENT_H_

#include "common_proxy.h"
#include "server_parserProtocoloServidor.h"
#include "server_workspace.h"
#include "server_object.h"

class ProxyClient: public Proxy {
private:
	Server &server;
	Workspace* workspace;
	//El proxy se guarda un puntero del objeto que ve el cliente.
	Object* objClientView = nullptr;
public:
	ProxyClient(Socket &socket, Server &server, Workspace* workspace);
	void execLobbyCMD(std::string &cad);
	void setObjName(const std::string &cad);
	void setCodeSegment(const std::string &cad);
	void addSlotNil(const std::string &cad);
	void addSlotBoolean(const std::string &cad);
	void addSlotNumber(const std::string &cad);
	void addSlotString(const std::string &cad);
	void addSlotObject(const std::string &cad);
	virtual void run();
};

#endif /* SERVER_PROXYCLIENT_H_ */
