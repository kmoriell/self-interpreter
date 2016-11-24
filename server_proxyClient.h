#ifndef SERVER_PROXYCLIENT_H_
#define SERVER_PROXYCLIENT_H_

#include "common_proxy.h"

class ProxyClient: public Proxy {
private:
	Server &server;
	std::string idWorkspace;
	std::stack<uint32_t> seenObj;

	//uint32_t idObj = ID_LOBBY;
	Socket* sckptr = nullptr;
public:
	ProxyClient(Socket &socket, Server &server);
	~ProxyClient();
	virtual void run();
private:
	void execLobbyCMD(std::string &cad);
	void execLocalCMD(std::string &cad);
	void showLobby();
	void execRefresh();
	void setObjName(const std::string &cad);
	void setCodeSegment(const std::string &cad);
	void getSlotObj(const std::string &cad);
	void swapMutability(const std::string &cad);
	void goBack();

	void availableWks();
	void loadWks(const std::string &cad);
	void newWks(const std::string &cad);
	void deleteWks(const std::string &cad);
	void closeWks();

	uint32_t topObj();
};

#endif /* SERVER_PROXYCLIENT_H_ */
