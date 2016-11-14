#ifndef SERVER_WORKSPACE_H_
#define SERVER_WORKSPACE_H_

#include "server_object.h"
#include "server_parser.h"
#include "server_virtualMachine.h"
#include <string>

class Workspace {
private:
	Object *lobby;
	std::string selfInstr;
	//std::string &name;
	VirtualMachine vm;

public:
	Workspace();
	~Workspace();

	Object* receive(std::string &code);
	VirtualMachine* getVirtualMachine();
};

#endif /* SERVER_WORKSPACE_H_ */
