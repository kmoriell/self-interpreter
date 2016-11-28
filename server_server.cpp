#include "server_server.h"

Server::~Server() {
    std::stack<Workspace*> stack;

    for (auto it = workspaces.begin(); it != workspaces.end(); ++it) {
        stack.push(std::get<0>(it->second));
    }

    while (stack.size() > 0) {
        auto wk = stack.top();
        stack.pop();
        delete wk;
    }
}

void Server::loadWorkspace(std::string name) {
    m.lock();
    auto it = workspaces.find(name);
    if (it == workspaces.end()) {
        m.unlock();
        throw std::runtime_error("No existe el workspace");
    }

    workspace_tuple tuple = it->second;
    std::get<1>(tuple) += 1;
    it->second = tuple;
    m.unlock();
}

std::vector<std::string> Server::availableWorkspace() {
    std::vector<std::string> _workspaces;
    m.lock();
    for (auto it = workspaces.begin(); it != workspaces.end(); ++it) {
        _workspaces.push_back(it->first);
    }
    m.unlock();
    return _workspaces;
}

void Server::newWorkspace(std::string name) {
    m.lock();
    auto it = workspaces.find(name);

    if (it == workspaces.end()) {
        Workspace *wk = new Workspace();
        workspace_tuple tuple = std::make_tuple(wk, 0);
        workspaces.insert(std::make_pair(name, tuple));
        m.unlock();
    } else {
        m.unlock();
        std::string error = "Ya existe un workspace llamado " + name + ".";
        throw std::runtime_error(error);
    }

}

void Server::closeWorkspace(std::string name) {
    m.lock();
    auto it = workspaces.find(name);
    if (it == workspaces.end()) {
        m.unlock();
        throw std::runtime_error("No existe el workspace");
    }

    workspace_tuple tuple = it->second;
    std::get<1>(tuple) -= 1;
    it->second = tuple;
    m.unlock();
}

void Server::deleteWorkspace(std::string name) {
    m.lock();
    auto it = workspaces.find(name);
    if (it == workspaces.end()) {
        m.unlock();
        throw std::runtime_error("No existe el workspace");
    } else {
        auto tuple = it->second;
        if (std::get<1>(tuple) == 0) {
            workspaces.erase(name);
            m.unlock();
        } else {
            m.unlock();
            std::string error = "El workspace " + name
                    + " tiene un cliente conectado.";
            throw std::runtime_error(error);
        }
    }

}

Workspace* Server::getWorkspace(const std::string &idWk) {
    m.lock();
    auto it = workspaces.find(idWk);
    m.unlock();
    if (it == workspaces.end()) {
        std::string error = "El workspace " + idWk + " no existe";
        throw std::runtime_error(error);
    }
    Workspace* _wk = std::get<0>(it->second);
    return _wk;
}

std::string Server::receiveCode(const std::string &idWk, uint32_t &idObj,
        std::string &code) {
    std::cout << "ID Objeto consultado: " << idObj << std::endl;
    std::cout << "Objeto consultado: " << std::endl;
    Workspace* wk = getWorkspace(idWk);

    m.lock();
    wk->findObjectById(idObj)->printObj(
            std::vector<Object*> { });
    m.unlock();

    std::string msg = "";
    try {
        m.lock();
        Object *context = wk->findObjectById(idObj);
        uint32_t idRet;
        idRet = wk->receive(context, code);
        Object *objRet = wk->findObjectById(idRet);
        idObj = idRet;
        m.unlock();
        msg = ParserProtocoloServidor(objRet).getString();
    } catch (...) {
        m.unlock();
        throw;
    }
    return msg;
}

std::string Server::getLobby(const std::string &idWk, uint32_t &idObj) {
    idObj = ID_LOBBY;
    return getObj(idWk, idObj);
}

std::string Server::getObj(const std::string &idWk, uint32_t &idObj) {
    std::cout << "ID Objeto consultado: " << idObj << std::endl;
    std::cout << "Objeto consultado: " << std::endl;
    getWorkspace(idWk)->findObjectById(idObj)->printObj(
            std::vector<Object*> { });

    Object* objRet = getWorkspace(idWk)->findObjectById(idObj);
    return ParserProtocoloServidor(objRet).getString();
}

std::string Server::setObjName(const std::string &idWk, uint32_t &idObj,
        const std::string &cad) {
    std::cout << "ID Objeto consultado: " << idObj << std::endl;
    std::cout << "Objeto consultado: " << std::endl;
    getWorkspace(idWk)->findObjectById(idObj)->printObj(
            std::vector<Object*> { });

    Object* objRet = getWorkspace(idWk)->findObjectById(idObj);
    objRet->setName(cad);
    return ParserProtocoloServidor(objRet).getString();
}

std::string Server::setCodeSegment(const std::string &idWk, uint32_t &idObj,
        const std::string &cad) {
    std::cout << "ID Objeto consultado: " << idObj << std::endl;
    std::cout << "Objeto consultado: " << std::endl;
    getWorkspace(idWk)->findObjectById(idObj)->printObj(
            std::vector<Object*> { });

    Object* objRet = getWorkspace(idWk)->findObjectById(idObj);
    objRet->setCodeSegment(cad);
    return ParserProtocoloServidor(objRet).getString();
}

std::string Server::getSlotObj(const std::string &idWk, uint32_t &idObj,
        const std::string &cad) {
    std::cout << "ID Objeto consultado: " << idObj << std::endl;
    std::cout << "Objeto consultado: " << std::endl;
    getWorkspace(idWk)->findObjectById(idObj)->printObj(
            std::vector<Object*> { });

    Object* obj = getWorkspace(idWk)->findObjectById(idObj);
    auto slots = obj->getSlots();
    auto it = slots.find(cad);
    if (it != slots.end()) {
        Object* objRet = std::get<0>(it->second);
        if (!objRet) {
            throw std::runtime_error("El slot tiene un puntero nulo");
        } else {
            idObj = objRet->getId();
            return ParserProtocoloServidor(objRet).getString();
        }
    } else {
        throw std::runtime_error("El slot buscado no existe");
    }
}

std::string Server::swapMutability(const std::string &idWk, uint32_t &idObj,
        const std::string &cad) {
    std::cout << "ID Objeto consultado: " << idObj << std::endl;
    std::cout << "Objeto consultado: " << std::endl;
    getWorkspace(idWk)->findObjectById(idObj)->printObj(
            std::vector<Object*> { });

    Object* obj = getWorkspace(idWk)->findObjectById(idObj);
    obj->swapSlotMutability(cad);
    idObj = obj->getId();
    return ParserProtocoloServidor(obj).getString();
    /*auto slots = obj->getSlots();
     auto it = slots.find(cad);
     if (it != slots.end()) {
     auto tuple = it->second;
     std::cout << "Es mutable? " << std::get<1>(tuple) << std::endl;
     if (std::get<1>(tuple)) {
     std::get<1>(tuple) = false;
     it->second = tuple;
     } else {
     std::get<1>(tuple) = true;
     it->second = tuple;
     }

     std::cout << "Y ahora, es mutable? " << std::get<1>(it->second)
     << std::endl;
     idObj = obj->getId();
     return ParserProtocoloServidor(obj).getString();
     } else {
     throw std::runtime_error("El slot buscado no existe");
     }*/
}
