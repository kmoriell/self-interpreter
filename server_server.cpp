#include "server_server.h"

std::string Server::loadWorkspace(std::string name) {
  m.lock();
  auto it = workspaces.find(name);
  if (it == workspaces.end()) {
    m.unlock();
    throw std::runtime_error("No existe el workspace");
  }

  workspace_tuple tuple = it->second;

  if (std::get<1>(tuple) > 0) {
    m.unlock();
    std::string error = "El workspace ";
    error += name + " esta en uso.";
    throw std::runtime_error(error);
  }

  std::get<1>(tuple) += 1;
  m.unlock();

  std::ifstream file(name);
  if (!file.is_open()) {
    std::string error = "No se puede abrir el workspace ";
    error += name + ".";
    throw std::runtime_error(error);
  }

  std::string x, strFile;

  while (file >> x)
    strFile += x + " ";

  return strFile;
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

  if (it != workspaces.end()) {
    workspace_tuple tuple = it->second;
    std::get<1>(tuple) += 1;
    it->second = tuple;
  } else {
    Workspace *wk = new Workspace();
    workspace_tuple tuple = std::make_tuple(wk, 0);
    workspaces.insert(std::make_pair(name, tuple));
  }
  m.unlock();
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

/*bool Server::checkExistence(std::string name) {

}*/

void Server::deleteWorkspace(std::string name) {
  m.lock();
  auto it = workspaces.find(name);
  if (it == workspaces.end()) {
    m.unlock();
    throw std::runtime_error("No existe el workspace");
  }

  workspaces.erase(name);
  m.unlock();
}

Object* Server::receiveCode(Object* context, std::string &code) {
  Object *result;
  try {
    m.lock();
    result = workspace.receive(context, code);
    m.unlock();
  } catch (...) {
    m.unlock();
    throw;
  }

  return result;
}

Object* Server::receiveCode(std::string &code) {
  Object *lobby = workspace.getLobby();
  return receiveCode(lobby, code);
}

Object* Server::getLobby() {
  return workspace.getLobby();
}

