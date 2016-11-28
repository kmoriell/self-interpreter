#include "server_server.h"

Server::Server() {
}

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
    auto it = workspaces.find(idWk);
    if (it == workspaces.end()) {
        std::string error = "El workspace " + idWk + " no existe";
        throw std::runtime_error(error);
    }
    Workspace* _wk = std::get<0>(it->second);
    return _wk;
}

std::string Server::receiveCode(const std::string &idWk, uint32_t &idObj,
        std::string &code) {
    std::string msg = "";
    try {
        m.lock();
        Workspace* wk = getWorkspace(idWk);
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
    Workspace* wk;
    Object* objRet;
    try {
        wk = getWorkspace(idWk);
        objRet = wk->findObjectById(idObj);
    } catch(...) {
        m.unlock();
        throw;
    }
    return ParserProtocoloServidor(objRet).getString();
}

std::string Server::setObjName(const std::string &idWk, uint32_t &idObj,
        const std::string &cad) {
    Workspace* wk;
    Object* objRet;
    try {
        wk = getWorkspace(idWk);
        objRet = wk->findObjectById(idObj);
        objRet->setName(cad);
    } catch(...) {
        m.unlock();
        throw;
    }
    return ParserProtocoloServidor(objRet).getString();
}

std::string Server::setCodeSegment(const std::string &idWk, uint32_t &idObj,
        const std::string &cad) {
    Workspace* wk;
    Object* objRet;
    try {
    wk = getWorkspace(idWk);
    objRet = wk->findObjectById(idObj);
    objRet->setCodeSegment(cad);
    } catch(...) {
        m.unlock();
        throw;
    }
    return ParserProtocoloServidor(objRet).getString();
}

std::string Server::getSlotObj(const std::string &idWk, uint32_t &idObj,
        const std::string &cad) {
    Workspace* wk;
    Object* obj;
    m.lock();
    try {
        wk = getWorkspace(idWk);
        obj = wk->findObjectById(idObj);
    } catch(...) {
        m.unlock();
        throw;
    }
    std::string retVal;
    auto slots = obj->getSlots();
    auto it = slots.find(cad);
    if (it != slots.end()) {
        Object* objRet = std::get<0>(it->second);
        if (!objRet) {
            m.unlock();
            throw std::runtime_error("El slot tiene un puntero nulo");
        } else {
            idObj = objRet->getId();
            retVal = ParserProtocoloServidor(objRet).getString();
        }
    } else {
        m.unlock();
        throw std::runtime_error("El slot buscado no existe");
    }
    m.unlock();
    return retVal;
}

std::string Server::swapMutability(const std::string &idWk, uint32_t &idObj,
        const std::string &cad) {
    Workspace* wk;
    Object* obj;
    m.lock();
    try {
        wk = getWorkspace(idWk);
        obj = wk->findObjectById(idObj);
        obj->swapSlotMutability(cad);
    } catch(...) {
        m.unlock();
        throw;
    }
    idObj = obj->getId();
    m.unlock();
    return ParserProtocoloServidor(obj).getString();
}	
