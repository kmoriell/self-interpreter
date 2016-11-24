#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <map>
#include <tuple>
#include <stack>
#include <mutex>
#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
#include "server_object.h"
#include "common_thread.h"
#include "server_workspace.h"
#include "common_define.h"
#include "server_parserProtocoloServidor.h"

class Server {
private:
	std::mutex m;
	//std::map<std::string, uint32_t> workspaces;
	//Workspace workspace;
	typedef std::tuple<Workspace*, uint32_t> workspace_tuple;
	std::map<std::string, workspace_tuple> workspaces;
private:
	Workspace* getWorkspace(const std::string &idWk);
public:
	 std::string loadWorkspace(std::string name);
	 std::vector<std::string> availableWorkspace();
	 void newWorkspace(std::string name);
	 void closeWorkspace(std::string name);
	 void deleteWorkspace(std::string name);
	Server() {};
	~Server();
	std::string receiveCode(const std::string &idWk, uint32_t &idObj, std::string &code);
	std::string getLobby(const std::string &idWk, uint32_t &idObj);
	std::string getObj(const std::string &idWk, uint32_t &idObj);
	std::string setObjName(const std::string &idWk, uint32_t &idObj, const std::string &cad);
	std::string setCodeSegment(const std::string &idWk, uint32_t &idObj, const std::string &cad);
	std::string getSlotObj(const std::string &idWk, uint32_t &idObj, const std::string &cad);
	std::string swapMutability(const std::string &idWk, uint32_t &idObj, const std::string &cad);
};

#endif /* SERVER_SERVER_H_ */
