/*
 * server_workspace.h
 *
 *  Created on: 8 nov. 2016
 *      Author: kmoriell
 */

#ifndef SERVER_WORKSPACE_H_
#define SERVER_WORKSPACE_H_

#include "common_object.h"
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

	std::string receive(std::string &code);

};


#endif /* SERVER_WORKSPACE_H_ */
