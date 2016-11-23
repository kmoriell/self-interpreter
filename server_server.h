#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <map>
#include <tuple>
#include <mutex>
#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
#include "server_object.h"
#include "common_thread.h"
#include "server_workspace.h"

class Server {
private:
	std::mutex m;
	//std::map<std::string, uint32_t> workspaces;
	Workspace workspace;
	typedef std::tuple<Workspace*, uint32_t> workspace_tuple;
	std::map<std::string, workspace_tuple> workspaces;

public:
	 std::string loadWorkspace(std::string name);
	 std::vector<std::string> availableWorkspace();
	 void newWorkspace(std::string name);
	 void closeWorkspace(std::string name);
	 void deleteWorkspace(std::string name);
	Server() {};
	~Server() {};
	Object* receiveCode(Object* context, std::string &code);
	Object* receiveCode(std::string &code);
	Object* getLobby();
};

#endif /* SERVER_SERVER_H_ */
