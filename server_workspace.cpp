/*
 * server_workspace.cpp
 *
 *  Created on: 8 nov. 2016
 *      Author: kmoriell
 */

#include "server_workspace.h"

Workspace::Workspace(std::string &name) : name(name) {
	lobby = new Object();
	lobby->addSlot("lobby", lobby, true, false, false);
}

Workspace::~Workspace() {
	delete lobby;
}

void Workspace::receive(std::string &code) {
	Parser parser;
	parser.setContext(lobby);
	try {
		parser.run(code);
	} catch(const std::runtime_error &e) {
		// TODO: enviar mensaje de error. Creo que habria que escalar la excepcion

	}
	selfInstr += code;
}
