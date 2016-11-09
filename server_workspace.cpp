/*
 * server_workspace.cpp
 *
 *  Created on: 8 nov. 2016
 *      Author: kmoriell
 */

#include "server_workspace.h"

Workspace::Workspace() {
	lobby = new Object();
	lobby->addSlot("lobby", lobby, true, false, false);
}

Workspace::~Workspace() {
	delete lobby;
}

std::string Workspace::receive(std::string &code) {
	Parser parser(vm);
	parser.setContext(lobby);
	parser.run(code);
	selfInstr += code;
	// TODO: terminar de definir el string devuelto
	return "";
}
