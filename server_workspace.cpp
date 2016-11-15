#include "server_workspace.h"
#include "common_define.h"

Workspace::Workspace() {
	lobby = new Object();
	lobby->setName(LOBBY);
	//El slot lobby es necesario para cuando se realizan llamadas explicitas a lobby.
	lobby->addSlot(LOBBY, lobby, false, false, false);
}

Workspace::~Workspace() {
	delete lobby;
}

Object* Workspace::receive(std::string &code) {
	Parser parser(vm);
	parser.setContext(lobby);
	std::vector<Object*> objs = parser.run(code);
    int size = objs.size() - 1;
    if (size >= 0)
	    return objs[size];
	throw std::runtime_error("Error de sintaxis");
	//selfInstr += code;
	// TODO: terminar de definir el string devuelto
	//return "";
}

VirtualMachine* Workspace::getVirtualMachine() {
	return &vm;
}
