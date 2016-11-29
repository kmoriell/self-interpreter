#include "server_workspace.h"
#include "common_define.h"

Workspace::Workspace() {
    lobby = new Object();
    std::string _lobby = LOBBY;
    lobby->setName(_lobby);
    //El slot lobby es necesario para cuando se realizan llamadas explicitas a lobby.
    lobby->addSlot(_lobby, lobby, false, true, false);
    lobby->enableNativeMethod("collect");
    vm.setLobby(lobby);
}

Workspace::~Workspace() {
    lobby->collect(std::vector<Object*> { });
    delete lobby;
}

uint32_t Workspace::receive(Object* context, std::string &code) {
    Parser parser(vm, context);
    std::vector<Object*> objs = parser.parse(code);
    int size = objs.size() - 1;
    if (size >= 0) {
        return objs[size]->getId();
    } else
        throw std::runtime_error("Error de sintaxis");
}

Object* Workspace::getLobby() {
    return lobby;
}

Object* Workspace::findObjectById(uint32_t id) {
    return vm.findObjectById(id);
}
