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

	return objs[objs.size() - 1];
	//selfInstr += code;
	// TODO: terminar de definir el string devuelto
	//return "";
}
